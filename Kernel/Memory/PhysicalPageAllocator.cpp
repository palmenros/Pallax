// Copyright (c) 2023, Pedro Palacios Almendros.

#include "PhysicalPageAllocator.h"
#include "PageUtils.h"
#include "PalLib/StdLibExtras.h"
#include "kstdio.h"

extern char __KERNEL_END_;
extern char __KERNEL_START_;

PhysicalPageAllocator::PhysicalPageAllocator(const BootInformation &boot_info) {
    size_t upper_memory_size = boot_info.get_upper_memory_size_bytes();

    kdbg << "Kernel start: " << (void *) &__KERNEL_START_ << '\n';
    kdbg << "Kernel end: " << (void *) &__KERNEL_END_ << '\n';

    ASSERT((uintptr_t) (&__KERNEL_END_) < 1 * MB + upper_memory_size);

    m_first_physical_page = (uint8_t *) PageUtils::ceil_align_to_page((uintptr_t) (&__KERNEL_END_));

    if ((uintptr_t) m_first_physical_page > 1 * MB + upper_memory_size) {
        kpanic("No RAM available for physical page allocation!");
    }

    m_number_physical_pages = (1 * MB + upper_memory_size - (uintptr_t) m_first_physical_page) / PageUtils::PAGE_SIZE;

    kdbg << "First physical page allocator: " << m_first_physical_page << '\n';
    kdbg << "Number of pages: " << m_number_physical_pages << '\n';
}
