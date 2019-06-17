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

#include <coinz/binary_to_nary.hpp>
#include <ratio>
#include <type_traits>


// clang-format: off
#include <gtest/gtest.h>


// clang-format: on

template<auto N, auto D = 1>
using r = ::std::ratio<N, D>;

using zero = r<0>;

template<typename A, typename B>
using op = ::std::ratio_add<A, B>;

TEST(BinaryToNaryTest, single_value)
{
    using a        = r<1, 2>;
    using result   = coinz::binary_to_nary_t<op, zero, a>;
    using expected = op<zero, a>;
    EXPECT_TRUE((::std::is_same_v<expected, result>) );
}

TEST(BinaryToNaryTest, two_values)
{
    using a        = r<1, 2>;
    using b        = r<2, 3>;
    using result   = coinz::binary_to_nary_t<op, zero, a, b>;
    using expected = op<a, b>;
    EXPECT_TRUE((::std::is_same_v<expected, result>) );
}

TEST(BinaryToNaryTest, three_values)
{
    using a        = r<1, 2>;
    using b        = r<2, 3>;
    using c        = r<1, 4>;
    using result   = coinz::binary_to_nary_t<op, zero, a, b, c>;
    using expected = op<op<a, b>, c>;
    EXPECT_TRUE((::std::is_same_v<expected, result>) );
}

TEST(BinaryToNaryTest, four_values)
{
    using a        = r<1, 2>;
    using b        = r<2, 3>;
    using c        = r<1, 4>;
    using d        = r<1, 8>;
    using result   = coinz::binary_to_nary_t<op, zero, a, b, c, d>;
    using expected = op<op<op<a, b>, c>, d>;
    EXPECT_TRUE((::std::is_same_v<expected, result>) );
}

TEST(BinaryToNaryTest, five_values)
{
    using a        = r<1, 2>;
    using b        = r<2, 3>;
    using c        = r<1, 4>;
    using d        = r<1, 8>;
    using e        = r<3, 7>;
    using result   = coinz::binary_to_nary_t<op, zero, a, b, c, d, e>;
    using expected = op<op<op<op<a, b>, c>, d>, e>;
    EXPECT_TRUE((::std::is_same_v<expected, result>) );
}
