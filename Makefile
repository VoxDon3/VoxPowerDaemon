SDK_BIN = ../ps5-payload-sdk/bin
SDK_TARGET = ../ps5-payload-sdk/target
SDK_LDSCRIPTS = ../ps5-payload-sdk/ldscripts

export PATH := $(PATH):$(realpath $(SDK_BIN))

CC = $(SDK_BIN)/prospero-clang

CFLAGS = -target x86_64-scei-ps4-elf -I$(SDK_TARGET)/include -fPIC -ffreestanding
LDFLAGS = -target x86_64-scei-ps4-elf -T $(SDK_LDSCRIPTS)/elf_x86_64.x -nostdlib

all: VoxPowerDaemon.elf

VoxPowerDaemon.elf: main.o
	$(CC) $(LDFLAGS) -o $@ $^

main.o: main.c
	$(CC) $(CFLAGS) -c -o $@ $<

clean:
	rm -f *.o *.elf

