// Copyright (c) 2023, Pedro Palacios Almendros.

#pragma once

#include <stddef.h>

namespace Pal {

    // TODO: Implement iterators
    // TODO: Take string views as constants

    class StringView {

    public:
        [[nodiscard]] const char *ptr_to_first_element() const;
        [[nodiscard]] size_t size() const;

        // TODO: Implement accessors (at, operator[])
        // TODO: Implement helpers (substr, find)

    private:
        const char *m_str;
        size_t m_size;
    };

}// namespace Pal