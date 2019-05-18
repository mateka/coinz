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

#include <coinz/tuple/partial_sum.hpp>
#include <tuple>

// clang-format: off
#include <gtest/gtest.h>

// clang-format: on

TEST(TuplePartialSumTest, no_sum_returns_init)
{
    auto const dummy  = ::std::tuple{1, 2.5f, 2u, 3.5f};
    auto const init   = 3.14f;
    auto const result = coinz::tuple::partial_sum<0>(
        dummy, [](auto const a1, auto const a2) { return a1 + a2; }, init);
    EXPECT_EQ(init, result);
}

TEST(TuplePartialSumTest, sum_only_the_first)
{
    auto const dummy  = ::std::tuple{1, 2.5f, 2u, 3.5f};
    auto const result = coinz::tuple::partial_sum<1>(
        dummy, [](auto const a1, auto const a2) { return a1 + a2; }, 0.0f);
    EXPECT_EQ(1, result);
}

TEST(TuplePartialSumTest, sum_three_elements)
{
    auto const dummy  = ::std::tuple{1, 2.5f, 2u, 3.5f};
    auto const result = coinz::tuple::partial_sum<3>(
        dummy, [](auto const a1, auto const a2) { return a1 + a2; }, 0.0f);
    EXPECT_EQ(5.5f, result);
}

TEST(TuplePartialSumTest, sum_all_elements)
{
    auto const dummy = ::std::tuple{1, 2.5f, 2u, 3.5f};
    auto const result =
        coinz::tuple::partial_sum<::std::tuple_size_v<decltype(dummy)>>(
            dummy, [](auto const a1, auto const a2) { return a1 + a2; }, 0.0f);
    EXPECT_EQ(9.0f, result);
}

namespace {
template<typename T>
struct dummy_wrapper {
    dummy_wrapper(T t) : value{::std::move(t)} {}
    T const value;
};
}  // namespace

TEST(TuplePartialSumTest, sum_with_transform)
{
    auto const dummy  = ::std::tuple{dummy_wrapper(1),
                                    dummy_wrapper(2.5f),
                                    dummy_wrapper(2u),
                                    dummy_wrapper(3.5f)};
    auto const result = coinz::tuple::partial_sum<1>(
        dummy,
        [](auto const a1, auto const a2) { return a1.value + a2; },
        0.0f);
    EXPECT_EQ(1, result);
}

TEST(TuplePartialSumByIndexTest, sum_first)
{
    auto const dummy  = ::std::tuple{1, 2.5f, 2u, 3.5f};
    auto const result = coinz::tuple::partial_sum_by_index(
        dummy,
        ::std::index_sequence<0>{},
        [](auto const a1, auto const a2) { return a1 + a2; },
        0.0f);
    EXPECT_EQ(1, result);
}

TEST(TuplePartialSumByIndexTest, sum_third)
{
    auto const dummy  = ::std::tuple{1, 2.5f, 2u, 3.5f};
    auto const result = coinz::tuple::partial_sum_by_index(
        dummy,
        ::std::index_sequence<2>{},
        [](auto const a1, auto const a2) { return a1 + a2; },
        0.0f);
    EXPECT_EQ(2, result);
}

TEST(TuplePartialSumByIndexTest, sum_two)
{
    auto const dummy  = ::std::tuple{1, 2.5f, 2u, 3.5f};
    auto const result = coinz::tuple::partial_sum_by_index(
        dummy,
        ::std::index_sequence<1, 3>{},
        [](auto const a1, auto const a2) { return a1 + a2; },
        0.0f);
    EXPECT_EQ(6.0f, result);
}

TEST(TuplePartialSumByIndexTest, sum_last_three)
{
    auto const dummy  = ::std::tuple{1, 2.5f, 2u, 3.5f};
    auto const result = coinz::tuple::partial_sum_by_index(
        dummy,
        ::std::index_sequence<1, 2, 3>{},
        [](auto const a1, auto const a2) { return a1 + a2; },
        0.0f);
    EXPECT_EQ(8.0f, result);
}
