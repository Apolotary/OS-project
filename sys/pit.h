#ifndef _PIT_H_
#define _PIT_H_

#include "tables/lib/kint.h"
#include "kio.h"
#include "isr.h"

void init_pit(uint32_t frequency);

#endif