// Copyright (c) 2023, Pedro Palacios Almendros.

#pragma once

#include "PalLib/OutputStream.h"
#include "VGA.h"
#include <stddef.h>
#include <stdint.h>

class ColorScope {
public:
    ~ColorScope();

private:
    ColorScope(class Terminal &terminal, VGA::CharacterColor color_to_be_restored);

    class Terminal &m_terminal;
    VGA::CharacterColor m_color_to_be_restored;

    friend class Terminal;
};

class Terminal : public Pal::OutputStream {
public:
    Terminal(VGA::Color fg_color, VGA::Color bg_color);

    [[nodiscard]] virtual size_t height() = 0;
    [[nodiscard]] virtual size_t width() = 0;

    void set_fg_color(VGA::Color fg_color);
    void set_bg_color(VGA::Color bg_color);

    [[nodiscard]] VGA::Color get_fg_color() const;
    [[nodiscard]] VGA::Color get_bg_color() const;

    [[nodiscard]] VGA::CharacterColor get_character_color() const;

    [[nodiscard]] ColorScope using_color(VGA::CharacterColor color);
    [[nodiscard]] ColorScope using_fg_color(VGA::Color color);
    [[nodiscard]] ColorScope using_bg_color(VGA::Color color);

    void write_char(char c) override;

    void set_character_color(VGA::CharacterColor color);

protected:
    virtual void put_char(char c, size_t x, size_t y, VGA::CharacterColor color) = 0;

private:
    VGA::Color m_fg_color, m_bg_color;

    size_t m_cursor_x, m_cursor_y;
};