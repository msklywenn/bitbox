BUILD_DIR=build
include $(N64_INST)/include/n64.mk

N64_CFLAGS += -I n64

src = $(wildcard src/*.c) $(wildcard src/*.cpp) $(wildcard n64/*.cpp)

all: bitbox.z64

$(BUILD_DIR)/bitbox.elf: $(src:%.cpp=$(BUILD_DIR)/%.o) # $(src:%.c=$(BUILD_DIR)/%.o)

bitbox.z64: N64_ROM_TITLE="Bitbox"

clean:
	rm -rf $(BUILD_DIR) bitbox.z64

-include $(wildcard $(BUILD_DIR)/*.d)

.PHONY: all clean
