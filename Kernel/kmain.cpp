// Copyright (c) 2023, Pedro Palacios Almendros.

#include "BootInformation.h"
#include "Devices/SerialPort.h"
#include "Devices/VGATerminal.h"
#include "Memory/PageUtils.h"
#include "kstdio.h"

extern char __KERNEL_END_;
extern char __KERNEL_START_;

extern "C" void kernel_main(struct multiboot_info *mb_info, int32_t mb_magic) {
    // TODO: Better detect the VGA address either with Multiboot or ACPI
    VGATerminal::initialize();

    SerialPort COM1{SerialPort::COM1_ADDR};
    DeviceManager::the().register_debug_output_serial_port(COM1);

    kout << "Pallax Kernel initialization...\n";

    // TODO: Make sure not to use mb_info data that is not copied after initializing the memory manager
    BootInformation boot_info{mb_info, mb_magic};
    kout << "Bootloader: " << boot_info.get_bootloader_name() << '\n';
    boot_info.print_memory_map();

    kout << "Memory size: " << (void *) boot_info.get_upper_memory_size_bytes() << '\n';
    kout << "Kernel start: " << (void *) &__KERNEL_START_ << '\n';
    kout << "Kernel end: " << (void *) &__KERNEL_END_ << '\n';

    kout << (void *) PageUtils::ceil_align_to_page(0x3451000) << '\n';
    kout << (void *) PageUtils::ceil_align_to_page(0x345bf03) << '\n';
}