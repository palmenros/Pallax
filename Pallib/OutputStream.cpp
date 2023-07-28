// Copyright (c) 2023, Pedro Palacios Almendros.

#include "OutputStream.h"

OutputStream &OutputStream::operator<<(char c) {
    writeChar(c);
    return *this;
}

OutputStream &OutputStream::operator<<(const char *str) {
    while (*str != '\0') {
        *this << *str;
        str++;
    }
    return *this;
}
