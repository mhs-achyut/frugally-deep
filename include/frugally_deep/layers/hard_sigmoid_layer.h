// Copyright 2016, Tobias Hermann.
// https://github.com/Dobiasd/frugally-deep
// Distributed under the MIT License.
// (See accompanying LICENSE file or at
//  https://opensource.org/licenses/MIT)

#pragma once

#include "frugally_deep/layers/activation_layer.h"

namespace fd
{

class hard_sigmoid_layer : public activation_layer
{
public:
    explicit hard_sigmoid_layer(const size3d& size_in)
        : activation_layer(size_in)
    {
    }
protected:
    static float_t activation_function(float_t x)
    {
        return std::min(1.0, std::max(0.0, (0.2 * x) + 0.5));
    };
    matrix3d transform_input(const matrix3d& in_vol) const override
    {
        return transform_matrix3d(activation_function, in_vol);
    }
    matrix3d transform_error_backward_pass(const matrix3d& e) const override
    {
        auto activation_function_deriv = [](float_t x) -> float_t
        {
            if (x < -2.5 || x > 2.5)
                return 0;
            else
                return 0.2;
        };
        const auto last_input_derivs =
            transform_matrix3d(activation_function_deriv, last_input_);
        return multiply_matrix3ds_elementwise(last_input_derivs, e);
    }
};

} // namespace fd