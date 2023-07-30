// Copyright (c) 2023, Pedro Palacios Almendros.

#pragma once

#include "Devices/DeviceManager.h"
#include "PalLib/OutputStream.h"
#include "PalLib/StdLibExtras.h"

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