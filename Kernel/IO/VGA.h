// Copyright (c) 2023, Pedro Palacios Almendros.

#pragma once

#include <stddef.h>
#include <stdint.h>

namespace VGA {

    constexpr size_t WIDTH = 80;
    constexpr size_t HEIGHT = 25;

    enum class Color : uint8_t {
        Black = 0,
        Blue = 1,
        Green = 2,
        Cyan = 3,
        Red = 4,
        Magenta = 5,
        Brown = 6,
        LightGrey = 7,
        DarkGrey = 8,
        LightBlue = 9,
        LightGreen = 10,
        LightCyan = 11,
        LightRed = 12,
        LightMagenta = 13,
        LightBrown = 14,
        White = 15
    };

    struct CharacterColor {
        Color m_foreground;
        Color m_background;

        CharacterColor(Color foreground, Color background) : m_foreground(foreground), m_background(background) {}

        [[nodiscard]] uint8_t to_vga_color_byte() const {
            return uint8_t(m_foreground) | (uint8_t(m_background) << 4);
        }
    };

}// namespace VGA