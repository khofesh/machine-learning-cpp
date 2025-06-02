#include <dlib/matrix.h>
#include <iostream>

int main()
{
  // definitions
  {
    dlib::matrix<double, 3, 1> y;
    dlib::matrix<double> m(3, 3);
    m.set_size(6, 6);
  }

  // initializations
  {
    // comma operator
    dlib::matrix<double> m(3, 3);
    m = 1., 2., 3., 4., 5., 6., 7., 8., 9.;
    std::cout << "Matix from comma operator\n"
              << m << "\n";

    // wrap array
    double data[] = {1, 2, 3, 4, 5, 6};
    // 2x3 matrix
    auto m2 = dlib::mat(data, 2, 3);
    std::cout << "Matix from array\n"
              << m2 << "\n";

    m(1, 2) = 300;
    std::cout << "Matix element updated\n"
              << m << "\n";

    auto a = dlib::identity_matrix<double>(3);
    std::cout << "Identity matix \n"
              << a << "\n";

    auto b = dlib::ones_matrix<double>(3, 4);
    std::cout << "Ones matix \n"
              << b << "\n";

    auto c = dlib::randm(3, 4);
    std::cout << "Random matix \n"
              << c << "\n";
  }

  // arithmetic operations
  {
    dlib::matrix<double> a(2, 2);
    a = 1, 1, 1, 1;
    dlib::matrix<double> b(2, 2);
    b = 2, 2, 2, 2;

    auto c = a + b;
    std::cout << "c = a + b \n"
              << c << "\n";

    auto e = a * b;
    std::cout << "e = a dot b \n"
              << e << "\n";

    a += 5;
    std::cout << "a += 5 \n"
              << a << "\n";

    auto d = dlib::pointwise_multiply(a, b);
    std::cout << "d = a * b \n"
              << d << "\n";

    auto t = dlib::trans(a);
    std::cout << "transposed matrix a \n"
              << t << "\n";
  }

  // partial access
  {
    dlib::matrix<float, 4, 4> m;
    m = 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16;
    auto sm =
        dlib::subm(m, dlib::range(1, 2),
                   dlib::range(1, 2));
    std::cout << "Sub matrix \n"
              << sm << "\n";

    dlib::set_subm(m, dlib::range(1, 2), dlib::range(1, 2)) = 100;
    std::cout << "Updated sub matrix \n"
              << m << "\n";
  }

  // there are no implicit broadcasting in dlib
  {
    // simulate broadcasting with partial access
    dlib::matrix<float, 2, 1> v;
    v = 10, 10;
    
    dlib::matrix<float, 2, 3> m;
    m = 1, 2, 3, 4, 5, 6;
    for (int i = 0; i < m.nc(); ++i)
    {
      dlib::set_colm(m, i) += v;
    }

    std::cout << "Matrix with updated columns \n"
              << m << "\n";
  }

  return 0;
}
