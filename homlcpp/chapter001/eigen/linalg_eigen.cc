#include <Eigen/Dense>
#include <iostream>

typedef Eigen::Matrix<float, 3, 3> MyMatrix33f;
typedef Eigen::Matrix<float, 3, 1> MyVector3f;
typedef Eigen::Matrix<double, Eigen::Dynamic, Eigen::Dynamic> MyMatrix;

int main()
{
    {
        // declaration
        MyMatrix33f a;
        MyVector3f v;
        MyMatrix m(10, 15);

        // init
        a = MyMatrix33f::Zero();
        std::cout << "zero matrix:\n" << a << "\n";
    }
}
