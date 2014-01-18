export PATH := $(DEVKITARM)/bin:$(PATH)

AS = arm-eabi-gcc
CC = arm-eabi-gcc
LD = arm-eabi-ld
OBJCOPY = arm-eabi-objcopy

ARCH = -mthumb -mthumb-interwork
CFLAGS = -g -Wall -DARM7 -mcpu=arm7tdmi -mtune=arm7tdmi
CFLAGS += -nostartfiles -nostdlib -nodefautlibs
INCLUDE = -Isrc -I$(DEVKITPRO)/libnds/include
LDFLAGS = -g -mno-fpu -specs=ds_arm7.specs
LDFLAGS += -nostartfiles -nostdlib -nodefaultlibs
LDFLAGS += -Wl,-Map,arm7.map
ASFLAGS = -x assembler-with-cpp -I src

ASMFILES = $(wildcard src/*.s)
CFILES = $(wildcard src/*.c)
OBJS = $(CFILES:.c=.o) $(ASMFILES:.s=.o)

#TODO : add auto asm dump
.c.o: %.c
	@echo Compiling $<
	@$(CC) $(ARCH) $(CFLAGS) $(INCLUDE) -o $@ -c $<

.s.o: %.s
	@echo Assembling $<
	@$(AS) $(ASFLAGS) -o $@ -c $<

bin: elf
	@$(OBJCOPY) -O binary $< $@

elf: $(OBJS)
	@echo -e '\e[1;33mLinking...\e[0m'
	@$(CC) $(ARCH) $(LDFLAGS) -o $@ $(OBJS)

clean:
	rm -f elf bin $(OBJS)
