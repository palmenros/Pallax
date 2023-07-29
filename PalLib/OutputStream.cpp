// Copyright (c) 2023, Pedro Palacios Almendros.

#include "OutputStream.h"

namespace Pal {

    OutputStream &OutputStream::operator<<(char c) {
        write_char(c);
        return *this;
    }

    OutputStream &OutputStream::operator<<(const char *str) {
        while (*str != '\0') {
            *this << *str;
            str++;
        }
        return *this;
    }

    OutputStream &OutputStream::operator<<(bool b) {
        if (b) {
            *this << "true";
        } else {
            *this << "false";
        }

        return *this;
    }

}// namespace Pal