/*
** Copyright 2002, Travis Geiselbrecht. All rights reserved.
** Distributed under the terms of the NewOS License.
*/
#ifndef _ZFS_H
#define _ZFS_H

#include <kernel/vfs.h>
#include "zfs_fs.h"

/* mount structure */
typedef struct zfs_fs {
	fs_id id;
	int fd;
	void *dev_vnode;
	zfs_superblock sb;
} zfs_fs;

/* fs calls */
int zfs_mount(fs_cookie *fs, fs_id id, const char *device, void *args, vnode_id *root_vnid);
int zfs_unmount(fs_cookie fs);
int zfs_sync(fs_cookie fs);

int zfs_lookup(fs_cookie fs, fs_vnode dir, const char *name, vnode_id *id);

int zfs_getvnode(fs_cookie fs, vnode_id id, fs_vnode *v, bool r);
int zfs_putvnode(fs_cookie fs, fs_vnode v, bool r);
int zfs_removevnode(fs_cookie fs, fs_vnode v, bool r);

int zfs_opendir(fs_cookie fs, fs_vnode v, dir_cookie *cookie);
int zfs_closedir(fs_cookie fs, fs_vnode v, dir_cookie cookie);
int zfs_rewinddir(fs_cookie fs, fs_vnode v, dir_cookie cookie);
int zfs_readdir(fs_cookie fs, fs_vnode v, dir_cookie cookie, void *buf, size_t buflen);

int zfs_open(fs_cookie fs, fs_vnode v, file_cookie *cookie, int oflags);
int zfs_close(fs_cookie fs, fs_vnode v, file_cookie cookie);
int zfs_freecookie(fs_cookie fs, fs_vnode v, file_cookie cookie);
int zfs_fsync(fs_cookie fs, fs_vnode v);

ssize_t zfs_read(fs_cookie fs, fs_vnode v, file_cookie cookie, void *buf, off_t pos, ssize_t len);
ssize_t zfs_write(fs_cookie fs, fs_vnode v, file_cookie cookie, const void *buf, off_t pos, ssize_t len);
int zfs_seek(fs_cookie fs, fs_vnode v, file_cookie cookie, off_t pos, seek_type st);
int zfs_ioctl(fs_cookie fs, fs_vnode v, file_cookie cookie, int op, void *buf, size_t len);

int zfs_canpage(fs_cookie fs, fs_vnode v);
ssize_t zfs_readpage(fs_cookie fs, fs_vnode v, iovecs *vecs, off_t pos);
ssize_t zfs_writepage(fs_cookie fs, fs_vnode v, iovecs *vecs, off_t pos);

int zfs_create(fs_cookie fs, fs_vnode dir, const char *name, void *create_args, vnode_id *new_vnid);
int zfs_unlink(fs_cookie fs, fs_vnode dir, const char *name);
int zfs_rename(fs_cookie fs, fs_vnode olddir, const char *oldname, fs_vnode newdir, const char *newname);

int zfs_mkdir(fs_cookie _fs, fs_vnode _base_dir, const char *name);
int zfs_rmdir(fs_cookie _fs, fs_vnode _base_dir, const char *name);

int zfs_rstat(fs_cookie fs, fs_vnode v, struct file_stat *stat);
int zfs_wstat(fs_cookie fs, fs_vnode v, struct file_stat *stat, int stat_mask);

#endif
