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

#include <coinz/get_n.hpp>
#include <type_traits>


// clang-format: off
#include <gtest/gtest.h>

// clang-format: on

struct empty {
};

TEST(GetNTest, first)
{
    using dummy = coinz::get_n_t<0, char, int, float, empty, int, long>;
    constexpr auto result = ::std::is_same_v<char, dummy>;
    ASSERT_TRUE(result);
}

TEST(GetNTest, middle)
{
    using dummy = coinz::get_n_t<2, char, int, float, empty, int, long>;
    constexpr auto result = ::std::is_same_v<float, dummy>;
    ASSERT_TRUE(result);
}

TEST(GetNTest, last)
{
    using dummy = coinz::get_n_t<5, char, int, float, empty, int, long>;
    constexpr auto result = ::std::is_same_v<long, dummy>;
    ASSERT_TRUE(result);
}
