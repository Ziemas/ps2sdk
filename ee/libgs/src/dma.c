/*
# _____     ___ ____     ___ ____
#  ____|   |    ____|   |        | |____|
# |     ___|   |____ ___|    ____| |    \    PS2DEV Open Source Project.
#-----------------------------------------------------------------------
# (c) 2009 Lion
# Licenced under Academic Free License version 2.0
# Review ps2sdk README & LICENSE files for further details.
*/

#include <errno.h>
#include <stdio.h>
#include <kernel.h>
#include <libgs.h>

#include "internal.h"

#define BIT(x)                 (1UL << (x))
#define MASK(x)                (BIT(x) - 1)
#define GENMASK(msb, lsb)      ((BIT((msb + 1) - (lsb)) - 1) << (lsb))
#define _FIELD_LSB(field)      ((field) & ~(field - 1))
#define FIELD_PREP(field, val) ((val) * (_FIELD_LSB(field)))
#define FIELD_GET(field, val)  (((val) & (field)) / _FIELD_LSB(field))

// Miscellaneous

/** GIF Channel Control Register */
#define gif_chcr 0x1000a000
/** Transfer Address Register */
#define gif_madr 0x1000a010
/** Transfer Size Register (in qwords) */
#define gif_qwc  0x1000a020
#define gif_tadr 0x1000a030

#define DMA_TAG_REFE 0x00
#define DMA_TAG_CNT  0x01
#define DMA_TAG_NEXT 0x02
#define DMA_TAG_REF  0x03
#define DMA_TAG_REFS 0x04
#define DMA_TAG_CALL 0x05
#define DMA_TAG_RET  0x06
#define DMA_TAG_END  0x07

#define CHCR_DIR BIT(0)
#define CHCR_MOD GENMASK(3, 2)
#define CHCR_ASP GENMASK(5, 4)
#define CHCR_TTE BIT(6)
#define CHCR_TIE BIT(7)
#define CHCR_STR BIT(8)
#define CHCR_TAG GENMASK(31, 16)

void GsDmaInit(void)
{
    /* This appears to have been based on code from Sony that initializes DMA channels 0-9, in bulk.
           Reset/init DMA CH 2 (GIF) only. */
    __asm__(
        "li	$2,0x1000A000	\n"
        "sw	$0,0x80($2)		\n" // D2_SADR = 0. Documented to not exist, but is done.
        "sw	$0,0($2)		\n" // D2_CHCR = 0
        "sw	$0,0x30($2)		\n" // D2_TADR = 0
        "sw	$0,0x10($2)		\n" // D2_MADR = 0
        "sw	$0,0x50($2)		\n" // D2_ASR1 = 0
        "sw	$0,0x40($2)		\n" // D2_ASR0 = 0
        "li	$2,0xFF1F		\n" // Clear all interrupt status under D_STAT, other than SIF0, SIF1 & SIF2.
        "sw	$2,0x1000E010	\n"
        "lw	$2,0x1000E010	\n"
        "lui	$3,0xFF1F		\n" // Clear all interrupt masks under D_STAT, other SIF0, SIF1 & SIF2. Writing a 1 reverses the bit.
        "and	$2,$3		\n"
        "sw	$2,0x1000E010	\n"
        "sw	$0,0x1000E000	\n" // D_CTRL = 0
        "sw	$0,0x1000E020	\n" // D_PCR = 0
        "sw	$0,0x1000E030	\n" // D_SQWC = 0
        "sw	$0,0x1000E050	\n" // D_RBOR = 0
        "sw	$0,0x1000E040	\n" // D_RBSR = 0
        "li	$3,1			\n"
        "lw	$2,0x1000E000	\n"
        "ori	$3,$2,1		\n" // D_CTRL (DMAE 1)
        "sw	$3,0x1000E000	\n");
}

void GsDmaSend(const void *addr, u32 qwords)
{
    u32 chcr;
    static char spr;

    if ((u32)addr >= 0x70000000 && (u32)addr <= 0x70003fff) {
        spr = 1;
    } else {
        spr = 0;
    }

    _sw((((u32)addr) & 0x7FFFFFFF) << 0 | (u32)((spr)&0x00000001) << 31, gif_madr);
    _sw(qwords, gif_qwc);

    chcr = FIELD_PREP(CHCR_DIR, 1) | FIELD_PREP(CHCR_STR, 1);

    asm("" ::
            : "memory");

    _sw(chcr, gif_chcr);
}

void GsDmaSend_tag(const void *addr, u32 qwords, const GS_GIF_DMACHAIN_TAG *tag)
{
    u32 chcr;
    static char spr;

    if ((u32)addr >= 0x70000000 && (u32)addr <= 0x70003fff) {
        spr = 1;
    } else {
        spr = 0;
    }

    _sw((((u32)addr) & 0x7FFFFFFF) << 0 | (u32)((spr)&0x00000001) << 31, gif_madr);
    _sw(qwords, gif_qwc);
    _sw((((u32)tag) & 0x7FFFFFFF) << 0 | (u32)((0) & 0x00000001) << 31, gif_tadr);


    chcr = FIELD_PREP(CHCR_DIR, 1) | FIELD_PREP(CHCR_MOD, 1) | FIELD_PREP(CHCR_STR, 1);

    asm("" ::
            : "memory");

    _sw(chcr, gif_chcr);
}

void GsDmaWait(void)
{
    while (FIELD_GET(CHCR_STR, _lw(gif_chcr)))
        ;
}
