/*
# _____     ___ ____     ___ ____
#  ____|   |    ____|   |        | |____|
# |     ___|   |____ ___|    ____| |    \    PS2DEV Open Source Project.
#-----------------------------------------------------------------------
# Copyright (c) 2003 Marcus R. Brown <mrbrown@0xd6.org>
# Licenced under Academic Free License version 2.0
# Review ps2sdk README & LICENSE files for further details.
*/

/**
 * @file
 * Standard C Library I/O.
 */

#ifndef __STDIO_H__
#define __STDIO_H__

#include <stdarg.h>
#include <irx.h>

int printf(const char *format, ...);
int getchar(void);
int putchar(int c);
int puts(const char *s);
char *gets(char *s);
int fdprintf(int fd, const char *format, ...);
int fdgetc(int fd);
int fdputc(int c, int fd);
int fdputs(const char *s, int fd);
char *fdgets(char *buf, int fd);
int vfdprintf(int fd, const char *format, va_list ap);

#endif /* __STDIO_H__ */
