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
 * Definitions and imports for iomanX.
 */

#ifndef __IOMANX_H__
#define __IOMANX_H__

#include <types.h>
#include <irx.h>
#include <io_common.h>
#include <iox_stat.h>

/* Device drivers.  */

/* Device types.  */
#define IOP_DT_CHAR	0x01
#define IOP_DT_CONS	0x02
#define IOP_DT_BLOCK	0x04
#define IOP_DT_RAW	0x08
#define IOP_DT_FS	0x10
#ifndef IOMAN_NO_EXTENDED
/** Supports calls after chstat().  */
#define IOP_DT_FSEXT	0x10000000	
#endif

/** File objects passed to driver operations.  */
typedef struct _iop_file {
	/** File open mode.  */
	int	mode;		
	/** HW device unit number.  */
	int	unit;		
	/** Device driver.  */
	struct _iop_device *device; 
	/** The device driver can use this however it wants.  */
	void	*privdata;	
} iop_file_t;

typedef struct _iop_device {
	const char *name;
	unsigned int type;
	/** Not so sure about this one.  */
	unsigned int version;
	const char *desc;
	struct _iop_device_ops *ops;
} iop_device_t;

typedef struct _iop_device_ops {
	int	(*init)(iop_device_t *);
	int	(*deinit)(iop_device_t *);
	int	(*format)(iop_file_t *, const char *, const char *, void *, int);
	int	(*open)(iop_file_t *, const char *, int, int);
	int	(*close)(iop_file_t *);
	int	(*read)(iop_file_t *, void *, int);
	int	(*write)(iop_file_t *, void *, int);
	int	(*lseek)(iop_file_t *, int, int);
	int	(*ioctl)(iop_file_t *, int, void *);
	int	(*remove)(iop_file_t *, const char *);
	int	(*mkdir)(iop_file_t *, const char *, int);
	int	(*rmdir)(iop_file_t *, const char *);
	int	(*dopen)(iop_file_t *, const char *);
	int	(*dclose)(iop_file_t *);
	int	(*dread)(iop_file_t *, iox_dirent_t *);
	int	(*getstat)(iop_file_t *, const char *, iox_stat_t *);
	int	(*chstat)(iop_file_t *, const char *, iox_stat_t *, unsigned int);

#ifndef IOMAN_NO_EXTENDED
	/* Extended ops start here.  */
	int	(*rename)(iop_file_t *, const char *, const char *);
	int	(*chdir)(iop_file_t *, const char *);
	int	(*sync)(iop_file_t *, const char *, int);
	int	(*mount)(iop_file_t *, const char *, const char *, int, void *, int);
	int	(*umount)(iop_file_t *, const char *);
	s64	(*lseek64)(iop_file_t *, s64, int);
	int	(*devctl)(iop_file_t *, const char *, int, void *, unsigned int, void *, unsigned int);
	int	(*symlink)(iop_file_t *, const char *, const char *);
	int	(*readlink)(iop_file_t *, const char *, char *, unsigned int);
	int	(*ioctl2)(iop_file_t *, int, void *, unsigned int, void *, unsigned int);
#endif /* IOMAN_NO_EXTENDED */
} iop_device_ops_t;

iop_device_t **GetDeviceList(void);

int open(const char *name, int flags, ...);
int close(int fd);
int read(int fd, void *ptr, int size);
int write(int fd, void *ptr, int size);
int lseek(int fd, int offset, int mode);

int ioctl(int fd, int cmd, void *param);
int remove(const char *name);

int mkdir(const char *path, int mode);
int rmdir(const char *path);
int dopen(const char *path);
int dclose(int fd);
int dread(int fd, iox_dirent_t *buf);

int getstat(const char *name, iox_stat_t *stat);
int chstat(const char *name, iox_stat_t *stat, unsigned int statmask);

/** This can take take more than one form.  */
int format(const char *dev, const char *blockdev, void *arg, int arglen);

#ifndef IOMAN_NO_EXTENDED
/* The newer calls - these are NOT supported by the older IOMAN.  */
int rename(const char *old, const char *new);
int chdir(const char *name);
int sync(const char *dev, int flag);
int mount(const char *fsname, const char *devname, int flag, void *arg, int arglen);
int umount(const char *fsname);
s64 lseek64(int fd, s64 offset, int whence);
int devctl(const char *name, int cmd, void *arg, unsigned int arglen, void *buf, unsigned int buflen);
int symlink(const char *old, const char *new);
int readlink(const char *path, char *buf, unsigned int buflen);
int ioctl2(int fd, int cmd, void *arg, unsigned int arglen, void *buf, unsigned int buflen);
#endif /* IOMAN_NO_EXTENDED */

int AddDrv(iop_device_t *device);
int DelDrv(const char *name);

void StdioInit(int mode);

#endif /* __IOMANX_H__ */
