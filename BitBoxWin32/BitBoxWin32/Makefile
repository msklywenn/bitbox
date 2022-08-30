BUILD_DIR=build
include $(N64_INST)/include/n64.mk

CFLAGS += -DN64
CXXFLAGS += -DN64

src = *.cpp *.c
assets_png = $(wildcard assets/*.png)

assets_conv = $(addprefix filesystem/,$(notdir $(assets_png:%.png=%.sprite)))

MKSPRITE_FLAGS ?=

all: bitbox.z64

filesystem/%.sprite: assets/%.png
	@mkdir -p $(dir $@)
	@echo "    [SPRITE] $@"
	@$(N64_MKSPRITE) $(MKSPRITE_FLAGS) "$<" "$@"

filesystem/circle.sprite: MKSPRITE_FLAGS=16 1 1
filesystem/diamond.sprite: MKSPRITE_FLAGS=16 1 1
filesystem/pentagon.sprite: MKSPRITE_FLAGS=16 1 1
filesystem/triangle.sprite: MKSPRITE_FLAGS=16 1 1

$(BUILD_DIR)/bitbox.dfs: $(assets_conv)
$(BUILD_DIR)/bitbox.elf: $(src:%.c=$(BUILD_DIR)/%.o)

bitbox.z64: N64_ROM_TITLE="Bitbox"

clean:
	rm -rf $(BUILD_DIR) bitbox.z64

-include $(wildcard $(BUILD_DIR)/*.d)

.PHONY: all clean
