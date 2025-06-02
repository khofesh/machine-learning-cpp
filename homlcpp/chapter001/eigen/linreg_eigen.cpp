#include <Eigen/Dense>
#include <Eigen/IterativeLinearSolvers>

#include <algorithm>
#include <iostream>
#include <random>
#include <vector>

std::pair<Eigen::MatrixXf, Eigen::MatrixXf> GenerateData(size_t n)
{
    std::vector<float> x_data(n);
    std::iota(x_data.begin(), x_data.end(), 0);
    std::vector<float> y_data(n);
    std::iota(y_data.begin(), y_data.end(), 0);

    // mutate data
    std::random_device rd;
    std::mt19937 re(rd());
    std::uniform_real_distribution<float> dist(-1.5f, 1.5f);

    for (auto &x : x_data)
    {
        // add noise
        x += dist(re);
    }

    for (auto &y : y_data)
    {
        // noise
        y += dist(re);
    }

    Eigen::Map<Eigen::MatrixXf> x(x_data.data(), static_cast<Eigen::Index>(n), 1);
    Eigen::Map<Eigen::MatrixXf> y(y_data.data(), static_cast<Eigen::Index>(n), 1);

    return {x, y};
}

int main()
{
    size_t n = 1000;

    // gen training data
    Eigen::MatrixXf x1, y;
    std::tie(x1, y) = GenerateData(n);
    Eigen::MatrixXf x0 = Eigen::MatrixXf::Ones(n, 1);

    // setup line coefficients y = b(4) + k(0.3)*x
    y.array() *= 0.3f;
    y.array() += 4.f;
    Eigen::MatrixXf x(n, 2);
    x << x0, x1;

    // train estimation
    Eigen::LeastSquaresConjugateGradient<Eigen::MatrixXf> gd;
    gd.setMaxIterations(100);
    gd.setTolerance(0.001f);
    gd.compute(x);
    Eigen::VectorXf b = gd.solve(y);
    std::cout << "estimated parameters vector: \n" << b << "\n";

    // normal equations
    Eigen::VectorXf b_norm = (x.transpose() * x).ldlt().solve(x.transpose() * y);
    std::cout << "estimated with normal equation parameters vector: " << b_norm << "\n";

    // predict
    Eigen::MatrixXf new_x(5, 2);
    new_x << 1, 1, 1, 2, 1, 3, 1, 4, 1, 5;
    auto new_y = new_x.array().rowwise() * b.transpose().array();
    std::cout << "predicted values: \n" << new_y << "\n";

    auto new_y_norm = new_x.array().rowwise() * b_norm.transpose().array();
    std::cout << "predicted(norm) values:\n" << new_y_norm << "\n";

    return 0;
}
