global start
extern kmain

MAGIC equ 0x1BADB002

MEMINFO equ 1<<1
VIDMODEINFO equ 1<<2

FLAGS equ MEMINFO | VIDMODEINFO

CHECKSUM equ -(MAGIC+FLAGS)

STACK_SIZE equ 0x4000

section .text
align 4
	dd MAGIC
	dd FLAGS
	dd CHECKSUM
	
start:
	mov esp, stack+STACK_SIZE
	
	push ebx  ; Multiboot structure
	push eax  ; magic number
	
	call kmain
	
	cli
	halt:
		hlt
		jmp halt
	
section .bss 
align 4
	stack:
		resb STACK_SIZE