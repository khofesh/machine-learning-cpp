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

        a = MyMatrix33f::Identity();
        std::cout << "identity matrix:\n" << a << "\n";

        v = MyVector3f::Random();
        std::cout << "random vector:\n" << v << "\n";

        a << 1, 2, 3, 4, 5, 6, 7, 8, 9;
        std::cout << "comma initialized matrix:\n" << a << "\n";
    }
}
