// Copyright (c) 2023, Pedro Palacios Almendros.

#include "StringView.h"

namespace Pal {

    size_t StringView::size() const {
        return m_size;
    }

    const char *StringView::ptr_to_first_element() const {
        return m_str;
    }

}// namespace Pal