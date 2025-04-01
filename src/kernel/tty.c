#include "../c.h"
#include "../libc/libc.h"
#include "pageAlloc.h"
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
	tty->x = 0;
	u8 col = createColor(fg, bg);
	setColor(col);
	memset(buff, (u16)' ' | tty->col, PAGE_SIZE);
	cleartty();
};
void putChar(const char c) {
    if (c == '\n' || tty->x >= VGA_WIDTH) {
        tty->x = 0;
        
        for(u32 y = 0; y < VGA_HEIGHT - 1; y++){
            for(u32 x = 0; x < VGA_WIDTH; x++){
                u32 dest = x + y * VGA_WIDTH;
                u32 src = x + (y + 1) * VGA_WIDTH;
                tty_addr[dest] = tty_addr[src];
            }
        }
        
        for(u32 x = 0; x < VGA_WIDTH; x++){
            u32 idx = x + (VGA_HEIGHT - 1) * VGA_WIDTH;
            tty_addr[idx] = ' ' | tty->col;
        }
    }else{
        tty_addr[tty->x + (VGA_HEIGHT - 1) * VGA_WIDTH] = c | tty->col;
        tty->x++;
    }
};

void putCharBuff(char c){
	tty->buff[tty->off] = (u16)c | tty->col;
	tty->off = (tty->off + 1) % PAGE_SIZE;
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
                    s64 num = va_arg(args, s32);
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
    while(count != tty->off){
	    putChar(tty->buff[count]);
	    count = (count+1) % PAGE_SIZE;
    };
};
