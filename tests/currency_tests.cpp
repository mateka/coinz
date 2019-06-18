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

TEST(IntCurrencyIndexTest, amount_n_first)
{
    // 1$ = 10 cents, store amount with 1/50 cent accuracy
    using dummy = coinz::currency<ic<100>, ic<50>>;
    constexpr auto result =
        ::std::ratio_equal_v<r<100 * 50>, dummy::amount_n<0>>;
    EXPECT_TRUE(result);
}

TEST(IntCurrencyIndexTest, amount_n_last)
{
    // 1$ = 10 cents, store amount with 1/50 cent accuracy
    using dummy           = coinz::currency<ic<100>, ic<50>>;
    constexpr auto result = ::std::ratio_equal_v<r<50>, dummy::amount_n<1>>;
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

TEST(RatioCurrencyIndexTest, amount_n_first)
{
    using dummy           = coinz::currency<r<3, 2>, r<10>>;
    constexpr auto result = ::std::ratio_equal_v<r<30, 2>, dummy::amount_n<0>>;
    EXPECT_TRUE(result);
}

TEST(RatioCurrencyIndexTest, amount_n_last)
{
    using dummy           = coinz::currency<r<3, 2>, r<10>>;
    constexpr auto result = ::std::ratio_equal_v<r<10>, dummy::amount_n<1>>;
    EXPECT_TRUE(result);
}

namespace metafunction {

struct gold {
    using type = ::std::ratio<39, 4>;  // 12 3/4
};

struct silver {
    using type = ::std::ratio<13, 2>;  // 6 1/2
};

struct copper {
    using type = ::std::integral_constant<int, 10>;
};

}  // namespace metafunction

TEST(MetafunctionCurrencyTypeTest, type_n_first)
{
    using namespace metafunction;
    using dummy           = coinz::currency<gold, silver, copper>;
    constexpr auto result = ::std::is_same_v<gold, dummy::type_n<0>>;
    EXPECT_TRUE(result);
}

TEST(MetafunctionCurrencyTypeTest, type_n_middle)
{
    using namespace metafunction;
    using dummy           = coinz::currency<gold, silver, copper>;
    constexpr auto result = ::std::is_same_v<silver, dummy::type_n<1>>;
    EXPECT_TRUE(result);
}

TEST(MetafunctionCurrencyTypeTest, type_n_last)
{
    using namespace metafunction;
    using dummy           = coinz::currency<gold, silver, copper>;
    constexpr auto result = ::std::is_same_v<copper, dummy::type_n<2>>;
    EXPECT_TRUE(result);
}

TEST(MetafunctionCurrencyTypeTest, amount_n_first)
{
    using namespace metafunction;
    using dummy = coinz::currency<gold, silver, copper>;
    constexpr auto result =
        ::std::ratio_equal_v<r<39 * 13 * 10, 4 * 2>, dummy::amount_n<0>>;
    EXPECT_TRUE(result);
}

TEST(MetafunctionCurrencyTypeTest, amount_n_middle)
{
    using namespace metafunction;
    using dummy = coinz::currency<gold, silver, copper>;
    constexpr auto result =
        ::std::ratio_equal_v<r<13 * 10, 2>, dummy::amount_n<1>>;
    EXPECT_TRUE(result);
}

TEST(MetafunctionCurrencyTypeTest, amount_n_last)
{
    using namespace metafunction;
    using dummy           = coinz::currency<gold, silver, copper>;
    constexpr auto result = ::std::ratio_equal_v<r<10>, dummy::amount_n<2>>;
    EXPECT_TRUE(result);
}

TEST(MetafunctionCurrencyTypeTest, type_first)
{
    using namespace metafunction;
    using dummy           = coinz::currency<gold, silver, copper>;
    constexpr auto result = ::std::is_same_v<gold, dummy::type<gold>>;
    EXPECT_TRUE(result);
}

TEST(MetafunctionCurrencyTypeTest, type_middle)
{
    using namespace metafunction;
    using dummy           = coinz::currency<gold, silver, copper>;
    constexpr auto result = ::std::is_same_v<silver, dummy::type<silver>>;
    EXPECT_TRUE(result);
}

TEST(MetafunctionCurrencyTypeTest, type_last)
{
    using namespace metafunction;
    using dummy           = coinz::currency<gold, silver, copper>;
    constexpr auto result = ::std::is_same_v<copper, dummy::type<copper>>;
    EXPECT_TRUE(result);
}

TEST(MetafunctionCurrencyTypeTest, amount_first)
{
    using namespace metafunction;
    using dummy = coinz::currency<gold, silver, copper>;
    constexpr auto result =
        ::std::ratio_equal_v<r<39 * 13 * 10, 4 * 2>, dummy::amount<gold>>;
    EXPECT_TRUE(result);
}

TEST(MetafunctionCurrencyTypeTest, amount_middle)
{
    using namespace metafunction;
    using dummy = coinz::currency<gold, silver, copper>;
    constexpr auto result =
        ::std::ratio_equal_v<r<13 * 10, 2>, dummy::amount<silver>>;
    EXPECT_TRUE(result);
}

TEST(MetafunctionCurrencyTypeTest, amount_last)
{
    using namespace metafunction;
    using dummy           = coinz::currency<gold, silver, copper>;
    constexpr auto result = ::std::ratio_equal_v<r<10>, dummy::amount<copper>>;
    EXPECT_TRUE(result);
}

namespace inheritance {

struct gold : ::std::ratio<39, 4> {  // 12 3/4
};

struct silver : ::std::ratio<13, 2> {  // 6 1/2
};

struct copper : ::std::integral_constant<int, 10> {
};

}  // namespace inheritance

TEST(InheritanceCurrencyTypeTest, type_n_first)
{
    using namespace inheritance;
    using dummy           = coinz::currency<gold, silver, copper>;
    constexpr auto result = ::std::is_same_v<gold, dummy::type_n<0>>;
    EXPECT_TRUE(result);
}

TEST(InheritanceCurrencyTypeTest, type_n_middle)
{
    using namespace inheritance;
    using dummy           = coinz::currency<gold, silver, copper>;
    constexpr auto result = ::std::is_same_v<silver, dummy::type_n<1>>;
    EXPECT_TRUE(result);
}

TEST(InheritanceCurrencyTypeTest, type_n_last)
{
    using namespace inheritance;
    using dummy           = coinz::currency<gold, silver, copper>;
    constexpr auto result = ::std::is_same_v<copper, dummy::type_n<2>>;
    EXPECT_TRUE(result);
}

TEST(InheritanceCurrencyTypeTest, amount_n_first)
{
    using namespace inheritance;
    using dummy = coinz::currency<gold, silver, copper>;
    constexpr auto result =
        ::std::ratio_equal_v<r<39 * 13 * 10, 4 * 2>, dummy::amount_n<0>>;
    EXPECT_TRUE(result);
}

TEST(InheritanceCurrencyTypeTest, amount_n_middle)
{
    using namespace inheritance;
    using dummy = coinz::currency<gold, silver, copper>;
    constexpr auto result =
        ::std::ratio_equal_v<r<13 * 10, 2>, dummy::amount_n<1>>;
    EXPECT_TRUE(result);
}

TEST(InheritanceCurrencyTypeTest, amount_n_last)
{
    using namespace inheritance;
    using dummy           = coinz::currency<gold, silver, copper>;
    constexpr auto result = ::std::ratio_equal_v<r<10>, dummy::amount_n<2>>;
    EXPECT_TRUE(result);
}
