#include "kdisplay.h"
#include "80x25.h"
void kcls(void)
{
	unsigned char *video, *end; 
	video = (unsigned char *) VIDEO_TEXT_BUFFER;
	end = video + COLUMNS * ROWS * 2 - 1;
	
	for (;video <= end; ++video) *video = 0;
	
	__x = __y = 0;
}