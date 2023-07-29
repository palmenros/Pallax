// Copyright (c) 2023, Pedro Palacios Almendros.

#include "Kernel/IO/VGATerminal.h"
#include "PalLib/Optional.h"
#include "kstdio.h"
#include "multiboot.h"

extern "C" void kernel_main(multiboot_info *mb_info, int32_t mb_magic) {

    // TODO: We should make a better init system
    DeviceManager::the().register_terminal(VGATerminal::the());

    kout << "Pedro\n";

    kout << "Pallax Kernel initialization...\n";

    if (mb_magic == MULTIBOOT_BOOTLOADER_MAGIC) {
        kout << "Multiboot bootloader magic correct!\n";
    } else {
        kpanic("Multiboot bootloader magic incorrect!\n");
    }

    //    Pal::Optional<int> maybe_int = {};
    kout << *(volatile char *) 0;

    if (mb_info->flags & MULTIBOOT_INFO_BOOT_LOADER_NAME) {
        kout << "Bootloader: " << (char *) mb_info->boot_loader_name << "\n";
    } else {
        kpanic("ERROR: Bootloader name not provided!\n");
    }

    kout << (void *) MULTIBOOT_BOOTLOADER_MAGIC << '\n';
}