#include "../c.h"
#include "../libc/libc.h"
#include "tty.h"

static u16* tty_addr = ((u16*)TTY_ADDR);

u8 createColor(vgaColor fg, vgaColor bg){ return fg | bg << 4;};
void setColor(u8 col, TTY *tty){ tty->col = col << 8;};

void cleartty(TTY *tty){
	u16 col = tty->col;
	for(u32 y=0; y<VGA_HEIGHT; y++){
		for(u32 x=0; x<VGA_WIDTH; x++){
			tty_addr[x + y*VGA_WIDTH] = (u16)' ' | col;
		};
	};
};

void ttyInit(const vgaColor fg, const vgaColor bg, TTY *tty){
	u8 col = createColor(fg, bg);
	setColor(col, tty);
	u16 shiftCol = (u16)col << 8;
	cleartty(tty);	
};

void putChar(const char c, TTY *tty){
	if(c == '\n'){
		tty->y += 1;
		return;
	};
	tty_addr[tty->x + tty->y*VGA_WIDTH] = c | tty->col;
	tty->x++;
	if(tty->x == VGA_WIDTH){
		tty->x = 0;
		tty->y += 1;
	};
};
