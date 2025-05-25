/*
A InitRAMfs /init .
Copyright (C) 2025  Wdboyes13

This program is free software; you can redistribute it and/or
modify it under the terms of the GNU General Public License
as published by the Free Software Foundation; **version 2 of the License only**.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program; if not, see
<https://www.gnu.org/licenses/>.
*/
#include "fsld.h"
#include <stdio.h>
#include <blkid/blkid.h>
#include <string.h>
#include <libkmod.h>
#include <stdlib.h>
#include <sys/mount.h>
#include <sys/stat.h>
#include <errno.h>


int is_ext4(const char *device){
    const char *fstype = NULL;
    blkid_probe pr = blkid_new_probe_from_filename(device);
    if (!pr) {
        perror("blkid_new_probe_from_filename");
        return 0;
    }

    blkid_do_probe(pr);
    blkid_probe_lookup_value(pr, "TYPE", &fstype, NULL);
    int result = fstype && strcmp(fstype, "ext4") == 0;
    blkid_free_probe(pr);
    return result;
}


int format_ext4(const char *device) {
    perror("Invalid Root Filesystem - Expected EXT4\n");
    exit(1);
}

int mount_ext4(const char *source, const char *target) {
    if (mount(source, target, "ext4", 0, "defaults") !=0) {
        perror("mount");
        return 1;
    }
    return 0;
}
