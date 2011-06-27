#include "pic.h"

void init_pic(void)
{
	//first control word
	outb(0x20, 0x11); //сигнал инициализации
	outb(0xA0, 0x11); 
		
	outb(0x21, 0x20);//32 
	outb(0xA1, 0x28);// 40
	
	outb(0x21, 0x04);//флаги для архитектуры
	outb(0xA1, 0x02);
		
	outb(0x21, 0x1);// 
	outb(0xA1, 0x1);// 
	
	//mask
	outb(0x21, 0x0);// 
	outb(0xA1, 0x0);// 
	
	
	
}

void reset_master_pic(void) // command port 20 dataport 21
{
	outb(0x20, 0x20); // на оммандный порт 20 передать сигнал 20 - end of interrupt
}

void reset_slave_pic(void)
{
	outb(0xA0, 0x20);
}