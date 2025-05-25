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
#include "mods.h"
#include <libkmod.h>
#include <stdio.h>
#include <string.h>

void mod(const char *name){
        struct kmod_ctx *ctx;
    struct kmod_module *mod;
    int err;

    // Create a new kmod context
    ctx = kmod_new(NULL, NULL);
    if (!ctx) {
        fprintf(stderr, "Failed to create kmod context\n");
    }

    // Load the module by name
    err = kmod_module_new_from_path(ctx, name, &mod);
    if (err < 0) {
        fprintf(stderr, "Failed to load module metadata\n");
        kmod_unref(ctx);
    }

    // Insert the module
    err = kmod_module_probe_insert_module(mod, 0, NULL, NULL, NULL, NULL);
    if (err < 0) {
        fprintf(stderr, "Failed to insert module: %s\n", strerror(-err));
    } else {
        printf("Module loaded successfully\n");
    }

    // Cleanup
    kmod_module_unref(mod);
    kmod_unref(ctx);
}

void ldmods(){
    mod("/lib/modules/drivers/block/virtio_blk");
    mod("/lib/modules/drivers/net/virtio_net");
    mod("/lib/modules/net/core/net_failover");
    mod("/lib/modules/drivers/net/ethernet/intel/e1000");
    mod("/lib/modules/drivers/net/ethernet/intel/e100");
    mod("/lib/modules/drivers/net/ethernet/intel/e1000e");
    mod("/lib/modules/drivers/net/ethernet/intel/i40e");
    mod("/lib/modules/drivers/net/ethernet/intel/iavf");
    mod("/lib/modules/drivers/net/ethernet/intel/ice");
    mod("/lib/modules/drivers/net/ethernet/intel/igb");
    mod("/lib/modules/drivers/net/ethernet/intel/igbvf");
    mod("/lib/modules/drivers/net/ethernet/intel/igc");
    mod("/lib/modules/drivers/net/ethernet/intel/ixgbe");
    mod("/lib/modules/drivers/net/ethernet/intel/ixgbevf");
    mod("/lib/modules/drivers/net/ethernet/intel/libeth");
    mod("/lib/modules/drivers/net/ethernet/intel/libie");
    mod("/lib/modules/drivers/virtio/virtio_balloon");
    mod("/lib/modules/drivers/virtio/virtio_dma_buf");
    mod("/lib/modules/drivers/virtio/virtio_input");
    mod("/lib/modules/drivers/virtio/virtio_mem");
    mod("/lib/modules/drivers/virtio/virtio_mmio");
    mod("/lib/modules/drivers/virtio/virtio_pci_legacy_dev");
    mod("/lib/modules/drivers/virtio/virtio_pci_modern_dev");
    mod("/lib/modules/drivers/virtio/virtio_pci");
    mod("/lib/modules/drivers/virtio/failover");
    mod("/lib/modules/fs/9p");
    mod("/lib/modules/fs/bfs");
    mod("/lib/modules/fs/exfat");
    mod("/lib/modules/fs/ext4");
    mod("/lib/modules/fs/fat");
}
