// Copyright (c) 2023, Pedro Palacios Almendros.

#pragma once

#include <PalLib/StdLibExtras.h>
#include <stddef.h>
#include <stdint.h>

class PageUtils {
public:
    // Must be a power of two
    static constexpr size_t PAGE_SIZE = 4 * KB;

    // Returns a pointer that is aligned to the beginning of a new page
    //  and its value is greater or equal than ptr.
    static uintptr_t ceil_align_to_page(uintptr_t ptr);

    PageUtils() = delete;
};
