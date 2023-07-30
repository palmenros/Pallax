// Copyright (c) 2023, Pedro Palacios Almendros.

#pragma once

#include <stddef.h>
#include <stdint.h>

class BootInformation {
public:
    BootInformation(struct multiboot_info *mb_info, int32_t mb_magic);

    void print_memory_map() const;

    // The returned string is only valid while multiboot_info pointer is
    [[nodiscard]] const char *get_bootloader_name() const;

    // Returns the size of the upper memory (starting at 1MiB) in bytes
    size_t get_upper_memory_size_bytes() const;

private:
    struct multiboot_info *m_mb_info;
};
