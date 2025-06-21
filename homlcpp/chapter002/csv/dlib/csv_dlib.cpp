#include <dlib/dnn.h>
#include <dlib/matrix.h>

#include <filesystem>
#include <iostream>
#include <random>
#include <regex>
#include <sstream>

int main(int argc, char **argv)
{
    if (argc > 1)
    {
        if (std::filesystem::exists(argv[1]))
        {
            std::stringstream str_stream;
            {
                std::ifstream data_stream(argv[1]);
                std::string data_string(
                    (std::istreambuf_iterator<char>(data_stream)),
                    std::istreambuf_iterator<char>()
                );

                data_string = std::regex_replace(data_string, std::regex("Iris-setosa"), "1");
                data_string = std::regex_replace(data_string, std::regex("Iris-versicolor"), "2");
                data_string = std::regex_replace(data_string, std::regex("Iris-virginica"), "3");

                str_stream << data_string;
            }

            dlib::matrix<double> data;
            str_stream >> data;

            std::cout << data << "\n";

            dlib::matrix<double> x_data = subm(data, 0, 0, data.nr(), data.nc() - 1);
        }
        else
        {
            std::cerr << "invalid file path " << argv[1] << "\n";
        }
    }
    else
    {
        std::cerr << "please provide a path to a dataset\n";
    }

    return 0;
}
