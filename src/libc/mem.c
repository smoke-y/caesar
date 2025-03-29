#include "../c.h"

void memset(void *ptr, s16 value, u64 size){
	size = size / sizeof(s16);
	s16 *mem = (s16*)ptr;
	for(u64 x=0; x<size; x++) mem[x] = value;
};
