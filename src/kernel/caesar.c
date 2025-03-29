#include "../c.h"
#include "tty.h"
#include "caesar.h"

static Caesar caesar;

int caesar_main(){
	ttyInit(VGA_COLOR_WHITE, VGA_COLOR_BLACK, &caesar.tty);
	putChar('c', &caesar.tty);
	return 0;
};
