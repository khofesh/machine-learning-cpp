#include <blaze/Math.h>
#include <iostream>
#include "blaze/math/TransposeFlag.h"
#include "blaze/math/dense/UniformVector.h"
#include "blaze/math/expressions/Forward.h"
#include "blaze/math/sparse/IdentityMatrix.h"
#include "blaze/util/Random.h"

typedef blaze::StaticMatrix<float, 3UL, 3UL, blaze::columnMajor> MyMatrix33f;
typedef blaze::StaticVector<float, 3UL> MyVector3f;
typedef blaze::DynamicMatrix<double> MyMatrix;

int main()
{
    {
        MyMatrix33f a;
        MyVector3f v;
        MyMatrix m(10, 15);

        // init
        a = blaze::zero<float>(3UL, 3UL);
        std::cout << "zero matrix:\n"
                  << a << "\n";

        a = blaze::IdentityMatrix<float>(3UL);
        std::cout << "identity matrix:\n"
                  << a << "\n";

        blaze::Rand<float> rnd;
        v = blaze::generate(3UL, [&](size_t)
                            { return rnd.generate(); });
        std::cout << "random vector:\n"
                  << v << "\n";

        a = {
            {1, 2, 3},
            {4, 5, 6},
            {7, 8, 9}};
        std::cout << "initializer list matrix:\n"
                  << a << "\n";

        a = blaze::uniform(3UL, 3UL, 3.f);
        std::cout << "uniformly initiated matrix:\n"
                  << a << "\n";

        a(0, 0) = 7;
        std::cout << "matrix with changed element[0][0]:\n"
                  << a << "\n";

        std::array<int, 4> data = {1, 2, 3, 4};
        blaze::CustomVector<int, blaze::unaligned, blaze::unpadded, blaze::rowMajor> v2(data.data(), data.size());
        data[1] = 5;
        std::cout << "vector mapped to array:\n"
                  << v2 << "\n";

        std::vector<float> mdata = {1, 2, 3, 4, 5, 6, 7, 8, 9};
        blaze::CustomMatrix<float, blaze::unaligned, blaze::unpadded, blaze::rowMajor> a2(mdata.data(), 3UL, 3UL);
        std::cout << "matrix mapped to array:\n"
                  << a2 << "\n";
    }
    // arithmetic
    {
        blaze::StaticMatrix<float, 2UL, 2UL> a = {{1, 2}, {3, 4}};
        auto b = a;

        // element wise operations
        blaze::StaticMatrix<float, 2UL, 2UL> result = a % b;
        std::cout << "element wise a * b: \n"
                  << result << "\n";

        a = b * 4;
        std::cout << "element wise a = b * 4: \n"
                  << a << "\n";

        // matrix operations
        result = a + b;
        std::cout << "matrices a + b:\n"
                  << result << "\n";

        a += b;
        std::cout << "matrices a += b: \n"
                  << a << "\n";

        result = a * b;
        std::cout << "matrices a * b: \n"
                  << result << "\n";
    }
    // partial access
    {
        blaze::StaticMatrix<float, 4UL, 4UL> m = {
            {1, 2, 3, 4},
            {5, 6, 7, 8},
            {9, 10, 11, 12},
            {13, 14, 15, 16}};
        std::cout << "4x4 matrix :\n"
                  << m << "\n";

        // copying the middle part of the matrix
        blaze::StaticMatrix<float, 2UL, 2UL> b = blaze::submatrix<1UL, 1UL, 2UL, 2UL>(m);
        std::cout << "middle of 4x4 matrix: \n"
                  << b << "\n";

        // change values in original matrix
        blaze::submatrix<1UL, 1UL, 2UL, 2UL>(m) *= 0;
        std::cout << "modified middle of 4x4 matrix :\n"
                  << m << "\n";

        blaze::row<1UL>(m) += 3;
        std::cout << "modified row of 4x4 matrix: \n"
                  << m << "\n";

        blaze::column<2UL>(m) /= 4;
        std::cout << "modified col of 4x4 matrix: \n"
                  << m << "\n";
    }
    // broadcasting
    {
        blaze::DynamicMatrix<float, blaze::rowVector> mat = blaze::uniform(4UL, 4UL, 2);
        std::cout << "uniform 4x4 matrix:\n"
                  << mat << "\n";

        blaze::DynamicVector<float, blaze::rowVector> vec = {1, 2, 3, 4};
        auto ex_vec = blaze::expand(vec, 4UL);
        std::cout << "expanded vector: \n"
                  << ex_vec << "\n";

        mat += ex_vec;
        std::cout << "sum broadcasted over rows:\n"
                  << mat << "\n";
    }

    return 0;
}
