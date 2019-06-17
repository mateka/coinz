/*
 * Copyright 2019 Mateusz Adamczyk
 *
 * Permission is hereby granted, free of charge, to any person obtaining
 * a copy of this software and associated documentation files(the "Source"),
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

#include <coinz/binary_to_nary.hpp>
#include <coinz/get_n.hpp>
#include <coinz/i_tail.hpp>
#include <coinz/to_ratio.hpp>
#include <cstdint>
#include <type_traits>

namespace coinz {

namespace detail {

    template<typename... Ts>
    struct multiply {
		using type = binary_to_nary_t<::std::ratio_multiply, ::std::ratio<1>, to_ratio_t<Ts>...>;
    };

	template<template<typename...> typename Wrapper, typename... Ts>
    struct multiply<Wrapper<Ts...>> : public multiply<Ts...> {};

    template<typename... Ts>
	using multiply_t = typename multiply<Ts...>::type;
}  // namespace details

template<typename... Parts>
class currency {
public:
    template<::std::size_t I>
    using type_n = get_n_t<I, Parts...>;

    template<::std::size_t I>
    using amount_n = detail::multiply_t<typename i_tail<I, Parts...>::type>;
};

}  // namespace coinz
