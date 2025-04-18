///////////////////////////////////////////////////////////////////////////////
//      Copyright Christopher Kormanyos 2022 - 2025.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef MANDELBROT_CFG_MANDELBROT_60_SATELITE_REGION_01_2024_04_05_H
  #define MANDELBROT_CFG_MANDELBROT_60_SATELITE_REGION_01_2024_04_05_H

  #if (!defined(_MSC_VER) && defined(__cplusplus) && (__cplusplus >= 201703L))
  namespace ckormanyos::mandelbrot::config {
  #else
  namespace ckormanyos { namespace mandelbrot { namespace config { // NOLINT(modernize-concat-nested-namespaces)
  #endif

  constexpr char MANDELBROT_FILENAME_STRING[]       = "MANDELBROT_60_SATELITE_REGION_01";

  constexpr int  MANDELBROT_COORD_PNT_DIGITS10      =     128;
  constexpr int  MANDELBROT_ITERATION_DIGITS10      =      24;
  constexpr int  MANDELBROT_CALCULATION_PIXELS_X    =    2048;
  constexpr int  MANDELBROT_CALCULATION_PIXELS_Y    =    2048;
  constexpr int  MANDELBROT_CALCULATION_ITERATIONS  =   60000;

  constexpr char MANDELBROT_POINT_DX_HALF[]         = "8.1E-95";
  constexpr char MANDELBROT_POINT_DY_HALF[]         = "8.1E-95";

  // This iteration stops at a little Mandelbrot figure
  // at a magnification of approximately 10^{-104}

  constexpr char MANDELBROT_POINT_CENTER_X[]        = "-1.7683830049648722692890015019043698317959353872497374995305914106735151309161730899233435108340865903508510745";
  constexpr char MANDELBROT_POINT_CENTER_Y[]        = "-0.0035564756051580419085635598914228270868497588929218730141623308457205131419997685780856071519939478350604525";

  template<typename CoordPntNumericType, typename IterateNumericType>
  using my_mandelbrot_generator_type = ::ckormanyos::mandelbrot::mandelbrot_generator_perturbative<CoordPntNumericType, IterateNumericType>;

  #if (!defined(_MSC_VER) && defined(__cplusplus) && (__cplusplus >= 201703L))
  } // namespace ckormanyos::mandelbrot::config
  #else
  } // namespace config
  } // namespace mandelbrot
  } // namespace ckormanyos
  #endif

#endif // MANDELBROT_CFG_MANDELBROT_60_SATELITE_REGION_01_2024_04_05_H
