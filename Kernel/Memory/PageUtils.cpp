// Copyright (c) 2023, Pedro Palacios Almendros.

#include "PageUtils.h"

uintptr_t PageUtils::ceil_align_to_page(uintptr_t ptr) {
    uintptr_t low = ptr & (PAGE_SIZE - 1);
    uintptr_t high = ptr ^ low;

    uintptr_t res;
    if (low != 0) {
        res = high + PAGE_SIZE;
    } else {
        res = high;
    }

    // TODO: These ASSERTs may be unnecessary;
    ASSERT((res & (PAGE_SIZE - 1)) == 0);
    ASSERT(res >= ptr);
    return res;
}
