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
#include "sysmnt.h"
#include <sys/mount.h>
#include <mntent.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>


int already_mounted(const char *target) {
    FILE *mtab = setmntent("/proc/mounts", "r");
    if (!mtab) {
        perror("setmntent /proc/mounts");
        return 0;
    }

    struct mntent *ent;
    while ((ent = getmntent(mtab)) != NULL) {
        if (ent->mnt_dir && strcmp(ent->mnt_dir, target) == 0) {
            endmntent(mtab);
            return 1;
        }
    }

    endmntent(mtab);
    return 0;
}

int ldfstab() {
    FILE *fstab = setmntent("/etc/fstab", "r");
    if (!fstab) {
        perror("setmntent /etc/fstab");
        return 1;
    }

    struct mntent *ent;
    while ((ent = getmntent(fstab)) != NULL) {
        if (!ent->mnt_fsname || !ent->mnt_dir || !ent->mnt_type || !ent->mnt_opts) {
            fprintf(stderr, "[init] Skipping invalid fstab entry\n");
            continue;
        }

        printf("[init] Mounting %s on %s type %s\n", ent->mnt_fsname, ent->mnt_dir, ent->mnt_type);

        unsigned long flags = 0;
        if (hasmntopt(ent, "ro")) flags |= MS_RDONLY;
        if (hasmntopt(ent, "noexec")) flags |= MS_NOEXEC;
        if (hasmntopt(ent, "nosuid")) flags |= MS_NOSUID;
        if (hasmntopt(ent, "nodev")) flags |= MS_NODEV;
        if (hasmntopt(ent, "sync")) flags |= MS_SYNCHRONOUS;
        if (hasmntopt(ent, "noatime")) flags |= MS_NOATIME;
        if (hasmntopt(ent, "bind")) flags |= MS_BIND;

        const char *data = NULL;
        if (strcmp(ent->mnt_opts, "defaults") != 0) {
            data = ent->mnt_opts;
        }

        if (!already_mounted(ent->mnt_dir)) {
            if (mount(ent->mnt_fsname, ent->mnt_dir, ent->mnt_type, flags, data) < 0) {
                fprintf(stderr, "[init] Mount failed for %s: %s\n", ent->mnt_dir, strerror(errno));
            }
        } else {
            printf("[init] Skipping %s (already mounted)\n", ent->mnt_dir);
        }
    }

    endmntent(fstab);
    return 0;
}

void mntall() {
    // Load proc first, always
    printf("[init] Loading proc\n");
    if (mount("proc", "/proc", "proc", 0, NULL) < 0)
        perror("mount /proc");

    // Now you can safely call already_mounted
    if (!already_mounted("/sys")) {
        printf("[init] Loading sys\n");
        if (mount("sysfs", "/sys", "sysfs", 0, NULL) < 0)
            perror("mount /sys");
    } else {
        printf("[init] sys already mounted\n");
    }

    if (!already_mounted("/dev")) {
        printf("[init] Loading devtmpfs\n");
        if (mount("devtmpfs", "/dev", "devtmpfs", 0, NULL) < 0)
            perror("mount /dev");
    } else {
        printf("[init] dev already mounted\n");
    }

}
