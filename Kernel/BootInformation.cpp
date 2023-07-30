// Copyright (c) 2023, Pedro Palacios Almendros.

#include "BootInformation.h"
#include "PalLib/StdLibExtras.h"
#include "kstdio.h"
#include "multiboot.h"

BootInformation::BootInformation(multiboot_info *mb_info, int32_t mb_magic)
    : m_mb_info(mb_info) {
    if (mb_magic != MULTIBOOT_BOOTLOADER_MAGIC) {
        kpanic("Multiboot bootloader magic incorrect!\n");
    }
}

void BootInformation::print_memory_map() const {
    if ((m_mb_info->flags & MULTIBOOT_INFO_MEM_MAP) == 0) {
        kpanic("Multiboot didn't provide us with a memory map");
    }

    // Print memory map
    for (size_t offset = 0; offset < m_mb_info->mmap_length; offset += sizeof(multiboot_memory_map_t)) {
        multiboot_memory_map_t *mmap = (multiboot_memory_map_t *) (m_mb_info->mmap_addr + offset);

        kout << "Start address: " << (void *) mmap->addr << ", ";
        kout << "Length: " << (void *) mmap->len << ", ";
        kout << "Size: " << mmap->size << ", ";
        kout << "Type: " << mmap->type << " (";

        switch (mmap->type) {
            case MULTIBOOT_MEMORY_AVAILABLE:
                kout << "AVAILABLE";
                break;
            case MULTIBOOT_MEMORY_RESERVED:
                kout << "RESERVED";
                break;
            case MULTIBOOT_MEMORY_ACPI_RECLAIMABLE:
                kout << "ACPI_RECLAIMABLE";
                break;
            case MULTIBOOT_MEMORY_NVS:
                kout << "NVS";
                break;
            case MULTIBOOT_MEMORY_BADRAM:
                kout << "BADRAM";
                break;
            default:
                kpanic("Unknown multiboot mmap type");
        }

        kout << ")\n";
    }
}

const char *BootInformation::get_bootloader_name() const {
    if (m_mb_info->flags & MULTIBOOT_INFO_BOOT_LOADER_NAME) {
        return (const char *) m_mb_info->boot_loader_name;
    } else {
        kpanic("Bootloader name not provided!\n");
    }
}

size_t BootInformation::get_upper_memory_size_bytes() const {
    if ((m_mb_info->flags & MULTIBOOT_INFO_MEMORY) == 0) {
        kpanic("Multiboot didn't provide us with mem_lower and mem_upper");
    }
    return m_mb_info->mem_upper * KB;
}
