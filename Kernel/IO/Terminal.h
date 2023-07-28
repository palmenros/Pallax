// Copyright (c) 2023, Pedro Palacios Almendros.

#pragma once

#include "VGA.h"
#include <stddef.h>
#include <stdint.h>

class ColorScope {
public:
    ~ColorScope();

private:
    ColorScope(class Terminal &terminal, VGA::CharacterColor colorToBeRestored);

    class Terminal &terminal;
    VGA::CharacterColor colorToBeRestored;

    friend class Terminal;
};

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

    [[nodiscard]] ColorScope using_color(VGA::CharacterColor color);
    [[nodiscard]] ColorScope using_fg_color(VGA::Color color);
    [[nodiscard]] ColorScope using_bg_color(VGA::Color color);

    void print(char c);

    // TODO: Add support for string views
    void print(const char *str);

    void set_character_color(VGA::CharacterColor color);

private:
    uint16_t *vgaBuffer;
    VGA::Color fgColor, bgColor;

    size_t cursorX, cursorY;

private:
    [[nodiscard]] uint16_t get_colored_vga_char(char c) const;
};