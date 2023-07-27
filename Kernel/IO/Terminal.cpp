// Copyright (c) 2023, Pedro Palacios Almendros.

#include "Terminal.h"

Terminal::Terminal(uint16_t *vgaBuffer)
    : vgaBuffer(vgaBuffer),
      fg_color(VGA::Color::LightGrey),
      bg_color(VGA::Color::Black),
      cursorX(0),
      cursorY(0) {
    // TODO: ASSERT that vgaBuffer is valid (add ASSERTS)

    // Blank the screen
    for (size_t x = 0; x < width(); x++) {
        for (size_t y = 0; y < height(); y++) {
            vgaBuffer[x + y * width()] = get_colored_vga_char(' ');
        }
    }
}

VGA::Color Terminal::get_fg_color() const {
    return fg_color;
}

VGA::Color Terminal::get_bg_color() const {
    return bg_color;
}

void Terminal::set_fg_color(VGA::Color fgColor) {
    fg_color = fgColor;
}

void Terminal::set_bg_color(VGA::Color bgColor) {
    bg_color = bgColor;
}

VGA::CharacterColor Terminal::get_character_color() const {
    return {fg_color, bg_color};
}

uint16_t Terminal::get_colored_vga_char(char c) const {
    uint8_t color = get_character_color().to_vga_color_byte();
    return uint16_t(c) | (uint16_t(color) << 8);
}

void Terminal::print(char c) {

    if (c != '\n') {
        vgaBuffer[cursorX + cursorY * width()] = get_colored_vga_char(c);
    }

    // Advance cursor
    cursorX++;

    if (c == '\n' || cursorX == width()) {
        // Switch to new line
        cursorX = 0;
        cursorY++;

        // TODO: Add scrolling
        // Maybe we have overflowed, in that case, move to the first line again and clear it
        if (cursorY == height()) {
            cursorY = 0;

            // Clear first line
            for (size_t x = 0; x < width(); x++) {
                vgaBuffer[x] = get_colored_vga_char(' ');
            }
        }
    }
}

void Terminal::print(const char *str) {
    while (*str != '\0') {
        print(*str);
        str++;
    }
}
