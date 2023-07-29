// Copyright (c) 2023, Pedro Palacios Almendros.

#pragma once

#include "StdLibExtras.h"

namespace Pal {

    // TODO: Test

    // TODO: Factor out trivially destructible objects contained in optional.
    // See http://www.club.cc.cmu.edu/~ajo/disseminate/2017-02-15-Optional-From-Scratch.pdf

    // TODO: Maybe implement something like nullopt?

    template<class T>
    class Optional {
    public:
        [[nodiscard]] bool has_value() const {
            return m_has_value;
        }

        void reset() {
            m_has_value = false;
            m_val.~T();
        }

        operator bool() const {
            return m_has_value;
        }

        // value

        [[nodiscard]] T &value() & {
            // TODO: ASSERT has_value
            return m_val;
        }

        [[nodiscard]] const T &value() const & {
            // TODO: ASSERT has_value
            return m_val;
        }

        [[nodiscard]] T &&value() && {
            // TODO: ASSERT has_value
            return move(m_val);
        }

        [[nodiscard]] const T &&value() const && {
            return move(m_val);
        }

        // value_or

        template<class U>
        [[nodiscard]] T value_or(U &&u) && {
            if (m_has_value) {
                return move(m_val);
            } else {
                return static_cast<T>(forward<U>(u));
            }
        }

        template<class U>
        [[nodiscard]] T value_or(U &&u) const & {
            if (m_has_value) {
                return m_val;
            } else {
                return static_cast<T>(forward<U>(u));
            }
        }

        // operator*

        constexpr T &operator*() & {
            return m_val;
        }

        constexpr const T &operator*() const & {
            return m_val;
        }

        constexpr T &&operator*() && {
            return move(m_val);
        }

        constexpr const T &&operator*() const && {
            return move(m_val);
        }

    public:
        // Constructors and assignment operators

        Optional()
            : m_dummy(0), m_has_value(false) {}

        Optional(const Optional<T> &t)
            : m_has_value(t.m_has_value) {
            if (m_has_value) {
                ::new (&m_val) T(t.m_val);
            }
        }

        Optional(Optional<T> &&t)
            : m_has_value(t.m_has_value) {
            if (m_has_value) {
                ::new (&m_val) T(move(t.m_val));
            }
        }

        Optional(const T &t)
            : m_val(t), m_has_value(true) {}

        Optional(const T &&t)
            : m_val(t), m_has_value(true) {}

        Optional<T> &operator=(const Optional<T> &other) {
            if (m_has_value && other.m_has_value) {
                m_val = other.m_val;
            } else if (m_has_value && !other.m_has_value) {
                m_val.~T();
                m_has_value = false;
            } else if (!m_has_value && other.m_has_value) {
                ::new (&m_val) T(other.m_val);
                m_has_value = true;
            }
            return *this;
        }

        Optional<T> &operator=(Optional<T> &&other) {
            if (m_has_value && other.m_has_value) {
                m_val = move(other.m_val);
            } else if (m_has_value && !other.m_has_value) {
                m_val.~T();
                m_has_value = false;
            } else if (!m_has_value && other.m_has_value) {
                ::new (&m_val) T(move(other.m_val));
                m_has_value = true;
            }
            return *this;
        }

        // Template needed so that opt = {} makes the optional object empty instead of assigning a default-initialized object.
        // See https://stackoverflow.com/questions/33511641/overload-resolution-assignment-of-empty-braces

        template<class U, EnableIfT<IsSame<U, T>{}, T> = 0>
        Optional<T> &operator=(const T &other) {
            if (&m_val != &other) {
                if (m_has_value) {
                    m_val = other;
                } else {
                    ::new (&m_val) T(other);
                    m_has_value = true;
                }
            }
            return *this;
        }

        template<class U, EnableIfT<IsSame<U, T>{}, T> = 0>
        Optional<T> &operator=(T &&other) {
            if (&m_val != &other) {
                if (m_has_value) {
                    m_val = other;
                } else {
                    ::new (&m_val) T(other);
                    m_has_value = true;
                }
            }
            return *this;
        }

        ~Optional() {
            if (m_has_value) {
                m_val.~T();
            }
        }

    private:
        union {
            char m_dummy;
            T m_val;
        };

        bool m_has_value;
    };

}// namespace Pal