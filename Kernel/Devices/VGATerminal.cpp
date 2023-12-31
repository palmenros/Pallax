// Copyright (c) 2023, Pedro Palacios Almendros.

#include "VGATerminal.h"
#include "kstdio.h"

Pal::Optional<VGATerminal> VGATerminal::s_maybe_terminal = {};

uint16_t VGATerminal::get_colored_vga_char(char c, VGA::CharacterColor color) {
    uint8_t color_byte = color.to_vga_color_byte();
    return uint16_t(c) | (uint16_t(color_byte) << 8);
}

void VGATerminal::put_char(char c, size_t x, size_t y, VGA::CharacterColor color) {
    m_vga_buffer[x + y * width()] = get_colored_vga_char(c, color);
}

VGATerminal::VGATerminal(uint16_t *vga_buffer)
    : Terminal(VGA::Color::LightGrey, VGA::Color::Black), m_vga_buffer(vga_buffer) {

    ASSERT(vga_buffer != nullptr);

    // Blank the screen
    for (size_t x = 0; x < VGATerminal::width(); x++) {
        for (size_t y = 0; y < VGATerminal::height(); y++) {
            vga_buffer[x + y * VGATerminal::width()] = get_colored_vga_char(' ', get_character_color());
        }
    }
}

size_t VGATerminal::height() {
    return VGA::HEIGHT;
}

size_t VGATerminal::width() {
    return VGA::WIDTH;
}

VGATerminal &VGATerminal::the() {
    return s_maybe_terminal.value();
}

bool VGATerminal::is_initialized() {
    return s_maybe_terminal.has_value();
}

void VGATerminal::initialize(uint16_t *vga_buffer) {
    s_maybe_terminal = VGATerminal{vga_buffer};
    DeviceManager::the().register_terminal(VGATerminal::the());
}
