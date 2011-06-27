#ifndef _FTOOLS_H_
#define _FTOOLS_H_

#include "kio.h"

typedef unsigned int size_t;

void rprint (char* buffer, unsigned int counter);

void itoa (int num, char* buffer, size_t buffer_len, int base);

void clb (char* buffer, int bsize);

void rprint (char* buffer, unsigned int counter);

#endif