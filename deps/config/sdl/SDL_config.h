#ifndef _SDL_config_h
#define _SDL_config_h
#include "SDL_platform.h"

/* C datatypes */
#define SDL_HAS_64BIT_TYPE 1

/* Endianness */
#define SDL_BYTEORDER 1234

/* Useful headers */
#define HAVE_STDIO_H 1
#define HAVE_STDLIB_H 1
#define HAVE_STDARG_H 1
#define HAVE_STRING_H 1
#define HAVE_STDINT_H 1

/* C library functions */
#define HAVE_MALLOC
#define HAVE_CALLOC
#define HAVE_REALLOC
#define HAVE_FREE
#define HAVE_ALLOCA
#define HAVE_MEMSET
#define HAVE_MEMCPY
#define HAVE_MEMMOVE
#define HAVE_MEMCMP

/* Enable various drivers */
#define SDL_AUDIO_DRIVER_DUMMY 1
#define SDL_CDROM_DISABLED 1
#define SDL_JOYSTICK_DISABLED 1
#define SDL_LOADSO_DISABLED 1
#define SDL_THREAD_PTHREAD 1
#define SDL_TIMER_DUMMY 1
#define SDL_VIDEO_DRIVER_DUMMY 1

#endif /* _SDL_config_h */
