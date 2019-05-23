/*
 * Copyright 2019 mateka
 *
 * Permission is hereby granted, free of charge, to any person obtaining
 * a copy of this software and associated documentation files(the
),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modify, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom
 * the Software is furnished to do so, subject to the following conditions:
 * - The above copyright notice and this permission notice shall be included
 *   in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED
, WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES
 * OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
 * IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM,
 * DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,
 * TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH
 * THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */
#pragma once

#include <coinz/make_tail_index_sequence.hpp>
#include <coinz/tuple/partial_sum.hpp>
#include <tuple>
#include <type_traits>

namespace coinz {

namespace details {
    template<typename T, bool IsNumeric>
    struct value_type {
        using type = decltype(::std::declval<T>().value());
    };

    template<typename T>
    struct value_type<T, true> {
        using type = T;
    };

    template<typename T, bool IsNumeric>
    struct value_getter {
        constexpr auto operator()(T const &v) const { return v.value(); }
    };

    template<typename T>
    struct value_getter<T, true> {
        constexpr auto operator()(T const &v) const { return v; }
    };
}  // namespace details

template<typename T>
struct value_type
    : public details::
          value_type<T, ::std::is_arithmetic_v<::std::remove_cvref_t<T>>> {
};

template<typename T>
using value_t = typename value_type<T>::type;

template<typename T>
struct value_getter
    : public details::
          value_getter<T, ::std::is_arithmetic_v<::std::remove_cvref_t<T>>> {
};

template<typename T, typename... Ts>
struct amount_type : public amount_type<Ts...> {
};

template<typename T>
struct amount_type<T> {
    using type                  = T;
    static constexpr auto value = type{1};
};

template<typename... Ts>
using amount_type_t = typename amount_type<Ts...>::type;

template<typename... Ts>
constexpr amount_type_t<Ts...> amount_type_v = amount_type<Ts...>::value;

template<typename... Parts>
class currency {
public:
    explicit constexpr currency(Parts... parts)
        : m_parts{::std::forward<Parts>(parts)...}
    {
    }

    template<std::size_t I>
    constexpr auto amount_n() const noexcept
    {
        return tuple::partial_sum_by_index(
            m_parts,
            make_tail_index_sequence<I, sizeof...(Parts)>{},
            [](auto const a, auto const b) {
                return amount_type_t<Parts...>{value_getter<decltype(a)>{}(
                    a) *value_getter<decltype(b)>{}(b)};
            },
            amount_type_v<Parts...>);
    }

    template<std::size_t I>
    constexpr auto sibling_amount() const noexcept
    {
        return ::std::get<I>(m_parts);
    }

private:
    ::std::tuple<Parts...> m_parts;
};

}  // namespace coinz
