///////////////////////////////////////////////////////////////////////////////
//      Copyright Christopher Kormanyos 2022 - 2025.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef MANDELBROT_CFG_MANDELBROT_XX_TRY_POINTS_2024_04_30_H
  #define MANDELBROT_CFG_MANDELBROT_XX_TRY_POINTS_2024_04_30_H

  #if (defined(MANDELBROT_CXX_VERSION) && (MANDELBROT_CXX_VERSION >= 201703L))
  namespace ckormanyos::mandelbrot::config {
  #else
  namespace ckormanyos { namespace mandelbrot { namespace config { // NOLINT(modernize-concat-nested-namespaces)
  #endif

  // This is a specialized configuration file intended to be used
  // for simply trying out deep dives, such as those found by the
  // MandelbrotDiscovery program or found by other methods.

  constexpr char MANDELBROT_FILENAME_STRING[]       = "MANDELBROT_XX_TRY_POINTS";

  constexpr int  MANDELBROT_COORD_PNT_DIGITS10      =     114;
  constexpr int  MANDELBROT_ITERATION_DIGITS10      =      28;
  constexpr int  MANDELBROT_CALCULATION_PIXELS_X    =    2048;
  constexpr int  MANDELBROT_CALCULATION_PIXELS_Y    =    2048;
  constexpr int  MANDELBROT_CALCULATION_ITERATIONS  =    6000;

  constexpr char MANDELBROT_POINT_DX_HALF[]         = "9.9E-54";
  constexpr char MANDELBROT_POINT_DY_HALF[]         = "9.9E-54";
  constexpr char MANDELBROT_POINT_CENTER_X[]        = "-1.26183755775978505622751723858815584827746138110013138369840150537109375";
  constexpr char MANDELBROT_POINT_CENTER_Y[]        = "-0.04542045407677098298613113871168335684828349326726677792959402958984375";

  template<typename CoordPntNumericType, typename IterateNumericType>
  using my_mandelbrot_generator_type = ::ckormanyos::mandelbrot::mandelbrot_generator_perturbative<CoordPntNumericType, IterateNumericType>;

  #if (defined(MANDELBROT_CXX_VERSION) && (MANDELBROT_CXX_VERSION >= 201703L))
  } // namespace ckormanyos::mandelbrot::config
  #else
  } // namespace config
  } // namespace mandelbrot
  } // namespace ckormanyos
  #endif

#endif // MANDELBROT_CFG_MANDELBROT_XX_TRY_POINTS_2024_04_30_H
