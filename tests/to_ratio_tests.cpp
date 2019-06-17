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

#include <coinz/to_ratio.hpp>
#include <type_traits>

// clang-format: off
#include <gtest/gtest.h>


// clang-format: on

TEST(ToRatioTests, from_std_integral_constant)
{
    using result   = coinz::to_ratio_t<::std::integral_constant<int, 2>>;
    using expected = ::std::ratio<2>;
    EXPECT_TRUE((::std::is_same_v<expected, result>) );
}

TEST(ToRatioTests, from_std_ratio)
{
    using result   = coinz::to_ratio_t<::std::ratio<1, 2>>;
    using expected = ::std::ratio<1, 2>;
    EXPECT_TRUE((::std::is_same_v<expected, result>) );
}

template<short x>
struct ic {
};

TEST(ToRatioTests, from_custom_integral_constant)
{
    using result   = coinz::to_ratio_t<ic<3>>;
    using expected = ::std::ratio<3>;
    EXPECT_TRUE((::std::is_same_v<expected, result>) );
}
