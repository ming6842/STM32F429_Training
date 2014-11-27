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
CMSIS=../Libraries/CMSIS
ST=../Libraries/STM32F4xx_StdPeriph_Driver
STM32F429_LIB = ../STM32F429I-Discovery
COMMON = ../Common
#============================================================================#

CFLAGS_INCLUDE=-I. \
	-I$(CMSIS)/Include\
	-I$(CMSIS)/Device/ST/STM32F4xx/Include\
	-I$(ST)/inc  \
	-I$(STM32F429_LIB) \
	-I$(COMMON)

CFLAGS_DEFINE= \
        -D USE_STDPERIPH_DRIVER \
        -D USE_STM32F429I_DISCO \
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
        $(ST)/src/stm32f4xx_dma2d.o \
        $(ST)/src/stm32f4xx_flash.o \
        $(ST)/src/stm32f4xx_gpio.o \
        $(ST)/src/stm32f4xx_ltdc.o \
        $(ST)/src/stm32f4xx_sai.o \
        $(ST)/src/stm32f4xx_fmc.o \
        $(ST)/src/stm32f4xx_spi.o \
        ../Common/fonts.o \
        $(STM32F429_LIB)/stm32f429i_discovery_lcd.o \
        $(STM32F429_LIB)/stm32f429i_discovery_sdram.o \
        ../Common/lcd_log.o \
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
#flash:
#	st-flash write $(BIN_IMAGE) 0x8000000

#Make openocd
#openocd: flash
#	openocd -f ../debug/openocd.cfg

#Make cgdb
cgdb:
	cgdb -d $(GDB) -x ./st_util_init.gdb

#Make gdbtui
gdbtui:
	$(GDB) -tui -x ../st_util_init.gdb
#Make gdbauto
gdbauto: cgdb

#flash_bmp:
#	$(GDB) firmware.elf -x ./gdb_black_magic.gdb
cgdb_bmp: 
	cgdb -d $(GDB) firmware.elf -x ./bmp_gdbinit.gdb
flash_openocd:
	openocd -f interface/stlink-v2.cfg \
	-c "transport select hla_swd" \
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

.PHONY:all clean flash_openocd openocd gdbauto gdbtui cgdb astyle
