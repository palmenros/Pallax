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

    OutputStream &OutputStream::operator<<(char *str) {
        *this << ((const char *) str);
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

    OutputStream &OutputStream::operator<<(uint32_t x) {
        // The maximum uint32_t value is 4,294,967,295, which fits in 10 characters.
        // The 11th value is a null terminator (which is the character 0)
        static char buffer[11] = {0};

        // TODO: Maybe there is a faster algorithm than module and dividing?
        int8_t idx = 9;

        do {
            buffer[idx] = '0' + ((uint8_t) (x % 10));
            idx--;
            x /= 10;
        } while (x != 0);

        *this << (buffer + idx + 1);
        return *this;
    }

    OutputStream &OutputStream::operator<<(int32_t x) {
        if (x < 0) {
            *this << '-';

            if (x == INT32_MIN) {
                *this << ((uint32_t) INT32_MAX + 1);
                return *this;
            }

            x = -x;
        }
        *this << ((uint32_t) x);

        return *this;
    }

    OutputStream &OutputStream::operator<<(uint16_t x) {
        *this << ((uint32_t) x);
        return *this;
    }

    OutputStream &OutputStream::operator<<(uint8_t x) {
        *this << ((uint32_t) x);
        return *this;
    }

    OutputStream &OutputStream::operator<<(int16_t x) {
        *this << ((int32_t) x);
        return *this;
    }

    OutputStream &OutputStream::operator<<(int8_t x) {
        *this << ((int32_t) x);
        return *this;
    }

    OutputStream &OutputStream::operator<<(int x) {
        *this << ((int32_t) x);
        return *this;
    }

    OutputStream &OutputStream::operator<<(unsigned int x) {
        *this << ((uint32_t) x);
        return *this;
    }

    OutputStream &OutputStream::operator<<(void *ptr) {
        *this << "0x";

        // For 32 bit pointers we need only 8 hex characters.
        // The 9th character is for null termination
        static char buffer[9] = {0};

        int8_t idx = 9;

        uintptr_t x = (uintptr_t) ptr;

        do {
            uint8_t val = (uint8_t) (x & 0b1111);
            if (val < 10) {
                buffer[idx] = '0' + val;
            } else {
                buffer[idx] = 'A' + (val - 10);
            }

            idx--;
            x >>= 4;
        } while (x != 0);

        *this << (buffer + idx + 1);
        return *this;
    }

}// namespace Pal