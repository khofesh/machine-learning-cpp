#include <xtensor-blas/xlinalg.hpp>
#include <xtensor/xadapt.hpp>
#include <xtensor/xarray.hpp>
#include <xtensor/xbuilder.hpp>
#include <xtensor/xeval.hpp>
#include <xtensor/xio.hpp>
#include <xtensor/xrandom.hpp>

#include <iostream>
#include <vector>

int main()
{
    {
        std::vector<uint64_t> shape = {3, 2, 4};
        xt::xarray<double, xt::layout_type::row_major> a(shape);

        std::cout << "a: \n" << a << "\n";
    }

    return 0;
}
