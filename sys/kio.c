#include "kio.h"
#include "ftools.h"
#include "display/80x25.h"

void putc(char c)
{
	if (c < 32 || c == 127)
	{
		switch (c)
		{
			case CHAR_LF:
				__x = 0;
				++__y;
				c = 0;
				break;
			case CHAR_CR:
				__x = 0;
				c = 0;
				break;
			case CHAR_BS:
				--__x;
				c = 0;
				unsigned char *video = (unsigned char *) VIDEO_TEXT_BUFFER;
				video += 2 * (__y * COLUMNS + __x);
				*video = c;
				*(video + 1) = ATTRIBUTE_BYTE;
				break;
			default:
				c = CHAR_NON_PRINTABLE;
				break;
		}
	}
	
	if (c) 
	{		
		unsigned char *video = (unsigned char *) VIDEO_TEXT_BUFFER;
		
		video += 2 * (__y * COLUMNS + __x);
		
		*video = c;
		*(video + 1) = ATTRIBUTE_BYTE;
		
		++__x;
		c = 0;
	}
	
	if (__x >= COLUMNS) { __x = 0; ++__y; }
	//if (__y >= ROWS) { scroll_down(); --__y = 0; }
	if (__y >= ROWS) { __y = 0; }
	
}

void puts(const char *str)
{
	if (str == NULL) return;
	while (*str)
	{
		putc(*str++);
	}
	putc(CHAR_LF);
}

void printf(const char *format, ...)
{
	char **args = (char **) &format;
	++args;
	char c;
	int blen = 500;
	char buffer[500];
	buffer[0] = ' ';
	
	while (*format != 0)
	{
		c = *format++;
		if (c == '%')
		{
			c = *format++;
			switch(c)
			{
				case 'b':
					itoa(*((int *) args), buffer, blen, 2);
					clb(buffer, blen);
					++args;
				break;
				case 'd':
					itoa(*((int *) args), buffer, blen, 10);
					clb(buffer, blen);
					++args;
				break;
				case 'o':
					itoa(*((int *) args), buffer, blen, 8);
					clb(buffer, blen);
					++args;
				break;
				case 'x':
					itoa(*((int *) args), buffer, blen, 16);
					clb(buffer, blen);
					++args;
				break;
				case 'X':
					itoa(*((int *) args), buffer, blen, 17);
					clb(buffer, blen);
					++args;
				break;
				case 's':
					puts(*args);
					++args;
				break;
				case '%':
					putc('%');
				break;
			}
		}
		else
		{
			putc(c);
		}
	}
}