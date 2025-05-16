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
    // dynamically sized array
    {
        std::vector<uint64_t> shape = {3, 2, 4};
        xt::xarray<double, xt::layout_type::row_major> a(shape);

        std::cout << "a: \n"
                  << a << "\n";
    }
    // declaration of dynamically sized tensor with fixed dimmentions number
    {
        std::array<size_t, 3> shape = {3, 2, 4};
        xt::xtensor<double, 3> a(shape);

        std::cout << "a: \n"
                  << a << "\n";
    }
    // declaration of tensor with shape fixed at compile time.
    {
        xt::xtensor_fixed<double, xt::xshape<3, 2, 4>> a;
        std::cout << "a: \n"
                  << a << "\n";
    }
    // Initialization of xtensor arrays can be done with C++ initializer lists:
    {
        xt::xarray<double> arr1{{1.0, 2.0, 3.0},
                                {2.0, 5.0, 7.0},
                                {2.0, 5.0, 7.0}};
        std::cout << "tensor from initializer list :\n"
                  << arr1 << "\n";
    }
    // special types of initializers
    {
        std::vector<uint64_t> shape = {2, 2};
        std::cout << "ones matrix: \n"
                  << xt::ones<float>(shape) << "\n";
        std::cout << "zero matrix: \n"
                  << xt::zeros<float>(shape) << "\n";
        std::cout << "matrix with ones on the diagonal: \n"
                  << xt::eye<float>(shape) << "\n";
    }
    // mapping c++ array to tensors
    {
        std::vector<float> data{1, 2, 3, 4};
        std::vector<size_t> shape{2, 2};
        auto data_x = xt::adapt(data, shape);
        std::cout << "matrix from vector: \n"
                  << data_x << "\n";
    }
    // element access
    {
        std::vector<size_t> shape = {3, 2, 4};
        xt::xarray<float> a = xt::ones<float>(shape);
        a(2, 1, 3) = 3.14f;
        std::cout << "updated elemtn: \n"
                  << a << "\n";
    }
    // arithmetic operations examples
    {
        xt::xarray<double> a = xt::random::rand<double>({2, 2});
        xt::xarray<double> b = xt::random::rand<double>({2, 2});

        std::cout << "a: \n"
                  << a << "\n";
        std::cout << "b: \n"
                  << b << "\n";

        xt::xarray<double> c = a + b;
        std::cout << "c = a + b \n"
                  << c << "\n";
        a -= b;
        std::cout << "a -= b \n"
                  << a << "\n";
        c = xt::linalg::dot(a, b);
        std::cout << "a dot b \n"
                  << c << "\n";
        c = a + 5;
        std::cout << "c = a + 5 \n"
                  << c << "\n";
        c = a * b;
        std::cout << "c = a * b \n"
                  << c << "\n";
    }
    // partial access to xtensor containers
    {
        xt::xarray<int> a{
            {1, 2, 3, 4}, {5, 6, 7, 8}, {9, 10, 11, 12}, {13, 14, 15, 16}};
        std::cout << "a: \n"
                  << a << "\n";
        auto b = xt::view(a, xt::range(1, 3), xt::range(1, 3));
        std::cout << "partial view on a \n"
                  << b << "\n";
    }
    // broadcasting
    {
        auto a = xt::xarray<double>({{1, 2}, {3, 4}});
        auto b = xt::xarray<double>({10, 20});
        b.reshape({2, 1});
        std::cout << "a: \n"
                  << a << "\n";
        std::cout << "b: \n"
                  << b << "\n";

        auto c = a + b;
        std::cout << "columns broadcasting: \n"
                  << c << "\n";
    }
    {
        auto m = xt::random::rand<double>({2, 2});
        auto v = xt::random::rand<double>({2, 1});
        std::cout << "m: \n"
                  << m << "\n";
        std::cout << "v: \n"
                  << v << "\n";
        auto c = m + v;
        std::cout << "m + v: \n"
                  << c << "\n";
    }

    return 0;
}
