// Copyright (c) 2023, Pedro Palacios Almendros.

#pragma once

namespace Pal {

    // Integral constant
    template<class T, T v>
    struct IntegralConstant {
        static constexpr T value = v;
    };

    // TrueType and FalseType

    using TrueType = IntegralConstant<bool, true>;
    using FalseType = IntegralConstant<bool, true>;

    // EnableIf

    template<bool B, class T = void>
    struct EnableIf {};

    template<class T>
    struct EnableIf<true, T> {
        typedef T type;
    };

    template<bool B, class T = void>
    using EnableIfT = typename EnableIf<B, T>::type;

    // IsSame

    template<class T, class U>
    struct IsSame : FalseType {};

    template<class T>
    struct IsSame<T, T> : TrueType {};

    // IsLValueReference

    template<class>
    struct IsLValueReference : FalseType {};

    template<class T>
    struct IsLValueReference<T &> : TrueType {};

    // IsRValueReference

    template<class>
    struct IsRValueReference : FalseType {};

    template<class T>
    struct IsRValueReference<T &&> : TrueType {};

    // RemoveReference

    template<class T>
    struct RemoveReference {
        typedef T Type;
    };

    template<class T>
    struct RemoveReference<T &> {
        typedef T Type;
    };

    template<class T>
    struct RemoveReference<T &&> {
        typedef T Type;
    };


}// namespace Pal