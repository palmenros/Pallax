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
};

extern KernelOutputStream kout;

// TODO: Convert panic into a std::format like interface.
[[noreturn]] void kpanic(const char *str);

void assert_impl(bool condition, const char *msg);

#ifndef ASSERT

// These macros are needed to stringize the __LINE__ integer constant
#define PAL_STRINGIZE(x) PAL_STRINGIZE2(x)
#define PAL_STRINGIZE2(x) #x
#define __LINE_STRING__ PAL_STRINGIZE(__LINE__)

#define ASSERT(COND) assert_impl(COND, "Assertion failed: " #COND " at " __FILE__ ", line " __LINE_STRING__)

#endif