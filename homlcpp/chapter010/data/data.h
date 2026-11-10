#pragma once

#include <cstddef>
#include <utility>
#include <vector>

using Samples = std::vector<double>;

// Toy regression dataset: y = sin(x) over [min_value, max_value],
// with optional Gaussian noise added to the target.
std::pair<Samples, Samples> GenerateData(double min_value,
                                         double max_value,
                                         std::size_t num_samples,
                                         std::size_t seed,
                                         bool noise);
