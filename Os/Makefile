# Makefile for bootsector(Floppy IMG) and loader

ASM		= nasm
ASMBFLAGS	= -I boot/inc/
ASMKFLAGS	= -I include/ -g -f elf32 -F stabs
LD		= ld -g
LDFLAGS		= -m elf_i386 -Ttext 0x30400
CC		= gcc
CFLAGS		= -m32 -c -g -fno-builtin -I include -Wall

TARGET		= boot/XXX.IMG boot/loader.bin kernel/kernel.bin

OBJS		= kernel/kernel.o kernel/start.o kernel/i8259.o kernel/global.o kernel/protect.o kernel/main.o kernel/clock.o kernel/syscall.o kernel/proc.o \
		  kernel/keyboard.o kernel/tty.o kernel/console.o kernel/printf.o\
		  lib/klib.o lib/string.o  lib/klibasm.o

.PHONY: 	clean image mount

all:		clean image add

clean:		
	umount ./mnt || true
	rm -f $(TARGET) $(OBJS)

image:		$(TARGET)


boot/XXX.IMG: boot/bootsector.asm boot/inc/loader.inc boot/inc/fat12hdr.inc boot/inc/disp.inc
	$(ASM) $(ASMBFLAGS) -o $@ $<

boot/loader.bin: boot/loader.asm boot/inc/loader.inc boot/inc/fat12hdr.inc boot/inc/protect.inc boot/inc/./disp.inc boot/inc/lib.inc
	$(ASM) $(ASMBFLAGS) -o $@ $<

kernel/kernel.bin: $(OBJS)
	$(LD) $(LDFLAGS) -o $@ $(OBJS)

kernel/kernel.o: kernel/kernel.asm 
	$(ASM) $(ASMKFLAGS) -o $@ $<

kernel/syscall.o: kernel/syscall.asm
	$(ASM) $(ASMKFLAGS) -o $@ $<

kernel/global.o: kernel/global.c include/type.h include/const.h \
		  include/protect.h include/proto.h include/global.h
	$(CC) $(CFLAGS) -o $@ $<

kernel/i8259.o: kernel/i8259.c include/type.h include/const.h include/protect.h \
		 include/proto.h
	$(CC) $(CFLAGS) -o $@ $<

kernel/start.o: kernel/start.c include/type.h include/const.h include/protect.h \
		 include/proto.h include/string.h include/global.h
	$(CC) $(CFLAGS) -o $@ $<

kernel/protect.o: kernel/protect.c include/type.h include/const.h \
	   include/protect.h include/global.h include/proto.h
	$(CC) $(CFLAGS) -o $@ $<

kernel/clock.o: kernel/clock.c include/type.h include/const.h include/global.h include/type.h
	$(CC) $(CFLAGS) -o $@ $<

kernel/proc.o: kernel/proc.c include/proto.h
	$(CC) $(CFLAGS) -o $@ $<

kernel/keyboard.o: kernel/keyboard.c include/proto.h
	$(CC) $(CFLAGS) -o $@ $<

kernel/tty.o:kernel/tty.c include/type.h include/proto.h include/type.h
	$(CC) $(CFLAGS) -o $@ $<

kernel/console.o: kernel/console.c
	$(CC) $(CFLAGS) -o $@ $<

lib/klibasm.o: lib/klibasm.asm
	$(ASM) $(ASMKFLAGS) -o $@ $<

lib/klib.o: lib/klib.c
	$(CC) $(CFLAGS) -o $@ $<

lib/string.o: lib/string.asm
	$(ASM) $(ASMKFLAGS) -o $@ $<


add: $(TARGET)
	mount -t vfat boot/XXX.IMG mnt
#	strip kernel/kernel.bin -o kernel/kernel.bin.stripped
#	cp boot/loader.bin  mnt
#	cp kernel/kernel.bin.stripped mnt/kernel.bin
	cp boot/loader.bin kernel/kernel.bin mnt
	nm -a kernel/kernel.bin| awk '{print $$1,$$3}' > kernel.sym

	sync

