// Copyright (c) 2023, Pedro Palacios Almendros.

#pragma once

#include "TypeTraits.h"
#include <stddef.h>

// Byte sizes
#define KB 1024
#define MB (1024 * KB)
#define GB (1024 * MB)

// New
inline void *operator new(size_t, void *p) noexcept { return p; }
inline void *operator new[](size_t, void *p) noexcept { return p; }
inline void operator delete(void *, void *) noexcept {}
inline void operator delete[](void *, void *) noexcept {}

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

// Assert

void assert_impl(bool condition, const char *msg);

// These macros are needed to stringize the __LINE__ integer constant

#ifndef ASSERT

#define PAL_STRINGIZE(x) PAL_STRINGIZE2(x)
#define PAL_STRINGIZE2(x) #x
#define __LINE_STRING__ PAL_STRINGIZE(__LINE__)

#define ASSERT(COND) ::assert_impl(COND, "Assertion failed: " #COND " at " __FILE__ ", line " __LINE_STRING__)

#endif