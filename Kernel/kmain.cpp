// Copyright (c) 2023, Pedro Palacios Almendros.

#include "Devices/SerialPort.h"
#include "Kernel/Devices/VGATerminal.h"
#include "PalLib/Optional.h"
#include "kstdio.h"
#include "multiboot.h"

extern "C" void kernel_main(multiboot_info *mb_info, int32_t mb_magic) {
    // TODO: Better detect the VGA address either with Multiboot or ACPI
    VGATerminal::initialize();

    SerialPort COM1{SerialPort::COM1_ADDR};
    DeviceManager::the().register_debug_output_serial_port(COM1);

    kout << "Pallax Kernel initialization...\n";

    if (mb_magic == MULTIBOOT_BOOTLOADER_MAGIC) {
        kout << "Multiboot bootloader magic correct!\n";
    } else {
        kpanic("Multiboot bootloader magic incorrect!\n");
    }

    if (mb_info->flags & MULTIBOOT_INFO_BOOT_LOADER_NAME) {
        kout << "Bootloader: " << (char *) mb_info->boot_loader_name << "\n";
    } else {
        kpanic("Bootloader name not provided!\n");
    }

    // TODO: Make sure we copy al relevant data from multiboot_info before claiming memory as ours
    if ((mb_info->flags & MULTIBOOT_INFO_MEMORY) == 0) {
        kpanic("Multiboot didn't provide us with mem_lower and mem_upper");
    }

    kout << "mem_lower: " << (void *) mb_info->mem_lower << ", mem_upper: " << (void *) mb_info->mem_upper << '\n';

    if ((mb_info->flags & MULTIBOOT_INFO_MEM_MAP) == 0) {
        kpanic("Multiboot didn't provide us with a memory map");
    }

    // Print memory map
    for (size_t offset = 0; offset < mb_info->mmap_length; offset += sizeof(multiboot_memory_map_t)) {
        multiboot_memory_map_t *mmap = (multiboot_memory_map_t *) (mb_info->mmap_addr + offset);

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