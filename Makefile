BUILD   = build
SRCS_C  = $(wildcard src/*.c)
SRCS_S  = $(wildcard src/*.s)
OBJS    = $(SRCS_C:src/%.c=$(BUILD)/%.o) $(SRCS_S:src/%.s=$(BUILD)/%.o)
DEPS    = $(SRCS_C:src/%.c=$(BUILD)/%.d)

CC      = gcc
CFLAGS  = -m32 -nostdlib -nostdinc -fno-builtin -fno-stack-protector \
          -nostartfiles -nodefaultlibs -Wall -Wextra -Werror -c      \
          -Iinclude -MMD -MP -O0 -std=c11
LDFLAGS = -T src/link.ld -melf_i386
AS      = nasm
ASFLAGS = -f elf

all: kernel.elf

kernel.elf: $(OBJS)
	ld $(LDFLAGS) $^ -o $@

os.iso: kernel.elf
	cp kernel.elf iso/boot/kernel.elf
	genisoimage -R                      \
		-b boot/grub/stage2_eltorito    \
		-no-emul-boot                   \
		-boot-load-size 4               \
		-A os                           \
		-input-charset utf8             \
		-quiet                          \
		-boot-info-table                \
		-o os.iso                       \
		iso

run: os.iso
	./packages/bochs-3.0/bochs -f bochsrc.txt -q

$(BUILD)/%.o: src/%.c
	mkdir -p $(BUILD)
	$(CC) $(CFLAGS)  $< -o $@

$(BUILD)/%.o: src/%.s
	mkdir -p $(BUILD)
	$(AS) $(ASFLAGS) $< -o $@

clean:
	rm -rf $(BUILD) kernel.elf os.iso

-include $(DEPS)

.PHONY: all run clean
