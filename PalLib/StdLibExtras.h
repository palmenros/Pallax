// Copyright (c) 2023, Pedro Palacios Almendros.

#pragma once

#include "TypeTraits.h"
#include <stddef.h>

// New
inline void *operator new(size_t, void *p) noexcept { return p; }
inline void *operator new[](size_t, void *p) noexcept { return p; }
inline void operator delete(void *, void *) noexcept {};
inline void operator delete[](void *, void *) noexcept {};

namespace Pal {
    
    // Move

    template<typename T>
    constexpr typename RemoveReference<T>::Type &&move(T &&arg) {
        return static_cast<typename RemoveReference<T>::Type &&>(arg);
    }

    // Forward

    template<class T>
    inline constexpr T &&forward(typename RemoveReference<T>::Type &t) noexcept {
        return static_cast<T &&>(t);
    }

    template<class T>
    inline constexpr T &&forward(typename RemoveReference<T>::Type &&t) noexcept {
        static_assert(!IsLValueReference<T>::value,
                      "Can not forward an rvalue as an lvalue.");
        return static_cast<T &&>(t);
    }


}// namespace Pal