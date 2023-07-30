// Copyright (c) 2023, Pedro Palacios Almendros.

#pragma once

#include <stdint.h>

namespace Pal {

    class OutputStream {
    public:
        OutputStream &operator<<(char);
        OutputStream &operator<<(const char *);
        OutputStream &operator<<(char *);
        OutputStream &operator<<(bool);

        OutputStream &operator<<(uint32_t);
        OutputStream &operator<<(int32_t);

        OutputStream &operator<<(uint16_t);
        OutputStream &operator<<(uint8_t);
        OutputStream &operator<<(int16_t);
        OutputStream &operator<<(int8_t);

        OutputStream &operator<<(int);
        OutputStream &operator<<(unsigned int);

        OutputStream &operator<<(void *);

        template<class T>
        OutputStream &operator<<(T *ptr) {
            *this << (void *) ptr;
            return *this;
        }

    protected:
        virtual void
        write_char(char c) = 0;
    };

}// namespace Pal
