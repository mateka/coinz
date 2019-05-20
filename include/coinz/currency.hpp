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
#include <cstdint>
#include <ratio>
#include <tuple>

namespace coinz {

namespace details {
    template<typename... Ts>
    struct amount_type {
        using type                  = ::std::common_type_t<Ts...>;
        static constexpr auto value = type{1};
    };

    template<::std::intmax_t A, ::std::intmax_t B, typename... Rest>
    struct amount_type<::std::ratio<A, B>, Rest...> {
        using type = ::std::ratio_multiply<
            ::std::ratio<A, B>,
            typename amount_type<Rest...>::type>;
        static constexpr auto value = type{};
    };

    template<::std::intmax_t A, ::std::intmax_t B>
    struct amount_type<::std::ratio<A, B>> {
        using type                  = std::ratio<A, B>;
        static constexpr auto value = type{};
    };

    template<typename... Ts>
    using amount_type_t = typename amount_type<Ts...>::type;

    template<typename... Ts>
    constexpr amount_type_t<Ts...> amount_type_v = amount_type<Ts...>::value;

    struct multiply {
        template<typename A, typename B>
        constexpr auto operator()(A const &a, B const &b) const
        {
            return a * b;
        }

        template<
            ::std::intmax_t A,
            ::std::intmax_t B,
            ::std::intmax_t C,
            ::std::intmax_t D>
        constexpr auto
        operator()(::std::ratio<A, B> a, ::std::ratio<C, D> b) const
            -> amount_type_t<decltype(a), decltype(b)>
        {
            return {};
        }
    };

}  // namespace details

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
            details::multiply{},
            details::amount_type_v<Parts...>);
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
