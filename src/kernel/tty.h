#pragma once

#define TTY_ADDR   0xB8000
#define VGA_HEIGHT 80
#define VGA_WIDTH  25

#include "../c.h"

STRUCT{
	u16 x;
	u16 y;
	u16 col;
} TTY;
ENUM{
	VGA_COLOR_BLACK = 0,
	VGA_COLOR_BLUE = 1,
	VGA_COLOR_GREEN = 2,
	VGA_COLOR_CYAN = 3,
	VGA_COLOR_RED = 4,
	VGA_COLOR_MAGENTA = 5,
	VGA_COLOR_BROWN = 6,
	VGA_COLOR_LIGHT_GREY = 7,
	VGA_COLOR_DARK_GREY = 8,
	VGA_COLOR_LIGHT_BLUE = 9,
	VGA_COLOR_LIGHT_GREEN = 10,
	VGA_COLOR_LIGHT_CYAN = 11,
	VGA_COLOR_LIGHT_RED = 12,
	VGA_COLOR_LIGHT_MAGENTA = 13,
	VGA_COLOR_LIGHT_BROWN = 14,
	VGA_COLOR_WHITE = 15,
} vgaColor;

void cleartty(TTY *tty);
void ttyInit(const vgaColor fg, const vgaColor bg, TTY *tty);
void putChar(const char c, TTY *tty);
void setColor(u8 col, TTY *tty);
u8   createColor(vgaColor fg, vgaColor bg); 
