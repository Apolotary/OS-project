#include "ftools.h"
#include "kio.h"

void rprint (char* buffer, unsigned int counter)
{
	putc(buffer[0]);
	--counter;
	while (counter >= 1)
	{
		putc(buffer[counter]);
		--counter;
	}
}

void clb(char* buffer, int bsize)
{
	--bsize;
	while (bsize >= 0)
	{
		buffer[bsize] = NULL;
		--bsize;
	}
	buffer[0] = ' ';
}

void itoa (int num, char* buffer, size_t buffer_len, int base)
{
	unsigned int counter = 1;
	if (num < 0)
	{
		buffer[0] = '-';
		num *= -1;
	}
	if (base == 10)
	{
		
		if (num < 0)
		{
			buffer[0] = '-';
			num *= -1;
		}
		
		while (num != 0 && counter <= buffer_len)
		{
			int temp = num % base;
			num = num / base ;
			buffer[counter] = '0' + temp;
			++counter;
		}		
	}
	else if (base == 2 || base == 8)
	{
		while (num != 0 && counter <= buffer_len)
		{
			int temp = num % base;
			num = num / base ;
			buffer[counter] = '0' + temp;
			++counter;
		}
	}
	else if (base == 16)
	{
		char hex[16] = "0123456789abcdef";
		while (num != 0 && counter <= buffer_len)
		{
			int temp = num % base;
			num = num / base ;
			buffer[counter] = hex[temp];
			++counter;
		}	
	}
	else if (base == 17)
	{
		--base;
		char HEX[16] = "0123456789ABCDEF";
		while (num != 0 && counter <= buffer_len)
		{
			int temp = num % base;
			num = num / base ;
			buffer[counter] = HEX[temp];
			++counter;
		}
	}
	rprint (buffer, counter);
}