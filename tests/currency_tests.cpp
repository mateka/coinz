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
#include <ratio>
#include <type_traits>


// clang-format: off
#include <gtest/gtest.h>


// clang-format: on

template<auto i>
using ic = ::std::integral_constant<decltype(i), i>;

template<auto a, auto b = 1>
using r = ::std::ratio<a, b>;

TEST(IntCurrencyIndexTest, type_n_first)
{
    // 1$ = 10 cents, store amount with 1/50 cent accuracy
    using dummy           = coinz::currency<ic<100>, ic<50>>;
    constexpr auto result = ::std::is_same_v<ic<100>, dummy::type_n<0>>;
    EXPECT_TRUE(result);
}

TEST(IntCurrencyIndexTest, type_n_last)
{
    // 1$ = 10 cents, store amount with 1/50 cent accuracy
    using dummy           = coinz::currency<ic<100>, ic<50>>;
    constexpr auto result = ::std::is_same_v<ic<50>, dummy::type_n<1>>;
    EXPECT_TRUE(result);
}

TEST(RatioCurrencyIndexTest, type_n_first)
{
    using dummy           = coinz::currency<r<3, 2>, r<10>>;
    constexpr auto result = ::std::is_same_v<r<3, 2>, dummy::type_n<0>>;
    EXPECT_TRUE(result);
}

TEST(RatioCurrencyIndexTest, type_n_last)
{
    using dummy           = coinz::currency<r<3, 2>, r<10>>;
    constexpr auto result = ::std::is_same_v<r<10>, dummy::type_n<1>>;
    EXPECT_TRUE(result);
}

// TEST(CurrencyIndexTest, check_amount_n_int)
// {
//     // 1$ = 10 cents, store amount with 1/50 cent accuracy
//     constexpr auto dummy = coinz::currency<100, 50>{};
//     EXPECT_EQ(100 * 50, dummy.amount_n<0>());
//     EXPECT_EQ(50, dummy.amount_n<1>());
// }

// namespace {

// struct gold {
//     explicit constexpr gold(int const amount) : amount_{amount} {}
//     constexpr gold(gold const &) = default;

//     constexpr int  value() const { return amount_; }
//     constexpr void value(int const v) { amount_ = v; }

//     int amount_;
// };

// struct silver {
//     explicit constexpr silver(int const amount) : amount_{amount} {}
//     constexpr silver(silver const &) = default;

//     constexpr int  value() const { return amount_; }
//     constexpr void value(int const v) { amount_ = v; }

//     int amount_;
// };

// struct copper {
//     explicit constexpr copper(int const amount) : amount_{amount} {}
//     constexpr copper(copper const &) = default;

//     constexpr int  value() const { return amount_; }
//     constexpr void value(int const v) { amount_ = v; }

//     int amount_;
// };

// template<typename T>
// bool operator==(T const &a, T const &b)
// {
//     return a.value() == b.value();
// }

// }  // namespace

// TEST(CurrencyIndexTest, check_sibling_amount_custom_types)
// {
//     constexpr auto dummy = coinz::currency<gold<12>, silver<64>,
//     copper<1>>{}; EXPECT_EQ(gold{12}, dummy.sibling_amount<0>());
//     EXPECT_EQ(silver{64}, dummy.sibling_amount<1>());
//     EXPECT_EQ(copper{1}, dummy.sibling_amount<2>());
// }

// TEST(CurrencyIndexTest, check_amount_n_custom_types)
// {
//     constexpr auto dummy = coinz::currency<gold<12>, silver<64>,
//     copper<1>>{}; EXPECT_EQ(copper{12 * 64}, dummy.amount_n<0>());
//     EXPECT_EQ(copper{64}, dummy.amount_n<1>());
//     EXPECT_EQ(copper{1}, dummy.amount_n<2>());
// }

// TEST(CurrencyTypeTest, check_sibling_amount)
// {
//     constexpr auto dummy = coinz::currency<gold<12>, silver<64>,
//     copper<1>>{}; EXPECT_EQ(gold{12}, dummy.sibling_amount<gold>());
//     EXPECT_EQ(silver{64}, dummy.sibling_amount<silver>());
//     EXPECT_EQ(copper{1}, dummy.sibling_amount<copper>());
// }

// TEST(CurrencyTypeTest, check_amount_n)
// {
//     constexpr auto dummy = coinz::currency<gold<12>, silver<64>,
//     copper<1>>{}; EXPECT_EQ(copper{12 * 64}, dummy.amount_n<gold>());
//     EXPECT_EQ(copper{64}, dummy.amount_n<silver>());
//     EXPECT_EQ(copper{1}, dummy.amount_n<copper>());
// }
