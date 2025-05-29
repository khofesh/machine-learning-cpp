#include <af/array.h>
#include <af/blas.h>
#include <af/data.h>
#include <af/defines.h>
#include <af/util.h>
#include <arrayfire.h>
#include <af/dim4.hpp>
#include <iostream>

int main()
{
    {
        af::array a(3, 3, af::dtype::f32);
        af::array v(3, af::dtype::f64);

        // init
        a = af::constant(0, 3, 3);
        std::cout << "zero matrix:\n";
        af_print(a);

        a = af::identity(3, 3);
        std::cout << "identity matrix:\n";
        af_print(a);

        v = af::randu(3);
        std::cout << "random vector:\n";
        af_print(v);

        // arrayfire uses the column major format
        a = af::array(af::dim4(3, 3), {1.f, 2.f, 3.f, 4.f, 5.f, 6.f, 7.f, 8.f, 9.f});
        std::cout << "initializer list matrix:\n";
        af_print(a);

        a = af::constant(3, 3, 3);
        std::cout << "uniformly initialized matrix:\n";
        af_print(a);

        a(0, 0) = 7;
        std::cout << "matrix with changed element[0][0]:\n";
        af_print(a);

        std::vector<float> mdata = {1, 2, 3, 4, 5, 6, 7, 8, 9};
        a = af::array(3, 3, mdata.data());
        std::cout << "matrix from array:\n";
        af_print(a);
    }

    // arithmetic
    {
        auto a = af::array(af::dim4(2, 2), {1, 2, 3, 4});
        a = a.as(af::dtype::f32);
        auto b = a.copy();

        // element wise
        auto result = a * b;
        std::cout << "element wise a * b:\n";
        af_print(result);

        a = b * 4;
        std::cout << "element wise a = b * 4:\n";
        af_print(a);

        // matrix
        result = a + b;
        std::cout << "matrices a + b:\n";
        af_print(result);

        a += b;
        std::cout << "matrices a += b: \n";
        af_print(a);

        result = af::matmul(a, b);
        std::cout << "matrices a * b: \n";
        af_print(result);
    }

    // partial access
    {
        auto m = af::iota(af::dim4(4, 4));
        std::cout << "4x4 matrix:\n";
        af_print(m);

        auto b = m(af::seq(1, 2), af::seq(1, 2));
        std::cout << "middle of 4x4 matrix:\n";
        af_print(b);

        b *= 0;
        std::cout << "modified middle of 4x4 matrix:\n";
        af_print(m);

        m.row(1) += 3;
        std::cout << "modified row of 4x4 matrix:\n";
        af_print(m);

        
    }
    
    return 0;
}
