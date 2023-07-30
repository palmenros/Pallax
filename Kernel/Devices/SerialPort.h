// Copyright (c) 2023, Pedro Palacios Almendros.

#pragma once

#include "PalLib/OutputStream.h"
#include <stdint.h>

class SerialPort : public Pal::OutputStream {
public:
    explicit SerialPort(uint16_t io_port, uint32_t baud_rate = DEFAULT_BAUD_RATE);

    void send_byte(uint8_t) const;
    uint8_t recv_byte() const;

    // Is the transmit queue full?
    [[nodiscard]] bool transmit_queue_full() const;

    // Is there data available to read from the serial?
    [[nodiscard]] bool data_available() const;

protected:
    void write_char(char c) override;

public:
    // Common addresses of serial ports
    static constexpr uint16_t COM1_ADDR = 0x3F8;

protected:
    static constexpr uint32_t MAX_BAUD_RATE = 115200;
    static constexpr uint32_t DEFAULT_BAUD_RATE = 38400;

    // IO_OFFSETS for the IO port for different hardware registers
    static constexpr uint8_t OFF_DATA = 0;
    static constexpr uint8_t OFF_LSB_BAUD_RATE = 0;// When DLAB=1, it's the LSB for setting the baud rate

    static constexpr uint8_t OFF_INTR_ENABLE = 1;// When DLAB=1, it's the MSB for setting the baud rate
    static constexpr uint8_t OFF_MSB_BAUD_RATE = 1;

    static constexpr uint8_t OFF_INTR_ID_FIFO_CTRL = 2;
    static constexpr uint8_t OFF_LINE_CTRL = 3;

    static constexpr uint8_t OFF_MODEM_CTRL = 4;
    static constexpr uint8_t OFF_LINE_STATUS = 5;
    static constexpr uint8_t OFF_MODEM_STATUS = 6;
    static constexpr uint8_t OFF_SCRATCH_REG = 7;

    static constexpr uint8_t DLAB_BIT = 1 << 7;

    static constexpr uint8_t LINE_CTRL_8N1 = 0x03;// 8 bits, no parity, 1 stop bit

    void set_baud_rate(uint32_t baud_rate);

private:
    uint16_t m_io_port;
    uint32_t m_baud_rate;

    uint8_t m_line_control;
};
