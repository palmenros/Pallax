// Copyright (c) 2023, Pedro Palacios Almendros.

#pragma once

#include <stdint.h>

// IO port operations
void outb(uint16_t port, uint8_t val);
uint8_t inb(uint16_t port);