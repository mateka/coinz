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

#include <coinz/tuple/find_type.hpp>
#include <tuple>

// clang-format: off
#include <gtest/gtest.h>

// clang-format: on

TEST(TupleFindTypeTest, find_first)
{
    constexpr auto const dummy = ::std::tuple{1, 2.5f, 2u, 3.5};
    EXPECT_EQ(0, (coinz::tuple::find_type_v<int, decltype(dummy)>) );
}

TEST(TupleFindTypeTest, find_middle)
{
    constexpr auto const dummy = ::std::tuple{1, 2.5f, 2u, 3.5};
    EXPECT_EQ(2, (coinz::tuple::find_type_v<decltype(2u), decltype(dummy)>) );
}

TEST(TupleFindTypeTest, find_last)
{
    constexpr auto const dummy = ::std::tuple{1, 2.5f, 2u, 3.5};
    EXPECT_EQ(3, (coinz::tuple::find_type_v<double, decltype(dummy)>) );
}
