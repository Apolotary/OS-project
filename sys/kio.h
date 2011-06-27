#ifndef _KIO_H_
#define _KIO_H_

#include "display/kdisplay.h"
#include "ftools.h"

#define CHAR_LF 0x0A

#define CHAR_CR 0x0D

#define CHAR_NON_PRINTABLE 0x3F // '?'

#define CHAR_BS 0x08

#define NULL 0
void putc(char c);

void puts(const char *str);

void printf(const char *format, ...);

#endif