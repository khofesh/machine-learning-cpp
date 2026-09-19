#include <dlib/cuda/cuda_dlib.h>
#include <dlib/dnn.h>

#include <iostream>
#include <vector>

using namespace dlib;

template <typename SUBNET>
using stem = max_pool<3, 3, 2, 2, relu<con<6, 5, 5, 1, 1, SUBNET>>>;

using net_type = loss_multiclass_log<
    fc<10,
    relu<fc<16,
    relu<fc<32,
    stem<input<matrix<unsigned char>>>>>>>>>;

int main()
{
#ifdef DLIB_USE_CUDA
    std::cout << "dlib built with CUDA support\n";
#else
    std::cout << "dlib built WITHOUT CUDA support\n";
    return 1;
#endif

    const int num_devices = dlib::cuda::get_num_devices();
    std::cout << "CUDA devices: " << num_devices << "\n";
    for (int i = 0; i < num_devices; ++i)
        std::cout << "  [" << i << "] " << dlib::cuda::get_device_name(i) << "\n";
    if (num_devices == 0)
    {
        std::cerr << "no CUDA device available\n";
        return 1;
    }

    net_type net;

    std::vector<matrix<unsigned char>> samples(4);
    for (auto &img : samples)
    {
        img.set_size(16, 16);
        for (long r = 0; r < img.nr(); ++r)
            for (long c = 0; c < img.nc(); ++c)
                img(r, c) = static_cast<unsigned char>((r * 7 + c * 3) % 256);
    }

    const std::vector<unsigned long> predictions = net(samples);
    std::cout << "forward pass through CUDA/cuDNN on " << predictions.size()
              << " samples; predictions:";
    for (const auto p : predictions)
        std::cout << ' ' << p;
    std::cout << "\n";
}
