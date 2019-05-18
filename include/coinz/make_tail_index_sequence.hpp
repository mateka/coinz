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

#include <utility>


namespace coinz {

template<::std::size_t Offset, typename T>
struct offset_index_sequence;

template<::std::size_t Offset, ::std::size_t... Idx>
struct offset_index_sequence<Offset, ::std::index_sequence<Idx...>> {
    using type = ::std::index_sequence<(Offset + Idx)...>;
};

template<::std::size_t Offset, typename T>
using offset_index_sequence_t = typename offset_index_sequence<Offset, T>::type;

template<::std::size_t I, ::std::size_t N>
using make_tail_index_sequence =
    offset_index_sequence_t<I, ::std::make_index_sequence<N - I>>;

}  // namespace coinz
