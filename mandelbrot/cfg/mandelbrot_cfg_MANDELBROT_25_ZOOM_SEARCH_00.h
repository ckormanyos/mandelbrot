///////////////////////////////////////////////////////////////////////////////
//      Copyright Christopher Kormanyos 2022 - 2025.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef MANDELBROT_CFG_MANDELBROT_25_ZOOM_SEARCH_00_2024_04_07_H
  #define MANDELBROT_CFG_MANDELBROT_25_ZOOM_SEARCH_00_2024_04_07_H

  #if (!defined(_MSC_VER) && defined(__cplusplus) && (__cplusplus >= 201703L))
  namespace ckormanyos::mandelbrot::config {
  #else
  namespace ckormanyos { namespace mandelbrot { namespace config { // NOLINT(modernize-concat-nested-namespaces)
  #endif

  // There seems to be countless points to iterate that dive on and on,
  // deeper and deeper without showing any interesting variation.
  // There are, however, some interesting scenes such as this one.
  // The image resembles huge towers or wobbly columns
  // with meandering roads or streams below.

  constexpr char MANDELBROT_FILENAME_STRING[]       = "MANDELBROT_25_ZOOM_SEARCH_00";

  constexpr int  MANDELBROT_COORD_PNT_DIGITS10      =      58;
  constexpr int  MANDELBROT_ITERATION_DIGITS10      =      58;
  constexpr int  MANDELBROT_CALCULATION_PIXELS_X    =    2048;
  constexpr int  MANDELBROT_CALCULATION_PIXELS_Y    =    2048;
  constexpr int  MANDELBROT_CALCULATION_ITERATIONS  =    8000;

  constexpr char MANDELBROT_POINT_DX_HALF[]         = "1.1E-32";
  constexpr char MANDELBROT_POINT_DY_HALF[]         = "1.1E-32";
  constexpr char MANDELBROT_POINT_CENTER_X[]        = "+0.364780049945910647420847479526784741020";
  constexpr char MANDELBROT_POINT_CENTER_Y[]        = "-0.629477855705057324723497932015414892010";

  template<typename CoordPntNumericType, typename IterateNumericType>
  using my_mandelbrot_generator_type = ::ckormanyos::mandelbrot::mandelbrot_generator_trivial<CoordPntNumericType, IterateNumericType>;

  #if (!defined(_MSC_VER) && defined(__cplusplus) && (__cplusplus >= 201703L))
  } // namespace ckormanyos::mandelbrot::config
  #else
  } // namespace config
  } // namespace mandelbrot
  } // namespace ckormanyos
  #endif

#endif // MANDELBROT_CFG_MANDELBROT_25_ZOOM_SEARCH_00_2024_04_07_H
