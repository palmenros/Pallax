// Copyright (c) 2023, Pedro Palacios Almendros.

#include "Terminal.h"

VGA::Color Terminal::get_fg_color() const {
    return m_fg_color;
}

VGA::Color Terminal::get_bg_color() const {
    return m_bg_color;
}

void Terminal::set_fg_color(VGA::Color fg_color) {
    this->m_fg_color = fg_color;
}

void Terminal::set_bg_color(VGA::Color bg_color) {
    this->m_bg_color = bg_color;
}

VGA::CharacterColor Terminal::get_character_color() const {
    return {m_fg_color, m_bg_color};
}


void Terminal::write_char(char c) {

    if (c != '\n') {
        put_char(c, m_cursor_x, m_cursor_y, get_character_color());
    }

    // Advance cursor
    m_cursor_x++;

    if (c == '\n' || m_cursor_x == width()) {
        // Switch to new line
        m_cursor_x = 0;
        m_cursor_y++;

        // TODO: Add scrolling
        // Maybe we have overflowed, in that case, move to the first line again and clear it
        if (m_cursor_y == height()) {
            m_cursor_y = 0;

            // TODO: Clearing the first line is not enough, because the terminal text will wrap
            //  Implement proper scrolling
            // Clear first line
            for (size_t x = 0; x < width(); x++) {
                put_char(' ', x, 0, get_character_color());
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
    set_fg_color(color.m_foreground);
    set_bg_color(color.m_background);
}

ColorScope Terminal::using_fg_color(VGA::Color color) {
    return using_color({color, m_bg_color});
}

ColorScope Terminal::using_bg_color(VGA::Color color) {
    return using_color({m_fg_color, color});
}

Terminal::Terminal(VGA::Color fg_color, VGA::Color bg_color) : m_fg_color(fg_color), m_bg_color(bg_color), m_cursor_x(0), m_cursor_y(0) {}

ColorScope::ColorScope(Terminal &terminal, VGA::CharacterColor color_to_be_restored)
    : m_terminal(terminal), m_color_to_be_restored(color_to_be_restored) {
}

ColorScope::~ColorScope() {
    m_terminal.set_character_color(m_color_to_be_restored);
}