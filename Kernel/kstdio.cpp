// Copyright (c) 2023, Pedro Palacios Almendros.

#include "kstdio.h"

KernelOutputStream kout;

void assert_impl(bool condition, const char *msg) {
    if (!condition) {
        kpanic(msg);
    }
}

void kpanic(const char *str) {
    auto &device_manager = DeviceManager::the();
    if (device_manager.has_terminal()) {
        device_manager.get_terminal().set_bg_color(VGA::Color::Red);
    }

    kout << "KERNEL PANIC: " << str << '\n';

    // TODO: Disable interrupts?
    while (true) {
        asm volatile("hlt");
    }

    __builtin_unreachable();
}
