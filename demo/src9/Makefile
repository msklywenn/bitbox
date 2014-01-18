export PATH := $(DEVKITARM)/bin:$(PATH)

AS = arm-eabi-gcc
CC = arm-eabi-gcc
LD = arm-eabi-ld
OBJCOPY = arm-eabi-objcopy

ARCH = -mthumb -mthumb-interwork
CFLAGS = -Wall -Os -DARM9 -march=armv5te -mtune=arm946e-s
CFLAGS += -nostdlib -nodefaultlibs -nostartfiles -fomit-frame-pointer
INCLUDE = -Isrc -I$(DEVKITPRO)/libnds/include
ASFLAGS = -x assembler-with-cpp -I src
LDFLAGS = -mno-fpu -specs=ds_arm9.specs
LDFLAGS += -nostdlib -nodefaultlibs -nostartfiles
LDFLAGS += -Wl,-Map,arm9.map

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
