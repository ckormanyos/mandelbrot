﻿///////////////////////////////////////////////////////////////////////////////
//      Copyright Christopher Kormanyos 2015 - 2023.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)
//

#include <ctime>
#include <iostream>
#include <string>

#if (defined(__GNUC__) && defined(__clang__))
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-parameter"
#endif


//#include <mandelbrot/cfg/mandelbrot_cfg_MANDELBROT_01_FULL.h>
//#include <mandelbrot/cfg/mandelbrot_cfg_MANDELBROT_03_TOP.h>
//#include <mandelbrot/cfg/mandelbrot_cfg_MANDELBROT_04_SWIRL.h>
#include <mandelbrot/cfg/mandelbrot_cfg_MANDELBROT_05_SEAHORSES.h>
//#include <mandelbrot/cfg/mandelbrot_cfg_MANDELBROT_06_BRANCHES.h>
//#include <mandelbrot/cfg/mandelbrot_cfg_MANDELBROT_07_SEAHORSE_VALLEY.h>
//#include <mandelbrot/cfg/mandelbrot_cfg_MANDELBROT_08_DEEP_DIVE_01.h>
//#include <mandelbrot/cfg/mandelbrot_cfg_MANDELBROT_09_DEEP_DIVE_02.h>
//#include <mandelbrot/cfg/mandelbrot_cfg_MANDELBROT_10_ZOOM_WIKI_00.h>
//#include <mandelbrot/cfg/mandelbrot_cfg_MANDELBROT_11_ZOOM_WIKI_01.h>
//#include <mandelbrot/cfg/mandelbrot_cfg_MANDELBROT_12_ZOOM_WIKI_02.h>
//#include <mandelbrot/cfg/mandelbrot_cfg_MANDELBROT_13_ZOOM_WIKI_03.h>
//#include <mandelbrot/cfg/mandelbrot_cfg_MANDELBROT_14_ZOOM_WIKI_04.h>
//#include <mandelbrot/cfg/mandelbrot_cfg_MANDELBROT_20_ZOOM_VERY_DEEP_00.h>
//#include <mandelbrot/cfg/mandelbrot_cfg_MANDELBROT_30_ZOOM_ANOTHER_00.h>
//#include <mandelbrot/cfg/mandelbrot_cfg_MANDELBROT_31_ZOOM_ANOTHER_01.h>
//#include <mandelbrot/cfg/mandelbrot_cfg_MANDELBROT_32_ZOOM_ANOTHER_02.h>

// Provide instructions for simple build on WSL.
// cd /mnt/c/Users/User/Documents/Ks/PC_Software/NumericalPrograms/mandelbrot/jpeg
// make all

// cd ..

// Compile with cpp_dec_float
// g++ -c -finline-functions -march=native -mtune=native -O3 -Wall -Wextra -std=c++14 -I. -I/mnt/c/boost/boost_1_81_0 -Ijpeg/jpeg-6b-2022 -pthread test/test_mandelbrot.cpp -o test_mandelbrot.o
// g++ test_mandelbrot.o -lpthread -ljpeg-6b -Ljpeg/jpeg-6b-2022/obj -o test_mandelbrot.exe

// Compile with gmp_float
// g++ -c -finline-functions -march=native -mtune=native -O3 -Wall -Wextra -std=c++14 -DMANDELBROT_USE_GMP_FLOAT -I. -I/mnt/c/boost/boost_1_81_0 -Ijpeg/jpeg-6b-2022 -pthread test/test_mandelbrot.cpp -o test_mandelbrot.o
// g++ test_mandelbrot.o -lpthread -ljpeg-6b -Ljpeg/jpeg-6b-2022/obj -lgmp -o test_mandelbrot.exe

auto main() -> int // NOLINT(bugprone-exception-escape)
{
  using namespace ckormanyos::mandelbrot; // NOLINT(google-build-using-namespace)

  const cfg::mandelbrot_config_type
    mandelbrot_config_object
    (
      cfg::center_x() - cfg::dx_half(), // NOLINT
      cfg::center_x() + cfg::dx_half(),
      cfg::center_y() - cfg::dx_half(),
      cfg::center_y() + cfg::dx_half()
    );

  using mandelbrot_generator_type =
    mandelbrot_generator<cfg::mandelbrot_numeric_type,
                         cfg::mandelbrot_config_type::max_iterations>;

        color::color_stretch_histogram_method local_color_stretches;
  const color::color_functions_bw             local_color_functions;

  mandelbrot_generator_type mandelbrot_generator(mandelbrot_config_object);

  const auto start = std::clock();

  mandelbrot_generator.generate_mandelbrot_image(cfg::filename(),
                                                 local_color_functions,
                                                 local_color_stretches);

  const auto stop = std::clock();

  const auto elapsed = static_cast<float>(static_cast<float>(stop - start) / CLOCKS_PER_SEC);

  std::cout << "Time for calculation: "
            << std::fixed
            << std::setprecision(static_cast<std::streamsize>(INT8_C(1)))
            << elapsed
            << "s"
            << std::endl;
}

#if (defined(__GNUC__) && defined(__clang__))
#pragma GCC diagnostic pop
#endif
