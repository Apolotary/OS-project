global load_idt

load_idt:
	mov eax, [esp + 4]
	lidt [eax]
	jmp 0x08: .set_cs
	
	.set_cs:
	ret
