#include <dlib/global_optimization.h>
#include <dlib/matrix.h>
#include <dlib/svm.h>

#include <plot.h>

#include <iostream>
#include <random>
#include <vector>

using SampleType = dlib::matrix<double, 1, 1>;
using Samples = std::vector<SampleType>;
using Labels = std::vector<SampleType>;

Samples LinSpace(double s, double e, size_t n) {
  Samples x_values(n);
  double step = (e - s) / n;
  double v = s;
  for (size_t i = 0; i < n; ++i) {
    x_values[i](0, 0) = v;
    v += step;
  }
  x_values[n - 1] = e;

  return x_values;
}

std::pair<Samples, Labels> GenerateData(size_t num_samples, size_t seed) {
  Samples x_values(num_samples);
  Labels y_values(num_samples);

  std::mt19937 re(seed);
  std::normal_distribution<double> dist;

  for (size_t i = 0; i < num_samples; ++i) {
    auto x_val = dist(re);
    x_values[i](0, 0) = x_val;

    auto y_val = std::cos(M_PI * x_val) + (dist(re) * 0.3);
    y_values[i](0, 0) = y_val;
  }
  return {x_values, y_values};
}

struct FoldStats {
  double n = 0.0;
  double sum_sq_err = 0.0;
  double sum_abs_err = 0.0;
  double sum_abs_err_sq = 0.0;
  double sum_xy = 0.0;
  double sum_x = 0.0;
  double sum_y = 0.0;
  double sum_xx = 0.0;
  double sum_yy = 0.0;
};

// Same k-fold split as dlib::cross_validate_regression_trainer(), but the
// independent folds run in parallel.
template <typename Trainer>
dlib::matrix<double, 1, 4> ParallelCrossValidate(const Trainer& trainer,
                                                 const Samples& samples,
                                                 const std::vector<double>& labels,
                                                 long folds) {
  const long n = static_cast<long>(samples.size());
  const long num_in_test = n / folds;
  const long num_in_train = n - num_in_test;

  std::vector<FoldStats> partial(folds);

#pragma omp parallel for schedule(dynamic)
  for (long i = 0; i < folds; ++i) {
    long idx = (i * num_in_test) % n;

    Samples x_test, x_train;
    std::vector<double> y_test, y_train;
    x_test.reserve(num_in_test);
    y_test.reserve(num_in_test);
    x_train.reserve(num_in_train);
    y_train.reserve(num_in_train);

    for (long cnt = 0; cnt < num_in_test; ++cnt) {
      x_test.push_back(samples[idx]);
      y_test.push_back(labels[idx]);
      idx = (idx + 1) % n;
    }
    for (long cnt = 0; cnt < num_in_train; ++cnt) {
      x_train.push_back(samples[idx]);
      y_train.push_back(labels[idx]);
      idx = (idx + 1) % n;
    }

    FoldStats& stats = partial[i];
    try {
      const auto df = trainer.train(x_train, y_train);
      for (size_t j = 0; j < x_test.size(); ++j) {
        const double out = df(x_test[j]);
        const double err = out - y_test[j];
        const double abs_err = std::abs(err);
        stats.sum_sq_err += err * err;
        stats.sum_abs_err += abs_err;
        stats.sum_abs_err_sq += abs_err * abs_err;
        stats.sum_xy += out * y_test[j];
        stats.sum_x += out;
        stats.sum_y += y_test[j];
        stats.sum_xx += out * out;
        stats.sum_yy += y_test[j] * y_test[j];
        stats.n += 1.0;
      }
    } catch (const dlib::invalid_nu_error&) {
      stats = FoldStats{};
    }
  }

  FoldStats total;
  for (const auto& s : partial) {
    total.n += s.n;
    total.sum_sq_err += s.sum_sq_err;
    total.sum_abs_err += s.sum_abs_err;
    total.sum_abs_err_sq += s.sum_abs_err_sq;
    total.sum_xy += s.sum_xy;
    total.sum_x += s.sum_x;
    total.sum_y += s.sum_y;
    total.sum_xx += s.sum_xx;
    total.sum_yy += s.sum_yy;
  }

  const double mse = total.n > 0 ? total.sum_sq_err / total.n : 0.0;
  const double mae = total.n > 0 ? total.sum_abs_err / total.n : 0.0;
  double corr = 0.0;
  double mae_stddev = 0.0;
  if (total.n > 1.0) {
    const double mae_var =
        (total.sum_abs_err_sq - total.sum_abs_err * total.sum_abs_err / total.n) /
        (total.n - 1.0);
    mae_stddev = mae_var > 0.0 ? std::sqrt(mae_var) : 0.0;

    const double cov =
        (total.sum_xy - total.sum_y * total.sum_x / total.n) / (total.n - 1.0);
    double var_x =
        (total.sum_xx - total.sum_x * total.sum_x / total.n) / (total.n - 1.0);
    double var_y =
        (total.sum_yy - total.sum_y * total.sum_y / total.n) / (total.n - 1.0);
    if (var_x < 0.0) var_x = 0.0;
    if (var_y < 0.0) var_y = 0.0;
    const double denom = std::sqrt(var_x * var_y);
    corr = denom > 0.0 ? cov / denom : 0.0;
  }

  dlib::matrix<double, 1, 4> result;
  result = mse, corr, mae, mae_stddev;
  return result;
}

int main(int /*argc*/, char** /*argv*/) {
  using namespace dlib;

  // Generate data
  auto [samples, labels] = GenerateData(1000, 435635);

  auto mm = std::minmax_element(
      samples.begin(), samples.end(),
      [](const auto& a, const auto& b) { return a(0, 0) < b(0, 0); });
  std::pair<double, double> x_minmax{*mm.first, *mm.second};

  // Normalize data
  vector_normalizer<SampleType> x_normalizer;
  x_normalizer.train(samples);
  std::for_each(samples.begin(), samples.end(), x_normalizer);

  vector_normalizer<SampleType> y_normalizer;
  y_normalizer.train(labels);
  std::for_each(labels.begin(), labels.end(), y_normalizer);

  std::vector<double> raw_labels(labels.size());
  for (size_t i = 0; i < labels.size(); ++i) {
    raw_labels[i] = labels[i](0, 0);
  }

  // Randomize data
  randomize_samples(samples, raw_labels);

  // Define cross validation function
  auto CrossValidationScore = [&](const double gamma, const double c,
                                  const double degree_in) {
    auto degree = std::floor(degree_in);
    using KernelType = dlib::polynomial_kernel<SampleType>;
    dlib::svr_trainer<KernelType> trainer;
    trainer.set_kernel(KernelType(gamma, c, degree));

    std::cout << "gamma: " << std::setw(11) << gamma << "  c: " << std::setw(11)
              << c << "  degree: " << std::setw(11) << degree;
    std::cout.flush();

    dlib::matrix<double> result =
        ParallelCrossValidate(trainer, samples, raw_labels, 10);
    std::cout << std::setw(11) << "  MSE: " << result(0, 0) << std::setw(11)
              << "  MAE: " << result(0, 2) << std::endl;

    return result(0, 0);
  };

  // Search for the best parameters
  auto result = find_min_global(
      CrossValidationScore,
      {0.01, 1e-8, 5},  // minimum values for gamma, c, and degree
      {0.1, 1, 15},     // maximum values for gamma, c, and degree
      max_function_calls(50));

  double gamma = result.x(0);
  double c = result.x(1);
  double degree = result.x(2);

  std::cout << " best cross validation score: " << result.y << std::endl;
  std::cout << " best gamma: " << gamma << "   best c: " << c
            << "    best degree: " << degree << std::endl;

  // Train model
  using KernelType = dlib::polynomial_kernel<SampleType>;
  dlib::svr_trainer<KernelType> trainer;
  trainer.set_kernel(KernelType(gamma, c, degree));
  auto descision_func = trainer.train(samples, raw_labels);

  // Plot perdictions
  auto new_samples = LinSpace(x_minmax.first, x_minmax.second, 50);
  std::for_each(new_samples.begin(), new_samples.end(), x_normalizer);

  std::vector<double> predictions(new_samples.size());
  std::transform(new_samples.begin(), new_samples.end(), predictions.begin(),
                 descision_func);

  plotcpp::Plot plt;
  plt.SetTerminal("png");
  plt.SetOutput("plot.png");
  plt.SetTitle("SVM Polynomial kernel regression");
  plt.SetXLabel("x");
  plt.SetYLabel("y");
  plt.SetAutoscale();
  plt.GnuplotCommand("set grid");

  std::vector<double> x_coords(samples.size());
  std::transform(samples.begin(), samples.end(), x_coords.begin(),
                 [](auto& m) { return m(0, 0); });

  std::vector<double> x_pred_coords(new_samples.size());
  std::transform(new_samples.begin(), new_samples.end(), x_pred_coords.begin(),
                 [](auto& m) { return m(0, 0); });

  plt.Draw2D(plotcpp::Points(x_coords.begin(), x_coords.end(),
                             raw_labels.begin(), "orig", "lc rgb 'black' pt 7"),
             plotcpp::Lines(x_pred_coords.begin(), x_pred_coords.end(),
                            predictions.begin(), "pred", "lc rgb 'red' lw 2"));
  plt.Flush();

  return 0;
}
