// Copyright (c) 2023, Pedro Palacios Almendros.

#include "Kernel/IO/VGATerminal.h"
#include "PalLib/Optional.h"
#include "multiboot.h"

// TODO: Better way to construct a terminal. Add support for streams.
// TODO: Define and enforce a naming convention

extern "C" void kernel_main(multiboot_info *mb_info, int32_t mb_magic) {
    Terminal &kout = VGATerminal::the();

    kout << "Pallax Kernel initialization...\n";

    if (mb_magic == MULTIBOOT_BOOTLOADER_MAGIC) {
        kout << "Multiboot bootloader magic correct!\n";
    } else {
        // TODO: Add support for panic and ASSERTs.
        auto color_scope = kout.using_fg_color(VGA::Color::Red);
        kout << "Multiboot bootloader magic incorrect!\n";
    }

    Pal::Optional<bool> a = true;
    a = false;

    a = {};

    kout << "Has value: " << a.has_value() << '\n';
    if (a) {
        kout << "Value: " << a.value() << '\n';
    }

    if (mb_info->flags & MULTIBOOT_INFO_BOOT_LOADER_NAME) {
        kout << "Bootloader: " << (char *) mb_info->boot_loader_name << "\n";
    } else {
        auto color_scope = kout.using_fg_color(VGA::Color::Red);
        kout << "ERROR: Bootloader name not provided!\n";
    }

    kout << (void *) MULTIBOOT_BOOTLOADER_MAGIC << '\n';
}