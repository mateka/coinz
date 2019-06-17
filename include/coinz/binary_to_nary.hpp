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

namespace coinz {

template<
    template<typename, typename>
    class BinaryOp,
    typename Init,
    typename... Args>
struct binary_to_nary {
};

template<
    template<typename, typename>
    class BinaryOp,
    typename Init,
    typename HeadArg,
    typename... TailArgs>
struct binary_to_nary<BinaryOp, Init, HeadArg, TailArgs...> {
    using type = BinaryOp<
        typename binary_to_nary<BinaryOp, HeadArg, TailArgs...>::type,
        Init>;
};

template<
    template<typename, typename>
    class BinaryOp,
    typename Init,
    typename Arg1,
    typename Arg2>
struct binary_to_nary<BinaryOp, Init, Arg1, Arg2> {
    using type = BinaryOp<Arg2, BinaryOp<Arg1, Init>>;
};

template<
    template<typename, typename>
    class BinaryOp,
    typename Init,
    typename Arg>
struct binary_to_nary<BinaryOp, Init, Arg> {
    using type = BinaryOp<Arg, Init>;
};

template<
    template<typename, typename>
    class BinaryOp,
    typename Init,
    typename... Args>
using binary_to_nary_t = typename binary_to_nary<BinaryOp, Init, Args...>::type;

}  // namespace coinz
