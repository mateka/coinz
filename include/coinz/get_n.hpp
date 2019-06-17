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

#include <utility>

namespace coinz {

template<::std::size_t I, typename... Ts>
struct get_n {
};

template<::std::size_t I, typename First, typename... Ts>
struct get_n<I, First, Ts...> {
    static_assert(I <= sizeof...(Ts), "Too large parameter pack index");

    using type = typename get_n<I - 1, Ts...>::type;
};

template<typename First, typename... Ts>
struct get_n<0, First, Ts...> {
    using type = First;
};

template<::std::size_t I, typename... Ts>
using get_n_t = typename get_n<I, Ts...>::type;

}  // namespace coinz
