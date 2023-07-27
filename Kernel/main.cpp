// Copyright (c) 2023, Pedro Palacios Almendros.

#include "IO/Terminal.h"

// TODO: Better way to construct a terminal. Add support for streams.
Terminal terminal{(uint16_t *) 0xB8000};

// TODO: Remove global constructor and destructor test
class Test {
public:
    const int i;

    explicit Test(int i)
        : i(i) {
    }

    ~Test() {
        terminal.print("Destroyed!");
    }
};

Test test(3);

#include "multiboot.h"

extern "C" void kernel_main(multiboot_info *mb_info, int32_t mb_magic) {

    /* Newline support is left as an exercise. */
    terminal.print("Hello, kernel World from C!\nEsto es otra linea\n");

    if (mb_magic == MULTIBOOT_BOOTLOADER_MAGIC) {
        terminal.print("Magic correct!\n");
    } else {
        terminal.print("Magic incorrect!\n");
    }

    if (mb_info->flags & MULTIBOOT_INFO_BOOT_LOADER_NAME) {
        terminal.print((char *) mb_info->boot_loader_name);
        terminal.print('\n');
    } else {
        terminal.print("Bootloader name not provided!\n");
    }

    int test_i = test.i;
    if (test_i != 3) {
        terminal.set_fg_color(VGA::Color::Red);

        terminal.print("ERROR: Global constructors not called, global object value is '");
        terminal.print('0' + test_i);
        terminal.print("' and should be '3'");

        terminal.set_fg_color(VGA::Color::LightGrey);
    } else {

        terminal.set_fg_color(VGA::Color::Green);

        terminal.print("Global constructors called successfully, global object value is ");
        terminal.print('0' + test_i);
        terminal.print('\n');

        terminal.set_fg_color(VGA::Color::LightGrey);
    }
}