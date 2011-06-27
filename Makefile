# It's not a Zaku, boy! It's not a Zaku!
CC = i386-elf-gcc
CFLAGS = -g -Wall -Wextra -nostdlib -nodefaultlibs -nostartfiles

ASM = nasm
ASMFLAGS = -f elf -g

LD = i386-elf-ld
LDFLAGS = -T linker.ld

# Moon Prism Power, Make Up!
LOADER = loader
KERNEL = kernel

ASM_SOURCES = $(LOADER).asm \
              sys/isr_handler.asm \
              sys/tables/idt_handler.asm \
              sys/tables/gdt_handler.asm
C_SOURCES   = $(KERNEL).c \
	      sys/kio.c \
	      sys/ftools.c \
	      sys/display/kdisplay.c \
          sys/isr.c \
          sys/tables/idt.c \
          sys/tables/gdt.c \
          sys/memory/heap.c \
          sys/memory/paging.c \
          sys/memory/panic.c
ASM_OBJECTS = $(ASM_SOURCES:.asm=.o)
C_OBJECTS   = $(C_SOURCES:.c=.o)

.PHONY : all
all : $(KERNEL)

$(KERNEL) : $(ASM_OBJECTS) $(C_OBJECTS)
	$(LD) $(LDFLAGS) -o $@ $^

$(ASM_OBJECTS) : %.o : %.asm
	$(ASM) $(ASMFLAGS) -o $@ $<

$(C_OBJECTS) : %.o : %.c
	$(CC) $(CFLAGS) -o $@ -c $<

.PHONY : clean
clean :
	rm -f $(KERNEL) $(ASM_OBJECTS) $(C_OBJECTS)

