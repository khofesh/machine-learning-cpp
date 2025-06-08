#include <af/algorithm.h>
#include <af/blas.h>
#include <af/data.h>
#include <af/defines.h>
#include <af/gfor.h>
#include <af/random.h>
#include <af/util.h>
#include <arrayfire.h>
#include <af/dim4.hpp>
#include <iostream>

int main()
{
    size_t n = 1000;

    auto predict = [](auto &v, auto &w) {
        return af::batchFunc(v, w, [](const auto &a, const auto &b) {
            return af::sum(a * b, 1);
        });
    };

    // gen training data
    auto x = af::iota(af::dim4(n)) / n;
    x += af::randu(n);
    x = af::join(1, af::constant(1, n), x);

    af::dim4 weights_dim(1, 2);
    auto line_weights = af::array(weights_dim, {4.f, 0.3f});
    auto y = predict(x, line_weights);

    // train classifier
    auto train_weights = af::constant(0.f, weights_dim, af::dtype::f32);
    af::array j, dj;
    float lr = 0.1f;
    int n_iter = 300;
    
    for (int i = 0; i < n_iter; i++)
    {
        std::cout << "iteration " << i << ":\n";

        // cost
        auto h = predict(x, train_weights);
        auto diff = (y - h);

        auto j = af::sum(diff * diff) / n;
        af_print(j);

        // gradient of cost
        auto dm = (-2.f / n) * af::sum(x.col(1) * diff);
        auto dc = (-2.f / n) * af::sum(diff);
        auto dj = af::join(1, dc, dm);

        // update the parameters via gradient descent
        train_weights = train_weights - lr * dj;
    }

    std::cout << "learned line weights\n";
    af_print(train_weights);

    return 0;
}
