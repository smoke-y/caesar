#include "../c.h"

u32 strlen(const char *str){
	u32 x=0;
	while(str[x]) x++;
	return x;
};
