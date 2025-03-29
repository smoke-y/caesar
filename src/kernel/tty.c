#include "../c.h"
#include "../libc/libc.h"
#include "tty.h"

static u16* tty_addr = ((u16*)TTY_ADDR);

u8 createColor(vgaColor fg, vgaColor bg){ return fg | bg << 4;};
void setColor(u8 col){ tty->col = col << 8;};

void cleartty(){
	u16 col = tty->col;
	tty->off = 0;
	for(u32 y=0; y<VGA_HEIGHT; y++){
		for(u32 x=0; x<VGA_WIDTH; x++){
			tty_addr[x + y*VGA_WIDTH] = (u16)' ' | col;
		};
	};
};

void ttyInit(void *buff, const vgaColor fg, const vgaColor bg){
	tty->buff = buff;
	tty->off = 0;
	u8 col = createColor(fg, bg);
	setColor(col);
	u16 shiftCol = (u16)col << 8;
	cleartty();	
};

void putChar(const char c){
	if(c == '\n'){
		tty->y += 1;
		tty->x = 0;
		return;
	};
	tty_addr[tty->x + tty->y*VGA_WIDTH] = c | tty->col;
	tty->x++;
	if(tty->x == VGA_WIDTH){
		tty->x = 0;
		tty->y += 1;
	};
};

void putCharBuff(char c){
	tty->buff[tty->off++] = c;
};
void kprint(char *fmt, ...){
    const u32 len = strlen(fmt);
    va_list args;
    va_start(args, fmt);
    u32 count = tty->off;
    for(u32 x=0; x<len; x++){
        if(fmt[x] == '%'){
            switch(fmt[++x]){
                case '%':
                    putCharBuff('%');
                    break;
                case 'd':{
                    s32 num = va_arg(args, s32);
                    if(num == 0){
                        putCharBuff('0');
                        break;
                    };
                    if(num < 0) putCharBuff('-');
                    u8 arr[20];
                    u32 i=0;
                    while(num > 0){
                        arr[i++] = (num % 10) + '0';
                        num /= 10;
                    };
                    while(i > 0) putCharBuff(arr[--i]);
                }break;
                case 'p':{
                    putCharBuff('0');
                    putCharBuff('x');
                    s64 num = va_arg(args, s64);
                    if(num == 0){
                        putCharBuff('0');
                        break;
                    };
                    u8 arr[20];
                    u32 i = 0;
                    while(num != 0){
                        u8 temp = num % 16;
                        if(temp < 10) temp += '0';
                        else temp += '7';
                        arr[i++] = temp;
                        num /= 16;
                    };
                    while(i > 0) putCharBuff(arr[--i]);
                }break;
                case 's':{
                    char *str = va_arg(args, char*);
                    u32 stringLen = strlen(str);
                    for(u32 i=0; i<stringLen; i++) putCharBuff(str[i]);
                }break;
            };
        }else if(fmt[x] == '\\'){
            switch(fmt[++x]){
                case 'n':
                    putCharBuff('\n');
                    break;
            };
        }else putCharBuff(fmt[x]);
    };
    va_end(args);
    count = tty->off - count;
    for(u32 x=0; x<count; x++) putChar(tty->buff[tty->off - count + x]);
};
