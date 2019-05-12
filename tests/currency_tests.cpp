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

#include <coinz/currency.hpp>

// clang-format: off
#include <gtest/gtest.h>

// clang-format: on

TEST(CurrencyTest, get_by_index)
{
    constexpr auto dummy = coinz::currency<int, float>{1, 2.5f};
    EXPECT_EQ(1, dummy.get<0>());
    EXPECT_EQ(2.5f, dummy.get<1>());
}

TEST(CurrencyTest, get_by_type)
{
    constexpr auto dummy = coinz::currency<int, float>{1, 2.5f};
    EXPECT_EQ(1, dummy.get<int>());
    EXPECT_EQ(2.5f, dummy.get<float>());
}
