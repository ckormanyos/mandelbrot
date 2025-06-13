///////////////////////////////////////////////////////////////////////////////
// Copyright Christopher Kormanyos 2015 - 2025.
// Distributed under the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt
// or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#if (defined(__GNUC__) && defined(__clang__))
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-parameter"
#endif

#include <concurrency/stopwatch.h>

#include <mandelbrot/mandelbrot.h>

#include <iomanip>
#include <iostream>
#include <sstream>

// Provide instructions for simple build on WSL.
// cd /mnt/c/Users/ckorm/Documents/Ks/PC_Software/NumericalPrograms/mandelbrot

// Compile with cpp_dec_float
// ./build_all.sh --boost=/mnt/c/boost/boost_1_88_0 --ixtra=/mnt/c/ChrisGitRepos/modular_boost/multiprecision/include --my_cc=g++ --stdcc=c++20

// Compile with gmp_float
// ./build_all_gmp.sh --boost=/mnt/c/boost/boost_1_88_0 --ixtra=/mnt/c/ChrisGitRepos/modular_boost/multiprecision/include --my_cc=g++ --stdcc=c++20

auto main() -> int // NOLINT(bugprone-exception-escape)
{
  using namespace ::ckormanyos::mandelbrot; // NOLINT(google-build-using-namespace)

  const config::mandelbrot_config_type
    mandelbrot_config_object
    (
      config::center_x() - config::dx_half(),
      config::center_x() + config::dx_half(),
      config::center_y() - config::dy_half(),
      config::center_y() + config::dy_half(),
      config::max_iter()
    );

  using mandelbrot_generator_type =
    config::my_mandelbrot_generator_type<config::coord_pnt_numeric_type, config::iteration_numeric_type>;

        color::color_stretch_histogram_method local_color_stretches;
  const color::color_functions_bw             local_color_functions;

  mandelbrot_generator_type mandelbrot_generator(mandelbrot_config_object);

  using stopwatch_type = concurrency::stopwatch;

  stopwatch_type my_stopwatch { };

  mandelbrot_generator.generate_mandelbrot_image(config::filename(),
                                                 local_color_functions,
                                                 local_color_stretches);

  const auto execution_time = stopwatch_type::elapsed_time<float>(my_stopwatch);

  {
    std::stringstream strm;

    strm << "Time for calculation: "
         << std::fixed
         << std::setprecision(std::streamsize { INT8_C(1) })
         << "execution_time: "
         << execution_time
         << "s";

    std::cout << strm.str() << std::endl;
  }
}

#if (defined(__GNUC__) && defined(__clang__))
#pragma GCC diagnostic pop
#endif
