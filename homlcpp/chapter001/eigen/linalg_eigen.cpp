#include <Eigen/Dense>
#include <iostream>

// matrix with known 3x3 dimensions
typedef Eigen::Matrix<float, 3, 3> MyMatrix33f;
typedef Eigen::Matrix<float, 3, 1> MyVector3f;
// matrix of doubles with dynamic dimensions
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

        a << 1, 2, 3, 
            4, 5, 6, 
            7, 8, 9;
        std::cout << "comma initialized matrix:\n" << a << "\n";

        a(0, 0) = 3;
        std::cout << "matrix with changed alament[0][0]:\n" << a << "\n";

        int data[] = {1, 2, 3, 4};
        Eigen::Map<Eigen::RowVectorXi> v_map(data, 4);
        std::cout << "row vector mapped to array:\n" << v_map << "\n";

        std::vector<float> vdata = {1, 2, 3, 4, 5, 6, 7, 8, 9};
        Eigen::Map<MyMatrix33f> a_map(vdata.data());
        std::cout << "matrix mapped to array:\n" << a_map << "\n";
    }

    // generate math operations
    {
        Eigen::Matrix2d a;
        a << 1, 2, 3, 4;
        Eigen::Matrix2d b;
        b << 1, 2, 3, 4;

        // element wise operations
        Eigen::Matrix2d result = a.array() * b.array();
        std::cout << "element wise a * b: \n" << result << "\n";

        result = a.array() / b.array();
        std::cout << "element wise a / b :\n" << result << "\n";

        a = b.array() * 4;
        std::cout << "element wise a = b * 4: \n" << a << "\n";

        // matrix operations
        result = a + b;
        std::cout << "matrices a + b:\n" << result << "\n";

        a += b;
        std::cout << "matrices a += b:\n" << result << "\n";

        std::cout << "matrix a: \n" << a << "\n";
        std::cout << "matrix b: \n" << b << "\n";

        result = a * b;
        std::cout << "matrices a * b:\n" << result << "\n";
    }

    // partial access
    {
        Eigen::MatrixXf m = Eigen::MatrixXf::Random(4, 4);
        std::cout << "random 4x4 matrix :\n" << m << "\n";

        Eigen::Matrix2f b = m.block(1, 1, 2, 2);
        std::cout << "middle of 4x4 matrix: \n" << b << "\n";

        m.block(1, 1, 2, 2) *= 0; // change values in original matrix
        std::cout << "modified middle of 4x4 matrix: \n" << m << "\n";

        std::cout << "matrix: \n" << m << "\n";

        // There are two more methods to access rows and columns by index
        m.row(1).array() += 3;
        std::cout << "modified row of 4x4 matrix: \n" << m << "\n";

        m.col(2).array() /= 4;
        std::cout << "modified col of 4x4 matrix: \n" << m << "\n";
    }

    // broadcasting
    {
        Eigen::MatrixXf mat = Eigen::MatrixXf::Random(2, 4);
        std::cout << "random 2x4 matrix: \n" << mat << "\n";

        // column vector
        Eigen::VectorXf v(2);
        v << 100, 100;
        mat.colwise() += v;
        std::cout << "sum broadcasted over columns: \n" << mat << "\n";
    }

    return 0;
}
