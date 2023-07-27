// Copyright (c) 2023, Pedro Palacios Almendros.

#pragma once

#include "VGA.h"
#include <stddef.h>
#include <stdint.h>

class Terminal {
public:
    explicit Terminal(uint16_t *vgaBuffer);

    [[nodiscard]] static size_t height() { return VGA::HEIGHT; }
    [[nodiscard]] static size_t width() { return VGA::WIDTH; }

    void set_fg_color(VGA::Color fgColor);
    void set_bg_color(VGA::Color bgColor);

    [[nodiscard]] VGA::Color get_fg_color() const;
    [[nodiscard]] VGA::Color get_bg_color() const;

    [[nodiscard]] VGA::CharacterColor get_character_color() const;

    void print(char c);

    // TODO: Add support for string views
    void print(const char *str);

private:
    uint16_t *vgaBuffer;
    VGA::Color fg_color, bg_color;

    size_t cursorX, cursorY;

private:
    [[nodiscard]] uint16_t get_colored_vga_char(char c) const;
};