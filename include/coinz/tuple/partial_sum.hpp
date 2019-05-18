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

#include <coinz/binary_op_aplicator.hpp>
#include <iostream>
#include <tuple>


namespace coinz::tuple {

template<typename Op, typename Result, typename Tuple, ::std::size_t... Idx>
auto partial_sum_by_index(
    Tuple const &t, ::std::index_sequence<Idx...>, Op op, Result init = {})
    -> Result
{
    auto op_ = binary_op_applicator(
        ::std::forward<Op>(op), ::std::forward<Result>(init));
    return op_(std::get<Idx>(t)...);
}

template<std::size_t N, typename Op, typename Result, typename... Args>
auto partial_sum(::std::tuple<Args...> const &t, Op op, Result init = {})
    -> Result
{
    if constexpr (N == 0) {
        return init;
    }
    else {
        return partial_sum_by_index(
            t,
            ::std::make_index_sequence<N>(),
            ::std::forward<Op>(op),
            ::std::forward<Result>(init));
    }
}

}  // namespace coinz::tuple
