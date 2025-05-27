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
#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/syscall.h>
#include <fcntl.h>

#include "utillinux/switch_root.h"
#include "fsld.h"
#include "mods.h"
#include "sysmnt.h"

int main(){
    mntall();
    ldmods();
    ldfstab();
    const char *mntpath = "/mnt";
    mode_t mode = 0755;

    syscall(SYS_mkdirat, AT_FDCWD, mntpath, mode);

    const char *mntdir = "/mnt/root";
    printf("Checking for sda or vda\n");
    const char *dev = "/dev/vda";
    int exists = 0;
    FILE *vfile = fopen("/dev/vda", "r");
    if (vfile) {
        fclose(vfile);
        exists = 1;
    } else {
        FILE *sfile = fopen("/dev/sda", "r");
        if (sfile) {
            exists = 1;
        }
    }
    if (exists == 1){
        syscall(SYS_mkdirat, AT_FDCWD, mntdir, mode);

        if (!is_ext4(dev)){
            printf("%s is not a valid EXT4 Drive\nFormatting now...\n", dev);
            if (format_ext4(dev) != 0){
                fprintf(stderr, "Formatting Failed!\n");
                return 1;
            }
        }

        if (mount_ext4(dev, mntdir) != 0) {
            fprintf(stderr, "Mount /dev/vda failed\n");
            return 1;
        }
        printf("Switch root\n");
        swrt_wrapper("/mnt/root", "/init");  
    } else {
        perror("Drive not found!!");
        return 1;
    }     
  
}
