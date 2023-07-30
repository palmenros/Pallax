// Copyright (c) 2023, Pedro Palacios Almendros.

#include "SerialPort.h"
#include "PalLib/StdLibExtras.h"
#include "io.h"
#include "kstdio.h"

SerialPort::SerialPort(uint16_t io_port, uint32_t baud_rate)
    : m_io_port(io_port) {

    // Disable all interrupts
    outb(io_port + OFF_INTR_ENABLE, 0x0);

    // Important: baud_rate will also "restore" m_line_control, setting it for the first time in the constructor
    m_line_control = LINE_CTRL_8N1;
    set_baud_rate(baud_rate);

    // Enable FIFOs and clear them
    outb(io_port + OFF_INTR_ID_FIFO_CTRL, 0xc7);

    // Disable IRQs, set RTS and DSR. Enable loopback for testing
    outb(io_port + OFF_MODEM_CTRL, 0b0001'0011);

    // Send a test character and try to receive it. We will check that we receive the same character we send.
    constexpr uint8_t test_char = 0xDE;
    outb(io_port + OFF_DATA, test_char);

    // TODO: Maybe instead of panicking offer a function to try create a SerialPort?
    if (inb(io_port + OFF_DATA) != test_char) {
        kpanic("Serial port loopback error while initializing");
    }

    // Disable IRQs, set RTS and DSR. Disable loopback for normal operation
    outb(io_port + OFF_MODEM_CTRL, 0b0011);
}

void SerialPort::set_baud_rate(uint32_t baud_rate) {
    ASSERT(baud_rate <= MAX_BAUD_RATE);

    // Enable DLAB (to set the baud rate divisor)
    outb(m_io_port + OFF_LINE_CTRL, DLAB_BIT | m_line_control);

    // Compute required divisor
    uint16_t divisor = MAX_BAUD_RATE / baud_rate;
    ASSERT(divisor > 0);

    // Store actual baud_rate (which may be different from baud_rate if baud_rate does not divide 115200)
    m_baud_rate = 115200 / divisor;

    // Send divisor to serial port
    outb(m_io_port + OFF_LSB_BAUD_RATE, divisor & 0xff);
    outb(m_io_port + OFF_MSB_BAUD_RATE, (divisor >> 8) & 0xff);

    // Restore line control information
    outb(m_io_port + OFF_LINE_CTRL, m_line_control);
}

bool SerialPort::data_available() const {
    return inb(m_io_port + OFF_LINE_STATUS) & 1;
}

bool SerialPort::transmit_queue_full() const {
    return !(inb(m_io_port + OFF_LINE_STATUS) & (1 << 5));
}

void SerialPort::send_byte(uint8_t b) const {
    while (transmit_queue_full()) {
        /* wait */
    }

    outb(m_io_port + OFF_DATA, b);
}

uint8_t SerialPort::recv_byte() const {
    while (!data_available()) {
        /* wait */
    }

    return inb(m_io_port + OFF_DATA);
}

void SerialPort::write_char(char c) {
    send_byte(c);
}
