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

#include <coinz/i_tail.hpp>
#include <type_traits>

// clang-format: off
#include <gtest/gtest.h>

// clang-format: on

TEST(ITailTest, from_first)
{
    using result   = coinz::i_tail_t<0, char, short, int>;
    using expected = coinz::types<char, short, int>;
    ASSERT_TRUE((::std::is_same_v<expected, result>) );
}

TEST(ITailTest, from_second)
{
    using result   = coinz::i_tail_t<1, char, short, int>;
    using expected = coinz::types<short, int>;
    ASSERT_TRUE((::std::is_same_v<expected, result>) );
}

TEST(ITailTest, from_third)
{
    using result   = coinz::i_tail_t<2, char, short, int, long>;
    using expected = coinz::types<int, long>;
    ASSERT_TRUE((::std::is_same_v<expected, result>) );
}

TEST(ITailTest, from_last)
{
    using result   = coinz::i_tail_t<3, char, short, int, long>;
    using expected = coinz::types<long>;
    ASSERT_TRUE((::std::is_same_v<expected, result>) );
}
