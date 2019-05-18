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

#include <coinz/make_tail_index_sequence.hpp>
#include <type_traits>

// clang-format: off
#include <gtest/gtest.h>

// clang-format: on

TEST(OffsetIndexSequenceTest, offset_0)
{
    using result =
        coinz::offset_index_sequence_t<0, ::std::index_sequence<1, 3, 6>>;
    using expected          = ::std::index_sequence<1, 3, 6>;
    constexpr auto the_same = ::std::is_base_of_v<result, expected>;
    EXPECT_TRUE(the_same);
}

TEST(OffsetIndexSequenceTest, offset_2)
{
    using result =
        coinz::offset_index_sequence_t<2, ::std::index_sequence<1, 3, 6>>;
    using expected          = ::std::index_sequence<3, 5, 8>;
    constexpr auto the_same = ::std::is_base_of_v<result, expected>;
    EXPECT_TRUE(the_same);
}

TEST(MakeTailIndexSequenceTest, full_sequence)
{
    using result            = coinz::make_tail_index_sequence<0, 6>;
    using expected          = ::std::index_sequence<0, 1, 2, 3, 4, 5>;
    constexpr auto the_same = ::std::is_base_of_v<result, expected>;
    EXPECT_TRUE(the_same);
}

TEST(MakeTailIndexSequenceTest, from_first)
{
    using result            = coinz::make_tail_index_sequence<1, 6>;
    using expected          = ::std::index_sequence<1, 2, 3, 4, 5>;
    constexpr auto the_same = ::std::is_same_v<result, expected>;
    EXPECT_TRUE(the_same);
}

TEST(MakeTailIndexSequenceTest, from_third)
{
    using result            = coinz::make_tail_index_sequence<3, 6>;
    using expected          = ::std::index_sequence<3, 4, 5>;
    constexpr auto the_same = ::std::is_same_v<result, expected>;
    EXPECT_TRUE(the_same);
}
