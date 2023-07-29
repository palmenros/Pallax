// Copyright (c) 2023, Pedro Palacios Almendros.

#include "DeviceManager.h"

void DeviceManager::register_terminal(Terminal &terminal) {
    this->m_terminal = &terminal;
}

Terminal &DeviceManager::get_terminal() {
    // TODO: Assert that terminal is not a null pointer or return Option<Terminal&>
    return *m_terminal;
}

bool DeviceManager::has_terminal() {
    return m_terminal != nullptr;
}

DeviceManager &DeviceManager::the() {
    static DeviceManager device_manager;
    return device_manager;
}
