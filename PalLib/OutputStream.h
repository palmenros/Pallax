// Copyright (c) 2023, Pedro Palacios Almendros.

#pragma once

#include <stdint.h>

namespace Pal {

    class OutputStream {
    public:
        OutputStream &operator<<(char);
        OutputStream &operator<<(const char *);
        OutputStream &operator<<(bool);

        // TODO: Add support for numbers

    protected:
        virtual void
        write_char(char c) = 0;
    };

};// namespace Pal
