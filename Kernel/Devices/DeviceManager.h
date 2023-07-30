// Copyright (c) 2023, Pedro Palacios Almendros.

#pragma once

#include "Terminal.h"

class DeviceManager {

public:
    static DeviceManager &the();

    void register_terminal(Terminal &terminal);
    Terminal &get_terminal();
    [[nodiscard]] bool has_terminal();

private:
    Terminal *m_terminal = nullptr;
};
