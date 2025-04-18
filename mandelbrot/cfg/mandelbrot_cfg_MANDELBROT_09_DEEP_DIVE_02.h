///////////////////////////////////////////////////////////////////////////////
//      Copyright Christopher Kormanyos 2022 - 2025.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef MANDELBROT_CFG_MANDELBROT_09_DEEP_DIVE_02_2022_03_14_H
  #define MANDELBROT_CFG_MANDELBROT_09_DEEP_DIVE_02_2022_03_14_H

  #if (!defined(_MSC_VER) && defined(__cplusplus) && (__cplusplus >= 201703L))
  namespace ckormanyos::mandelbrot::config {
  #else
  namespace ckormanyos { namespace mandelbrot { namespace config { // NOLINT(modernize-concat-nested-namespaces)
  #endif

  // This is a deep zoom image.
  // Note: Use 79 or more decimal digits for this iteration.

  constexpr char MANDELBROT_FILENAME_STRING[]       = "MANDELBROT_09_DEEP_DIVE_02";

  constexpr int  MANDELBROT_COORD_PNT_DIGITS10      =      95;
  constexpr int  MANDELBROT_ITERATION_DIGITS10      =      24;
  constexpr int  MANDELBROT_CALCULATION_PIXELS_X    =    2048;
  constexpr int  MANDELBROT_CALCULATION_PIXELS_Y    =    2048;
  constexpr int  MANDELBROT_CALCULATION_ITERATIONS  =   15000;

  constexpr char MANDELBROT_POINT_DX_HALF[]         = "2.55E-55";
  constexpr char MANDELBROT_POINT_DY_HALF[]         = "2.55E-55";
  constexpr char MANDELBROT_POINT_CENTER_X[]        = "-1.29518908214777745701706417718568192670656646088488846921745350";
  constexpr char MANDELBROT_POINT_CENTER_Y[]        = "+0.44093698267832013888090367835626261211321462743139620368266100";

  template<typename CoordPntNumericType, typename IterateNumericType>
  using my_mandelbrot_generator_type = ::ckormanyos::mandelbrot::mandelbrot_generator_perturbative<CoordPntNumericType, IterateNumericType>;

  #if (!defined(_MSC_VER) && defined(__cplusplus) && (__cplusplus >= 201703L))
  } // namespace ckormanyos::mandelbrot::config
  #else
  } // namespace config
  } // namespace mandelbrot
  } // namespace ckormanyos
  #endif

#endif // MANDELBROT_CFG_MANDELBROT_09_DEEP_DIVE_02_2022_03_14_H
