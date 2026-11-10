#include "data.h"

#include <cmath>
#include <random>

std::pair<Samples, Samples> GenerateData(double min_value,
                                         double max_value,
                                         std::size_t num_samples,
                                         std::size_t seed,
                                         bool noise) {
  std::mt19937 generator(static_cast<std::mt19937::result_type>(seed));
  std::uniform_real_distribution<double> uniform(min_value, max_value);
  std::normal_distribution<double> gaussian(0.0, 0.1);

  Samples x;
  Samples y;
  x.reserve(num_samples);
  y.reserve(num_samples);

  for (std::size_t i = 0; i < num_samples; ++i) {
    double sample = uniform(generator);
    double target = std::sin(sample);
    if (noise) {
      target += gaussian(generator);
    }
    x.push_back(sample);
    y.push_back(target);
  }

  return {std::move(x), std::move(y)};
}
