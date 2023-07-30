// Copyright (c) 2023, Pedro Palacios Almendros.

#pragma once

#include "BootInformation.h"
#include <stddef.h>
#include <stdint.h>

class PhysicalPageAllocator {
public:
    explicit PhysicalPageAllocator(const BootInformation &boot_info);

private:
    uint8_t *m_first_physical_page;
    size_t m_number_physical_pages;
};
