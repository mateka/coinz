/*
 * Copyright 2019 Mateusz Adamczyk
 *
 * Permission is hereby granted, free of charge, to any person obtaining
 * a copy of this software and associated documentation files (the "Software"),
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

#include <coinz/find_type.hpp>
#include <type_traits>

// clang-format: off
#include <gtest/gtest.h>
// clang-format: on

TEST(FindTypeTests, find_first)
{
    constexpr auto result =
        coinz::find_type_v<int, int, char, float, long, double>;
    EXPECT_EQ(result, 0);
}

TEST(FindTypeTests, find_middle)
{
    constexpr auto result =
        coinz::find_type_v<float, int, char, float, long, double>;
    EXPECT_EQ(result, 2);
}

TEST(FindTypeTests, find_last)
{
    constexpr auto result =
        coinz::find_type_v<double, int, char, float, long, double>;
    EXPECT_EQ(result, 4);
}
