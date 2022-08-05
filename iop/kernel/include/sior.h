/*
# _____     ___ ____     ___ ____
#  ____|   |    ____|   |        | |____|
# |     ___|   |____ ___|    ____| |    \    PS2DEV Open Source Project.
#-----------------------------------------------------------------------
# Copyright 2001-2004, ps2dev - http://www.ps2dev.org
# Licenced under Academic Free License version 2.0
# Review ps2sdk README & LICENSE files for further details.
*/

/**
 * @file
 * IOP-side SIO remote service.
 */

#ifndef __SIOR_H__
#define __SIOR_H__

#include <stdarg.h>
#include <irx.h>

#include <sior-common.h>

void sio_init(u32 baudrate, u8 lcr_ueps, u8 lcr_upen, u8 lcr_usbl, u8 lcr_umode);
int sio_putc(int c);
int sio_getc(void);
int sio_getc_block(void);

size_t sio_write(const char *buf, size_t size);
size_t sio_read(char *buf, size_t size);

int sio_puts(const char *str);
int sio_putsn(const char *str); // no newline for this one
char *sio_gets(char *str);

void sio_flush(void);

int sio_printf(const char *format, ...);
int sio_vprintf(const char *format, va_list);

#endif /* __SIOR_H__ */
