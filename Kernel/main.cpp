// Copyright (c) 2023, Pedro Palacios Almendros.

#include "IO/Terminal.h"
#include "multiboot.h"

// TODO: Better way to construct a terminal. Add support for streams.
Terminal terminal{(uint16_t *) 0xB8000};

extern "C" void kernel_main(multiboot_info *mb_info, int32_t mb_magic) {
    terminal.print("Hello, kernel World from C!\nEsto es otra linea\n");

    if (mb_magic == MULTIBOOT_BOOTLOADER_MAGIC) {
        terminal.print("Magic correct!\n");
    } else {
        // TODO: Add support for panic and ASSERTs.
        auto colorScope = terminal.using_fg_color(VGA::Color::Red);
        terminal.print("Magic incorrect!\n");
    }

    if (mb_info->flags & MULTIBOOT_INFO_BOOT_LOADER_NAME) {
        terminal.print("Bootloader: ");
        terminal.print((char *) mb_info->boot_loader_name);
        terminal.print('\n');
    } else {
        auto colorScope = terminal.using_fg_color(VGA::Color::Red);
        terminal.print("ERROR: Bootloader name not provided!\n");
    }
}