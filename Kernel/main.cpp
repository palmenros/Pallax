// Copyright (c) 2023, Pedro Palacios Almendros.

#include "IO/Terminal.h"
#include "multiboot.h"

// TODO: Better way to construct a terminal. Add support for streams.
Terminal terminal{(uint16_t *) 0xB8000};
TerminalOutputStream kout{terminal};

extern "C" void kernel_main(multiboot_info *mb_info, int32_t mb_magic) {
    kout << "Pallax Kernel initialization...\n";

    if (mb_magic == MULTIBOOT_BOOTLOADER_MAGIC) {
        kout << "Multiboot bootloader magic correct!\n";
    } else {
        // TODO: Add support for panic and ASSERTs.
        auto colorScope = terminal.using_fg_color(VGA::Color::Red);
        kout << "Multiboot bootloader magic incorrect!\n";
    }

    if (mb_info->flags & MULTIBOOT_INFO_BOOT_LOADER_NAME) {
        kout << "Bootloader: " << (char *) mb_info->boot_loader_name << "\n";
    } else {
        auto colorScope = terminal.using_fg_color(VGA::Color::Red);
        kout << "ERROR: Bootloader name not provided!\n";
    }
}