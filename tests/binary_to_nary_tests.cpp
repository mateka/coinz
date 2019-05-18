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

#include <coinz/binary_to_nary.hpp>

// clang-format: off
#include <gtest/gtest.h>

// clang-format: on

TEST(BinaryOpApplicatorTest, single_value)
{
    auto wrapper = coinz::binary_to_nary{[](int a, int b) { return a + b; }, 0};
    EXPECT_EQ(1, wrapper(1));
}

TEST(BinaryOpApplicatorTest, two_values)
{
    auto wrapper = coinz::binary_to_nary{[](int a, int b) { return a + b; }, 0};
    EXPECT_EQ(4, wrapper(1, 3));
}

TEST(BinaryOpApplicatorTest, three_values)
{
    auto wrapper = coinz::binary_to_nary{[](int a, int b) { return a + b; }, 0};
    EXPECT_EQ(8, wrapper(1, 3, 4));
}

TEST(BinaryOpApplicatorTest, four_values)
{
    auto wrapper = coinz::binary_to_nary{[](int a, int b) { return a + b; }, 0};
    EXPECT_EQ(10, wrapper(1, 3, 4, 2));
}

TEST(BinaryOpApplicatorTest, five_values)
{
    auto wrapper = coinz::binary_to_nary{[](int a, int b) { return a + b; }, 0};
    EXPECT_EQ(111, wrapper(1, 3, 4, 2, 101));
}
