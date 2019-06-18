/*
 * Copyright 2019 Mateusz Adamczyk
 *
 * Permission is hereby granted, free of charge, to any person obtaining
 * a copy of this software and associated documentation files(the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modify, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom
 * the Software is furnished to do so, subject to the following conditions:
 * - The above copyright notice and this permission notice shall be included
 *   in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES
 * OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
 * IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM,
 * DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,
 * TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH
 * THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */
#pragma once

#include <type_traits>

namespace coinz {

namespace detail {
    template<typename Searched, ::std::size_t N, typename... Ts>
    struct find_type_impl;

    template<
        typename Searched,
        ::std::size_t N,
        bool          Found,
        typename Head,
        typename... Ts>
    struct find_type_iteration : find_type_impl<Searched, N + 1, Ts...> {
    };

    template<typename Searched, ::std::size_t N, typename Head, typename... Ts>
    struct find_type_iteration<Searched, N, true, Head, Ts...>
        : ::std::integral_constant<decltype(N), N> {
        static_assert(
            ::std::is_same_v<Searched, Head>, "Find type implementation error");
    };

    template<typename Searched, ::std::size_t N, typename... Ts>
    struct find_type_impl {
    };

    template<typename Searched, ::std::size_t N, typename Head, typename... Ts>
    struct find_type_impl<Searched, N, Head, Ts...>
        : find_type_iteration<
              Searched,
              N,
              ::std::is_same_v<Searched, Head>,
              Head,
              Ts...> {
    };
}  // namespace detail

template<typename Searched, typename... Ts>
struct find_type : detail::find_type_impl<Searched, 0, Ts...> {
};

template<typename Searched, typename... Ts>
constexpr auto find_type_v = find_type<Searched, Ts...>::value;

}  // namespace coinz
