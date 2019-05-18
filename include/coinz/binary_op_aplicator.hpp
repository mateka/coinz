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
#pragma once

namespace coinz {

template<typename BinaryOperator, typename Init>
class binary_op_applicator {
public:
    binary_op_applicator(BinaryOperator op, Init init = {})
        : op_{::std::move(op)}, init_{::std::move(init)}
    {
    }

    template<typename Arg, typename... Args>
    auto operator()(Arg arg, Args... args) const
    {
        if constexpr (sizeof...(Args) > 0) {
            return op_(this->operator()(::std::move(args)...), arg);
        }
        else
            return op_(arg, init_);
    }

private:
    BinaryOperator op_;
    Init           init_;
};

}  // namespace coinz
