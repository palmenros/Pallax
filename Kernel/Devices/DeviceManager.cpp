// Copyright (c) 2023, Pedro Palacios Almendros.

#include "DeviceManager.h"
#include "kstdio.h"

void DeviceManager::register_terminal(Terminal &terminal) {
    m_terminal = &terminal;
}

Terminal &DeviceManager::get_terminal() {
    ASSERT(m_terminal != nullptr);
    return *m_terminal;
}

bool DeviceManager::has_terminal() {
    return m_terminal != nullptr;
}

DeviceManager &DeviceManager::the() {
    static DeviceManager device_manager;
    return device_manager;
}

bool DeviceManager::has_debug_output_serial_port() {
    return m_debug_output_serial_port != nullptr;
}
SerialPort &DeviceManager::get_debug_output_serial_port() {
    ASSERT(m_debug_output_serial_port != nullptr);
    return *m_debug_output_serial_port;
}

void DeviceManager::register_debug_output_serial_port(SerialPort &serial_port) {
    m_debug_output_serial_port = &serial_port;
}
