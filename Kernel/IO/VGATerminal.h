// Copyright (c) 2023, Pedro Palacios Almendros.

#pragma once

#include "Terminal.h"

class VGATerminal : public Terminal {
public:
    static VGATerminal &the();

    size_t height() override;
    size_t width() override;

protected:
    void put_char(char c, size_t x, size_t y, VGA::CharacterColor color) override;

    explicit VGATerminal(uint16_t *vga_buffer);

private:
    uint16_t *m_vga_buffer;

    [[nodiscard]] uint16_t get_colored_vga_char(char c, VGA::CharacterColor color) const;

    static VGATerminal s_terminal;
};
