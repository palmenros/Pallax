// Copyright (c) 2023, Pedro Palacios Almendros.

#pragma once

#include "PalLib/Optional.h"
#include "SerialPort.h"
#include "Terminal.h"

class DeviceManager {

public:
    static DeviceManager &the();

    void register_terminal(Terminal &terminal);
    void register_debug_output_serial_port(SerialPort &serial_port);

    Terminal &get_terminal();
    [[nodiscard]] bool has_terminal();

    SerialPort &get_debug_output_serial_port();
    [[nodiscard]] bool has_debug_output_serial_port();

private:
    Terminal *m_terminal = nullptr;
    SerialPort *m_debug_output_serial_port = nullptr;
};
