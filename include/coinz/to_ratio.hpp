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
#pragma once

#include <cstdint>
#include <ratio>

namespace coinz {

template<typename T>
struct to_ratio;

namespace detail {
    template<::std::intmax_t N, ::std::intmax_t D>
    inline ::std::true_type use_base_type(::std::ratio<N, D> const &)
    {
        return {};
    }
    template<auto i, template<typename T, T c> typename IntegralConstant>
    inline ::std::true_type
    use_base_type(IntegralConstant<decltype(i), i> const &)
    {
        return {};
    }
    template<auto i, template<auto c> typename IntegralConstant>
    inline ::std::true_type use_base_type(IntegralConstant<i> const &)
    {
        return {};
    }
    inline ::std::false_type use_base_type(...) { return {}; }

    template<::std::intmax_t N, ::std::intmax_t D>
    inline ::std::ratio<N, D> base_type(::std::ratio<N, D> const &)
    {
        return {};
    }
    template<auto i, template<typename T, T c> typename IntegralConstant>
    inline ::std::ratio<i> base_type(IntegralConstant<decltype(i), i> const &)
    {
        return {};
    }
    template<auto i, template<auto c> typename IntegralConstant>
    inline ::std::ratio<i> base_type(IntegralConstant<i> const &)
    {
        return {};
    }

    template<typename T, typename UseBaseType = ::std::false_type>
    struct to_ratio_impl {
        using type = typename to_ratio<typename T::type>::type;
    };
    template<typename T>
    struct to_ratio_impl<T, ::std::true_type> {
        using type = decltype(detail::base_type(::std::declval<T>()));
    };
}  // namespace detail

template<typename T>
struct to_ratio
    : detail::to_ratio_impl<
          T,
          decltype(detail::use_base_type(::std::declval<T>()))> {
};

template<typename T>
using to_ratio_t = typename to_ratio<T>::type;

}  // namespace coinz
