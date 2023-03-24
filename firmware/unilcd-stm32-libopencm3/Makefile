DEVICE          = stm32f103c8t6
OPENCM3_DIR     = libopencm3
OBJS            += stm32_delay.o unilcd.o unilcd-stm32.o

CFLAGS          += -Os -ggdb3
CPPFLAGS		+= -MD -DSTM32_LIBOPENCM3 -DF_CPU=48000000
LDFLAGS         += -static -nostartfiles 
LDLIBS          += -Wl,--start-group -lm -lc -lgcc -lnosys -Wl,--end-group 

include $(OPENCM3_DIR)/mk/genlink-config.mk
include $(OPENCM3_DIR)/mk/gcc-config.mk

.PHONY: clean all

all: unilcd.elf unilcd.hex

clean:
	$(Q)$(RM) -rf *.o *.d *.ld unilcd.hex unilcd.elf

size:
	$(SIZE) unilcd.elf

include $(OPENCM3_DIR)/mk/genlink-rules.mk
include $(OPENCM3_DIR)/mk/gcc-rules.mk