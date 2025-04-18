///////////////////////////////////////////////////////////////////////////////
//      Copyright Christopher Kormanyos 2022 - 2025.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef MANDELBROT_CFG_MANDELBROT_70_DOUADY_RABBIT_01_2024_04_06_H
  #define MANDELBROT_CFG_MANDELBROT_70_DOUADY_RABBIT_01_2024_04_06_H

  #if (!defined(_MSC_VER) && defined(__cplusplus) && (__cplusplus >= 201703L))
  namespace ckormanyos::mandelbrot::config {
  #else
  namespace ckormanyos { namespace mandelbrot { namespace config { // NOLINT(modernize-concat-nested-namespaces)
  #endif

  constexpr char MANDELBROT_FILENAME_STRING[]       = "MANDELBROT_70_DOUADY_RABBIT_01";

  constexpr int  MANDELBROT_COORD_PNT_DIGITS10      =      36;
  constexpr int  MANDELBROT_ITERATION_DIGITS10      =      36;
  constexpr int  MANDELBROT_CALCULATION_PIXELS_X    =    2048;
  constexpr int  MANDELBROT_CALCULATION_PIXELS_Y    =    2048;
  constexpr int  MANDELBROT_CALCULATION_ITERATIONS  =   10000;

  constexpr char MANDELBROT_POINT_DX_HALF[]         = "9.0E-7";
  constexpr char MANDELBROT_POINT_DY_HALF[]         = "9.0E-7";

  constexpr char MANDELBROT_POINT_CENTER_X[]        = "-0.7801536846";
  constexpr char MANDELBROT_POINT_CENTER_Y[]        = "+0.1334866332";

  template<typename CoordPntNumericType, typename IterateNumericType>
  using my_mandelbrot_generator_type = ::ckormanyos::mandelbrot::mandelbrot_generator_trivial<CoordPntNumericType, IterateNumericType>;

  #if (!defined(_MSC_VER) && defined(__cplusplus) && (__cplusplus >= 201703L))
  } // namespace ckormanyos::mandelbrot::config
  #else
  } // namespace config
  } // namespace mandelbrot
  } // namespace ckormanyos
  #endif

#endif // MANDELBROT_CFG_MANDELBROT_70_DOUADY_RABBIT_01_2024_04_06_H
