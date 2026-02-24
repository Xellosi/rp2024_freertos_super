PROJECT ?= blink_freertos
BUILD_DIR ?= build

SUPER_PROJECT_ROOT ?= $(abspath ../..)
PICO_SDK_PATH ?= $(SUPER_PROJECT_ROOT)/pico-sdk
FREERTOS_PATH ?= $(SUPER_PROJECT_ROOT)/FreeRTOS
PICOTOOL_DIR ?=

CMAKE ?= cmake

.PHONY: all configure build clean

all: build

configure:
	$(CMAKE) -S . -B $(BUILD_DIR) \
		-DPICO_BOARD=pico \
		-DSUPER_PROJECT_ROOT=$(SUPER_PROJECT_ROOT) \
		-DPICO_SDK_PATH=$(PICO_SDK_PATH) \
		-DFREERTOS_PATH=$(FREERTOS_PATH) \
		$(if $(PICOTOOL_DIR),-Dpicotool_DIR=$(PICOTOOL_DIR),)

build: configure
	$(CMAKE) --build $(BUILD_DIR) -j

clean:
	rm -rf $(BUILD_DIR)
