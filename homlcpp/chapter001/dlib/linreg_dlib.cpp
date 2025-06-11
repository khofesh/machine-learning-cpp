#include <dlib/matrix.h>
#include <dlib/svm.h>

#include <iostream>
#include <random>

float func(float x)
{
    // line coefficients
    return 4.f + 0.3f * x;
}

using SampleType = dlib::matrix<double, 1, 1>;
using KernelType = dlib::linear_kernel<SampleType>;

int main()
{
    size_t n = 1000;
    std::vector<dlib::matrix<double>> x(n);
    std::vector<float> y(n);

    std::random_device rd;
    std::mt19937 re(rd());
    std::uniform_real_distribution<float> dist(-1.5, 1.5);

    // generate data
    for (size_t i = 0; i < n; i++)
    {
        x[i].set_size(1, 1);
        x[i](0, 0) = i;

        y[i] = func(i) + dist(re);
    }

    // normalize data
    dlib::vector_normalizer<dlib::matrix<double>> normalizer_x;
    // let the normalizer learn the mean and standard deviation of the samples
    normalizer_x.train(x);

    // normalize each sample
    for (size_t i = 0; i < x.size(); i++)
    {
        x[i] = normalizer_x(x[i]);
    }

    dlib::krr_trainer<KernelType> trainer;
    trainer.set_kernel(KernelType());
    dlib::decision_function<KernelType> df = trainer.train(x, y);

    // gen new data
    std::cout << "original data \n";
    std::vector<dlib::matrix<double>> new_x(5);
    for (size_t i = 0; i < 5; i++)
    {
        new_x[i].set_size(1, 1);
        new_x[i](0, 0) = i;
        new_x[i] = normalizer_x(new_x[i]);
        std::cout << func(i) << "\n";
    }
    
    std::cout << "predictions \n";
    for (auto &v : new_x)
    {
        auto prediction = df(v);
        std::cout << prediction << "\n";
    }

    return 0;
}
