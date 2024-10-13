///////////////////////////////////////////////////////////////////////////////
// Copyright Christopher Kormanyos 2015 - 2024.
// Distributed under the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt
// or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#include <concurrency/stopwatch.h>

#include <iomanip>
#include <iostream>
#include <sstream>

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
//#include <mandelbrot/cfg/mandelbrot_cfg_MANDELBROT_08_DEEP_DIVE_01_magnify51.h>
//#include <mandelbrot/cfg/mandelbrot_cfg_MANDELBROT_09_DEEP_DIVE_02.h>
//#include <mandelbrot/cfg/mandelbrot_cfg_MANDELBROT_10_ZOOM_WIKI_00.h>
//#include <mandelbrot/cfg/mandelbrot_cfg_MANDELBROT_10_ZOOM_WIKI_00_rect.h>
//#include <mandelbrot/cfg/mandelbrot_cfg_MANDELBROT_11_ZOOM_WIKI_01.h>
//#include <mandelbrot/cfg/mandelbrot_cfg_MANDELBROT_12_ZOOM_WIKI_02.h>
//#include <mandelbrot/cfg/mandelbrot_cfg_MANDELBROT_13_ZOOM_WIKI_03.h>
//#include <mandelbrot/cfg/mandelbrot_cfg_MANDELBROT_14_ZOOM_WIKI_04.h>
//#include <mandelbrot/cfg/mandelbrot_cfg_MANDELBROT_20_ZOOM_VERY_DEEP_00.h>
//#include <mandelbrot/cfg/mandelbrot_cfg_MANDELBROT_20_ZOOM_VERY_DEEP_00_magnify51.h>
//#include <mandelbrot/cfg/mandelbrot_cfg_MANDELBROT_20_ZOOM_VERY_DEEP_612.h>
//#include <mandelbrot/cfg/mandelbrot_cfg_MANDELBROT_25_ZOOM_SEARCH_00.h>
//#include <mandelbrot/cfg/mandelbrot_cfg_MANDELBROT_25_ZOOM_SEARCH_01.h>
//#include <mandelbrot/cfg/mandelbrot_cfg_MANDELBROT_30_ZOOM_ANOTHER_00.h>
//#include <mandelbrot/cfg/mandelbrot_cfg_MANDELBROT_30_ZOOM_ANOTHER_00_magnify51.h>
//#include <mandelbrot/cfg/mandelbrot_cfg_MANDELBROT_31_ZOOM_ANOTHER_01.h>
//#include <mandelbrot/cfg/mandelbrot_cfg_MANDELBROT_32_ZOOM_ANOTHER_02.h>
//#include <mandelbrot/cfg/mandelbrot_cfg_MANDELBROT_33_ZOOM_EVEN_MORE_03.h>
//#include <mandelbrot/cfg/mandelbrot_cfg_MANDELBROT_40_SEAHORSE_DIVE_01.h>
//#include <mandelbrot/cfg/mandelbrot_cfg_MANDELBROT_45_SEAHORSE_OTHER_01_magnify51.h>
//#include <mandelbrot/cfg/mandelbrot_cfg_MANDELBROT_50_TENDRIL_AREA_01.h>
//#include <mandelbrot/cfg/mandelbrot_cfg_MANDELBROT_60_SATELITE_REGION_01.h>
//#include <mandelbrot/cfg/mandelbrot_cfg_MANDELBROT_61_SATELITE_REGION_02.h>
//#include <mandelbrot/cfg/mandelbrot_cfg_MANDELBROT_62_SATELITE_REGION_03.h>
//#include <mandelbrot/cfg/mandelbrot_cfg_MANDELBROT_63_SATELITE_REGION_04.h>
//#include <mandelbrot/cfg/mandelbrot_cfg_MANDELBROT_70_DOUADY_RABBIT_01.h>
//#include <mandelbrot/cfg/mandelbrot_cfg_MANDELBROT_72_DOUADY_RABBIT_03.h>
//#include <mandelbrot/cfg/mandelbrot_cfg_MANDELBROT_80_SEARCH_HALO_01.h>
//#include <mandelbrot/cfg/mandelbrot_cfg_MANDELBROT_99_TRY_POINTS.h>

// Provide instructions for simple build on WSL.
// cd /mnt/c/Users/ckorm/Documents/Ks/PC_Software/NumericalPrograms/mandelbrot

// Compile with cpp_dec_float
// ./build_all.sh --boost=/mnt/c/boost/boost_1_85_0 --my_cc=g++ --stdcc=c++20

// Compile with gmp_float
// ./build_all_gmp.sh --boost=/mnt/c/boost/boost_1_85_0 --my_cc=g++ --stdcc=c++20

auto main() -> int // NOLINT(bugprone-exception-escape)
{
  using namespace ckormanyos::mandelbrot; // NOLINT(google-build-using-namespace)

  const cfg::mandelbrot_config_type
    mandelbrot_config_object
    (
      cfg::center_x() - cfg::dx_half(),
      cfg::center_x() + cfg::dx_half(),
      cfg::center_y() - cfg::dy_half(),
      cfg::center_y() + cfg::dy_half(),
      cfg::max_iter()
    );

  using mandelbrot_generator_type =
    MANDELBROT_GENERATOR_TYPE<cfg::coord_pnt_numeric_type,
                              cfg::iteration_numeric_type>;

        color::color_stretch_histogram_method local_color_stretches;
  const color::color_functions_bw             local_color_functions;

  mandelbrot_generator_type mandelbrot_generator(mandelbrot_config_object);

  using stopwatch_type = concurrency::stopwatch;

  stopwatch_type my_stopwatch { };

  mandelbrot_generator.generate_mandelbrot_image(cfg::filename(),
                                                 local_color_functions,
                                                 local_color_stretches);

  const auto execution_time = stopwatch_type::elapsed_time<float>(my_stopwatch);

  {
    std::stringstream strm;

    strm << "Time for calculation: "
         << std::fixed
         << std::setprecision(static_cast<std::streamsize>(INT8_C(1)))
         << "execution_time: "
         << execution_time
         << "s";

    std::cout << strm.str() << std::endl;
  }
}

#if (defined(__GNUC__) && defined(__clang__))
#pragma GCC diagnostic pop
#endif
