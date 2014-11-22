#Output files
PROJECT=firmware
EXECUTABLE=$(PROJECT).elf
BIN_IMAGE=$(PROJECT).bin
HEX_IMAGE = $(PROJECT).hex
#============================================================================#
HOST_CC=gcc
#Cross Compiler
CC=arm-none-eabi-gcc
OBJCOPY=arm-none-eabi-objcopy
GDB=arm-none-eabi-gdb
LD=arm-none-eabi-gcc
CMSIS=./CMSISV1.4
ST=./STM32F4xx_StdPeriph_DriverV1.4
USB_LIB=./usb_lib
#============================================================================#

CFLAGS_INCLUDE=-I. \
	-I$(CMSIS)/Include\
	-I$(CMSIS)/Device/ST/STM32F4xx/Include \
	-I$(ST)/inc \
	-I$(USB_LIB) \
	-I$(USB_LIB)/usb_hid_device


CFLAGS_DEFINE= \
        -D USE_STDPERIPH_DRIVER \
        -D STM32F429_439xx
        -D __FPU_PRESENT=1 \
        -D ARM_MATH_CM4 \
        -D __FPU_USED=1 \
		-U printf -D printf=printf_base

        #__CC_ARM
CFLAGS_OPTIMIZE= \
	-O2
CFLAGS_NEW_LIB_NANO= \
	--specs=nano.specs --specs=nosys.specs  -u _printf_float
CFLAGS_WARNING= \
	-Wall \
	-Wextra \
	-Wdouble-promotion \
	-Wshadow \
	-Werror=array-bounds \
	-Wfatal-errors \
	-Wmissing-prototypes \
	-Wbad-function-cast  \
	-Wstrict-prototypes \
	-Wmissing-parameter-type

ARCH_FLAGS=-mlittle-endian -mthumb -mcpu=cortex-m4 \
	-mfpu=fpv4-sp-d16 -mfloat-abi=hard

CFLAGS=-g $(ARCH_FLAGS)\
	${CFLAGS_INCLUDE} ${CFLAGS_DEFINE} \
	${CFLAGS_WARNING}


LDFLAGS +=$(CFLAGS_NEW_LIB_NANO) --static -Wl,--gc-sections

LDFLAGS +=-T stm32f429zi_flash.ld
LDLIBS +=-Wl,--start-group -lm -Wl,--end-group

#============================================================================#

STARTUP=./startup_stm32f429_439xx.o

OBJS=	./system_stm32f4xx.o \
	    $(ST)/src/misc.o \
        $(ST)/src/stm32f4xx_rcc.o \
        $(ST)/src/stm32f4xx_dma.o \
        $(ST)/src/stm32f4xx_flash.o \
        $(ST)/src/stm32f4xx_gpio.o \
        $(ST)/src/stm32f4xx_usart.o \
        $(ST)/src/stm32f4xx_adc.o \
        $(ST)/src/stm32f4xx_tim.o \
        $(ST)/src/stm32f4xx_exti.o \
        $(USB_LIB)/tm_stm32f4_usb_hid_device.o\
        $(USB_LIB)/tm_stm32f4_disco.o\
        $(USB_LIB)/tm_stm32f4_delay.o\
        $(USB_LIB)/usb_hid_device/usb_bsp.o\
        $(USB_LIB)/usb_hid_device/usb_core.o\
        $(USB_LIB)/usb_hid_device/usb_dcd.o\
        $(USB_LIB)/usb_hid_device/usb_dcd_int.o\
        $(USB_LIB)/usb_hid_device/usbd_core.o\
        $(USB_LIB)/usb_hid_device/usbd_desc.o\
        $(USB_LIB)/usb_hid_device/usbd_ioreq.o\
        $(USB_LIB)/usb_hid_device/usbd_usr.o\
        $(USB_LIB)/usb_hid_device/usbd_req.o\
        $(USB_LIB)/usb_hid_device/usbd_hid_core.o\
        ./stm32f4xx_it.o \
        ./main.o \
        $(STARTUP) 
        
#Make all
all:$(BIN_IMAGE)

$(BIN_IMAGE):$(EXECUTABLE)
	@$(OBJCOPY) -O binary $^ $@
	@echo 'OBJCOPY $(BIN_IMAGE)'

$(EXECUTABLE): $(OBJS)
	@$(LD) $(LDFLAGS) $(ARCH_FLAGS) $(OBJS) $(LDLIBS) -o $@ 
	@echo 'LD $(EXECUTABLE)'

%.o: %.c
	@$(CC) $(CFLAGS) -c $< -o $@
	@echo 'CC $<'

%.o: %.s
	@$(CC) $(CFLAGS) -c $< -o $@
	@echo 'CC $<'

PC_SIM:$(TEST_EXE)

$(TEST_EXE):$(HOST_SRC)
	$(HOST_CC) $(HOST_CFLAG) $^ -o $@
#Make clean
clean:
	rm -rf $(STARTUP_OBJ)
	rm -rf $(EXECUTABLE)
	rm -rf $(BIN_IMAGE)
	rm -f $(OBJS)

#Make flash
flash:
	st-flash write $(BIN_IMAGE) 0x8000000

#Make openocd
openocd: flash
	openocd -f ../debug/openocd.cfg

#Make cgdb
cgdb:
	cgdb -d $(GDB) -x ./st_util_init.gdb

#Make gdbtui
gdbtui:
	$(GDB) -tui -x ../st_util_init.gdb
#Make gdbauto
gdbauto: cgdb

flash_bmp:
	$(GDB) firmware.elf -x ./gdb_black_magic.gdb
cgdb_bmp: 
	cgdb -d $(GDB) firmware.elf -x ./bmp_gdbinit.gdb
flash_openocd:
	openocd -f interface/stlink-v2.cfg \
	-f target/stm32f4x_stlink.cfg \
	-c "init" \
	-c "reset init" \
	-c "halt" \
	-c "flash write_image erase $(PROJECT).elf" \
	-c "verify_image $(PROJECT).elf" \
	-c "reset run" -c shutdown
#automatically formate
astyle: 
	astyle -r --exclude=lib  *.c *.h
#============================================================================#

.PHONY:all clean flash openocd gdbauto gdbtui cgdb astyle
