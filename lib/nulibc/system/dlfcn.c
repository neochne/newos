/* 
** Copyright 2001, Manuel J. Petit. All rights reserved.
** Distributed under the terms of the NewOS License.
*/

#include <dlfcn.h>
#include <sys/syscalls.h>
#include <kernel/user_runtime.h>


static struct rld_export_t *rld;

void *
dlopen(char const *name, unsigned flags)
{
	return (void*)(rld->dl_open(name, flags));
}

void *
dlsym(void *img, char const *name)
{
	return rld->dl_sym((unsigned)img, name, 0);
}

int
dlclose(void *img)
{
	return rld->dl_close((unsigned)img, 0);
}