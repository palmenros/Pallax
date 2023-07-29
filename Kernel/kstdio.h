// Copyright (c) 2023, Pedro Palacios Almendros.

#pragma once

#include "Kernel/IO/DeviceManager.h"
#include "PalLib/OutputStream.h"

class KernelOutputStream : public Pal::OutputStream {
protected:
    void write_char(char c) override {
        auto &device_manager = DeviceManager::the();
        if (device_manager.has_terminal()) {
            device_manager.get_terminal().write_char(c);
        }
    }
} kout;

// TODO: Convert panic into a std::format like interface.
[[noreturn]] void kpanic(const char *str) {
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

static void assert_impl(bool condition, const char *msg) {
    if (!condition) {
        kpanic(msg);
    }
}

// These macros are needed to stringize the __LINE__ integer constant
#define PAL_STRINGIZE(x) PAL_STRINGIZE2(x)
#define PAL_STRINGIZE2(x) #x
#define __LINE_STRING__ PAL_STRINGIZE(__LINE__)

#define ASSERT(COND) assert_impl(COND, "Assertion failed: " #COND " at " __FILE__ ", line " __LINE_STRING__)
