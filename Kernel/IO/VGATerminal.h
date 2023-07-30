// Copyright (c) 2023, Pedro Palacios Almendros.

#pragma once

#include "PalLib/Optional.h"
#include "Terminal.h"

class VGATerminal final : public Terminal {
public:
    static VGATerminal &the();
    static bool is_initialized();
    static void initialize(uint16_t *vga_buffer = (uint16_t *) VGA_BUFFER_PTR);

    size_t height() override;
    size_t width() override;

    // Default VGA_BUFFER_PTR
    static constexpr intptr_t VGA_BUFFER_PTR = 0xB8000;

protected:
    void put_char(char c, size_t x, size_t y, VGA::CharacterColor color) override;

    explicit VGATerminal(uint16_t *vga_buffer);

private:
    uint16_t *m_vga_buffer;

    [[nodiscard]] static uint16_t get_colored_vga_char(char c, VGA::CharacterColor color);

    static Pal::Optional<VGATerminal> s_maybe_terminal;
};
