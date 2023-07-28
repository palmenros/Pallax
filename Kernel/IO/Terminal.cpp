// Copyright (c) 2023, Pedro Palacios Almendros.

#include "Terminal.h"

Terminal::Terminal(uint16_t *vgaBuffer)
    : vgaBuffer(vgaBuffer),
      fgColor(VGA::Color::LightGrey),
      bgColor(VGA::Color::Black),
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
    return fgColor;
}

VGA::Color Terminal::get_bg_color() const {
    return bgColor;
}

void Terminal::set_fg_color(VGA::Color fgColor) {
    this->fgColor = fgColor;
}

void Terminal::set_bg_color(VGA::Color bgColor) {
    this->bgColor = bgColor;
}

VGA::CharacterColor Terminal::get_character_color() const {
    return {fgColor, bgColor};
}

uint16_t Terminal::get_colored_vga_char(char c) const {
    uint8_t color = get_character_color().to_vga_color_byte();
    return uint16_t(c) | (uint16_t(color) << 8);
}

void Terminal::printChar(char c) {

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

ColorScope Terminal::using_color(VGA::CharacterColor color) {
    auto old_color = get_character_color();

    set_character_color(color);

    return {*this, old_color};
}

void Terminal::set_character_color(VGA::CharacterColor color) {
    set_fg_color(color.foreground);
    set_bg_color(color.background);
}

ColorScope Terminal::using_fg_color(VGA::Color color) {
    return using_color({color, bgColor});
}

ColorScope Terminal::using_bg_color(VGA::Color color) {
    return using_color({fgColor, color});
}

ColorScope::ColorScope(Terminal &terminal, VGA::CharacterColor colorToBeRestored)
    : terminal(terminal), colorToBeRestored(colorToBeRestored) {
}

ColorScope::~ColorScope() {
    terminal.set_character_color(colorToBeRestored);
}
TerminalOutputStream::TerminalOutputStream(Terminal &terminal)
    : terminal(terminal) {
}
void TerminalOutputStream::writeChar(char c) {
    terminal.printChar(c);
}
