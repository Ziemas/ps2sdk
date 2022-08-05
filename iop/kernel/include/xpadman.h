/**
 * @file
 * Extended pad functions
 */

#ifndef __XPADMAN_H__
#define __XPADMAN_H__

#include <types.h>
#include <defs.h>

s32 padInit(void * ee_addr);
s32 padEnd();
s32 padPortClose(s32 port, s32 slot, s32 wait);
s32 padPortOpen(s32 port, s32 slot, s32 pad_area_ee_addr, u32 *buf);
u32 padGetInBuffer(u32 port, u32 slot, u8 *buf);
u32 padSetupEEButtonData(u32 port, u32 slot, void *pstate);
u32 padGetModeConfig(u32 port, u32 slot);
u32 padSetMainMode(u32 port, u32 slot, u32 mode, u32 lock);
u32 padSetActDirect(u32 port, u32 slot, u8 *actData);
u32 padSetActAlign(u32 port, u32 slot, const u8 *actData);
u32 padGetButtonMask(u32 port, u32 slot);
u32 padSetButtonInfo(u32 port, u32 slot, u32 info);
s32 padInfoAct(u32 port, u32 slot, s32 act, u32 val);
s32 padInfoComb(u32 port, u32 slot, s32 val1, u32 val2);
s32 padInfoMode(u32 port, u32 slot, s32 val1, u32 val2);

#endif /* __XPADMAN_H__ */
