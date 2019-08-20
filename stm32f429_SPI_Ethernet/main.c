#include "main.h"
#include "spi.h"
char lcd_text_main[100];

/* Internet define */
#include <stdbool.h>
#include <ctype.h>
#include "socket.h"
#include "dhcp.h"
#include "dns.h"

#define DHCP_SOCKET     0
#define DNS_SOCKET      1
#define HTTP_SOCKET     2

// 1K should be enough, see https://forum.wiznet.io/t/topic/1612/2
uint8_t dhcp_buffer[1024];
// 1K seems to be enough for this buffer as well
uint8_t dns_buffer[1024];

volatile bool ip_assigned = false;

void Callback_IPAssigned(void) {
    
    sprintf("Callback: IP assigned! Leased time: %d sec\r\n", getDHCPLeasetime()); 
    terminalWrite(lcd_text_main); 
   
    ip_assigned = true;
}
 
void Callback_IPConflict(void) {
    terminalWrite("Callback: IP conflict!\r\n");
}

/* Ethernet W5500 define */


static inline void Delay_1us(uint32_t nCnt_1us)
{
  volatile uint32_t nCnt;

  for (; nCnt_1us != 0; nCnt_1us--)
    for (nCnt = 13; nCnt != 0; nCnt--);
}


void W5500_Unselect(void);
void W5500_Select(void);


void W5500_Unselect(void){

  GPIO_SetBits(GPIOE,GPIO_Pin_3);

}

void W5500_Select(void){

  GPIO_ResetBits(GPIOE,GPIO_Pin_3);

}

uint8_t W5500_ReadByte(void) {
    uint8_t byte;
    byte = SPI4_Xfer(0xff);
    return byte;
}

void W5500_WriteByte(uint8_t byte) {
    SPI4_Xfer(byte);
}


void init() {
    terminalWrite("\r\ninit() called!\r\n");

    terminalWrite("Registering W5500 callbacks...\r\n");
    reg_wizchip_cs_cbfunc(W5500_Select, W5500_Unselect);
    reg_wizchip_spi_cbfunc(W5500_ReadByte, W5500_WriteByte);

    terminalWrite("Calling wizchip_init()...\r\n");
    uint8_t rx_tx_buff_sizes[] = {2, 2, 2, 2, 2, 2, 2, 2};
    wizchip_init(rx_tx_buff_sizes, rx_tx_buff_sizes);
    
    terminalWrite("Calling DHCP_init()...\r\n");
    wiz_NetInfo net_info = {
        .mac  = { 0xEA, 0x11, 0x22, 0x33, 0x44, 0xEA },
        .dhcp = NETINFO_DHCP
    };
    // set MAC address before using DHCP
    setSHAR(net_info.mac);
    DHCP_init(DHCP_SOCKET, dhcp_buffer);

    terminalWrite("Registering DHCP callbacks...\r\n");
    reg_dhcp_cbfunc(
        Callback_IPAssigned,
        Callback_IPAssigned,
        Callback_IPConflict
    );

    terminalWrite("Calling DHCP_run()...\r\n");
    // actually should be called in a loop, e.g. by timer
    uint32_t ctr = 10000;
    while((!ip_assigned) && (ctr > 0)) {
        DHCP_run();
        ctr--;
    }
    if(!ip_assigned) {
        terminalWrite("\r\nIP was not assigned :(\r\n");
        return;
    }else{

        terminalWrite("\r\nGot IP :)\r\n");

    }

    getIPfromDHCP(net_info.ip);
    getGWfromDHCP(net_info.gw);
    getSNfromDHCP(net_info.sn);

    uint8_t dns[4];
    getDNSfromDHCP(dns);

    sprintf(lcd_text_main, "IP:  %d.%d.%d.%d\r\nGW:  %d.%d.%d.%d\r\nNet: %d.%d.%d.%d\r\nDNS: %d.%d.%d.%d\r\n",
    
        net_info.ip[0], net_info.ip[1], net_info.ip[2], net_info.ip[3],
        net_info.gw[0], net_info.gw[1], net_info.gw[2], net_info.gw[3],
        net_info.sn[0], net_info.sn[1], net_info.sn[2], net_info.sn[3],
        dns[0], dns[1], dns[2], dns[3]
    );
    terminalWrite(lcd_text_main);
    terminalWrite("Calling wizchip_setnetinfo()...\r\n");
    wizchip_setnetinfo(&net_info);

    terminalWrite("Calling DNS_init()...\r\n");
    DNS_init(DNS_SOCKET, dns_buffer);

    uint8_t addr[4];
    {
        char domain_name[] = "www.google.com";
        sprintf(lcd_text_main,"Resolving domain name \"%s\"...\r\n", domain_name);
        terminalWrite(lcd_text_main);
        int8_t res = DNS_run(dns, (uint8_t*)&domain_name, addr);
        if(res != 1) {
            sprintf(lcd_text_main,"DNS_run() failed, res = %d", res); terminalWrite(lcd_text_main);
            return;
        }
        sprintf(lcd_text_main,"Result: %d.%d.%d.%d\r\n", addr[0], addr[1], addr[2], addr[3]); terminalWrite(lcd_text_main);
    }

    terminalWrite("Creating socket...\r\n");
    uint8_t http_socket = HTTP_SOCKET;
    uint8_t code = socket(http_socket, Sn_MR_TCP, 10888, 0);
    if(code != http_socket) {
        sprintf(lcd_text_main,"socket() failed, code = %d\r\n", code); terminalWrite(lcd_text_main);
        return;
    }

    terminalWrite("Socket created, connecting...\r\n");
    code = connect(http_socket, addr, 80);
    if(code != SOCK_OK) {
        sprintf(lcd_text_main,"connect() failed, code = %d\r\n", code); terminalWrite(lcd_text_main);
        close(http_socket);
        return;
    }

    terminalWrite("Connected, sending HTTP request...\r\n");
    {
        char req[] = "GET / HTTP/1.0\r\nHost: eax.me\r\n\r\n";
        uint16_t len = sizeof(req) - 1;
        uint8_t* buff = (uint8_t*)&req;
        while(len > 0) {
            sprintf(lcd_text_main,"Sending %d bytes...\r\n", len); terminalWrite(lcd_text_main);
            int32_t nbytes = send(http_socket, buff, len);
            if(nbytes <= 0) {
                sprintf(lcd_text_main,"send() failed, %d returned\r\n", nbytes); terminalWrite(lcd_text_main);
                close(http_socket);
                return;
            }
            sprintf(lcd_text_main,"%d bytes sent!\r\n", nbytes); terminalWrite(lcd_text_main);
            len -= nbytes;
        }
    }

    terminalWrite("Request sent. Reading response...\r\n");
    {
        char buff[32];
        for(;;) {
            int32_t nbytes = recv(http_socket, (uint8_t*)&buff, sizeof(buff)-1);
            if(nbytes == SOCKERR_SOCKSTATUS) {
                terminalWrite("\r\nConnection closed.\r\n");
                break;
            }

            if(nbytes <= 0) {
                sprintf(lcd_text_main,"\r\nrecv() failed, %d returned\r\n", nbytes); terminalWrite(lcd_text_main);
                break;
            }

            buff[nbytes] = '\0';
            sprintf(lcd_text_main,"%s", buff); terminalWrite(lcd_text_main);
        }
    }

    terminalWrite("Closing socket.\r\n");
    close(http_socket);

}

int main(void)
{

  uint32_t runner=0;
  uint8_t receivedData=0;

	  SysTick_Config(180000);
    SPI_Initialization();

    lcd_init();
    lcd_drawBackground(20,60,250);
    lcd_drawBGPersimmon(20, 60, 250);
    LCD_SetColors(LCD_COLOR_WHITE-1,LCD_COLOR_WHITE);

    LCD_SetFont(&Font8x12); 

    terminalBufferInitilization();

  init();

    while(1){

    }

    while(1){
      SPI_I2S_SendData(SPI4,0x80);
      while (SPI_I2S_GetFlagStatus(SPI4, SPI_I2S_FLAG_TXE) == RESET);

      while (SPI_I2S_GetFlagStatus(SPI4, SPI_FLAG_RXNE) == RESET);
      receivedData=SPI_I2S_ReceiveData(SPI4);

      sprintf(lcd_text_main,"receivedData : %x    \n", receivedData); terminalWrite(lcd_text_main); 
   


      SPI_I2S_SendData(SPI4,0x05);
      while (SPI_I2S_GetFlagStatus(SPI4, SPI_I2S_FLAG_TXE) == RESET);

      while (SPI_I2S_GetFlagStatus(SPI4, SPI_FLAG_RXNE) == RESET);
      receivedData=SPI_I2S_ReceiveData(SPI4);
      

      sprintf(lcd_text_main,"receivedData : %x    \n", receivedData); terminalWrite(lcd_text_main); 
   
      Delay_1us(170000);
    }
  
}



// TODO:
/* Systick 1s for DHCP handler




 */