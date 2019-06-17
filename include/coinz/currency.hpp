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

#include <coinz/binary_to_nary.hpp>
#include <coinz/get_n.hpp>
#include <coinz/i_tail.hpp>
#include <coinz/to_ratio.hpp>


// #include <coinz/make_tail_index_sequence.hpp>
// #include <coinz/tuple/find_type.hpp>
// #include <coinz/tuple/partial_sum.hpp>
// #include <tuple>
#include <cstdint>
#include <type_traits>

namespace coinz {

// namespace details {
//     template<typename T, bool IsNumeric>
//     struct value_type {
//         using type = decltype(::std::declval<T>().value());
//     };

//     template<typename T>
//     struct value_type<T, true> {
//         using type = T;
//     };

//     template<typename T, bool IsNumeric>
//     struct value_getter {
//         constexpr auto operator()(T const &v) const { return v.value(); }
//     };

//     template<typename T>
//     struct value_getter<T, true> {
//         constexpr auto operator()(T const &v) const { return v; }
//     };

//     template<typename T>
//     using bare_cv_type =
//     ::std::remove_pointer_t<::std::remove_reference_t<T>>;
// }  // namespace details

// template<typename T>
// struct value_type
//     : public details::
//           value_type<T, ::std::is_arithmetic_v<details::bare_cv_type<T>>> {
// };

// template<typename T>
// using value_t = typename value_type<T>::type;

// template<typename T>
// struct value_getter
//     : public details::
//           value_getter<T, ::std::is_arithmetic_v<details::bare_cv_type<T>>> {
// };

// template<typename T, typename... Ts>
// struct amount_type : public amount_type<Ts...> {
// };

// template<typename T>
// struct amount_type<T> {
//     using type                  = T;
//     static constexpr auto value = type{1};
// };

// template<typename... Ts>
// using amount_type_t = typename amount_type<Ts...>::type;

// template<typename... Ts>
// constexpr amount_type_t<Ts...> amount_type_v = amount_type<Ts...>::value;

///////////////////////////////////////////////////////////////////////////////

template<typename A, typename B>
struct multiply : multiply<to_ratio_t<A>, to_ratio_t<B>> {
};

template<
    ::std::intmax_t Anum,
    ::std::intmax_t Bnum,
    ::std::intmax_t Adenom,
    ::std::intmax_t Bdenom>
struct multiply<::std::ratio<Anum, Adenom>, std::ratio<Bnum, Bdenom>> {
    using type = ::std::
        ratio_multiply<::std::ratio<Anum, Adenom>, std::ratio<Bnum, Bdenom>>;
};

template<typename A, typename B>
using multiply_t = typename multiply<A, B>::type;

template<typename... Parts>
class currency {
public:
    template<::std::size_t I>
    using type_n = get_n_t<I, Parts...>;

    template<::std::size_t I>
    using amount_n = get_n_t<I, Parts...>;

    // template<std::size_t I>
    // constexpr auto amount_n() const noexcept
    // {
    //     return tuple::partial_sum_by_index(
    //         m_parts,
    //         make_tail_index_sequence<I, sizeof...(Parts)>{},
    //         [](auto const a, auto const b) {
    //             return
    //             amount_type_t<Parts...>{value_getter<decltype(a)>{}(
    //                 a) *value_getter<decltype(b)>{}(b)};
    //         },
    //         amount_type_v<Parts...>);
    // }

    // template<typename T>
    // constexpr auto amount_n() const noexcept
    // {
    //     return amount_n<tuple::find_type_v<T, decltype(m_parts)>>();
    // }

    // template<typename T>
    // constexpr auto sibling_amount() const noexcept
    // {
    //     return sibling_amount<tuple::find_type_v<T,
    //     decltype(m_parts)>>();
    // }
};

}  // namespace coinz
