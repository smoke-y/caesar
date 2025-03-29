#pragma once

//Define C_LOG(fmt, ...) in source code

#ifdef DBG
#define DASS(x)	if(!x) C_LOG("\n%s(%d): asserion failed -> %s\n", __FILE_NAME__, __LINE__, #x)
#define HIT     C_LOG("\n%s(%d): HIT!\n", __FILE_NAME__, __LINE__);
#else
#define DASS(x)
#define HIT
#endif

//checks
#define SASS(x)         static_assert(x)
#define SASSM(x, msg)   static_assert(x, msg)
#define UNREACHABLE(x)  C_LOG("\n%s(%d): unreachable area reached\n")
//bit manipulation
#define SET_BIT(x, off)  x |=  (1 << (u32)off)
#define CLR_BIT(x, off)  x &= ~(1 << (u32)off) 
#define IS_BIT(x, off)   ((((u32)(x))>>((u32)off)) & 1)
//syntax sugar
#define STRUCT   typedef struct
#define ENUM     typedef enum
#define DIFFPTR  restrict

typedef unsigned char           u8;
typedef unsigned short          u16;
typedef unsigned int            u32;
typedef unsigned long long int  u64;
typedef signed char             s8;
typedef signed short            s16;
typedef signed int              s32;
typedef signed long long int    s64;
typedef float                   f32;
typedef double                  f64;
SASSM(sizeof(u8)  == 1 && sizeof(s8) == 1,  "u8/s8 is not 1 byte");
SASSM(sizeof(u16) == 2 && sizeof(s16) == 2, "u16/s16 is not 2 bytes");
SASSM(sizeof(u32) == 4 && sizeof(s32) == 4, "u32/s32 is not 4 bytes");
SASSM(sizeof(u64) == 8 && sizeof(s64) == 8, "u64/s64 is not 8 bytes");
SASSM(sizeof(f32) == 4, "f32 is not 4 bytes");
SASSM(sizeof(f64) == 8, "f64 is not 8 bytes");
typedef u8                      b8;
typedef u16                     b16;
typedef u32                     b32;
typedef u64                     b64;
