///////////////////////////////////////////////////////////////////////////////
//      Copyright Christopher Kormanyos 2022 - 2025.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef MANDELBROT_CFG_MANDELBROT_99_TRY_POINTS_2024_04_30_H
  #define MANDELBROT_CFG_MANDELBROT_99_TRY_POINTS_2024_04_30_H

  #if (!defined(_MSC_VER) && defined(__cplusplus) && (__cplusplus >= 201703L))
  namespace ckormanyos::mandelbrot::config {
  #else
  namespace ckormanyos { namespace mandelbrot { namespace config { // NOLINT(modernize-concat-nested-namespaces)
  #endif

  // This is a specialized configuration file intended to be used
  // for simply trying out deep dives, such as those found by the
  // MandelbrotDiscovery program or found by other methods.

  constexpr char MANDELBROT_FILENAME_STRING[]       = "MANDELBROT_99_TRY_POINTS";

  constexpr int  MANDELBROT_COORD_PNT_DIGITS10      =      93;
  constexpr int  MANDELBROT_ITERATION_DIGITS10      =      24;
  constexpr int  MANDELBROT_CALCULATION_PIXELS_X    =    2048;
  constexpr int  MANDELBROT_CALCULATION_PIXELS_Y    =    2048;
  constexpr int  MANDELBROT_CALCULATION_ITERATIONS  =   14000;

  constexpr char MANDELBROT_POINT_DX_HALF[]         = "1.5E-65";
  constexpr char MANDELBROT_POINT_DY_HALF[]         = "1.5E-65";
  constexpr char MANDELBROT_POINT_CENTER_X[]        = "-1.253463479447302815474865258549389016280094034767189031956233695315741236328125";
  constexpr char MANDELBROT_POINT_CENTER_Y[]        = "-0.028042431732257382427343123373114054881891874392209595538604931514826763671875";

  template<typename CoordPntNumericType, typename IterateNumericType>
  using my_mandelbrot_generator_type = ::ckormanyos::mandelbrot::mandelbrot_generator_perturbative<CoordPntNumericType, IterateNumericType>;

  #if (!defined(_MSC_VER) && defined(__cplusplus) && (__cplusplus >= 201703L))
  } // namespace ckormanyos::mandelbrot::config
  #else
  } // namespace config
  } // namespace mandelbrot
  } // namespace ckormanyos
  #endif

#endif // MANDELBROT_CFG_MANDELBROT_99_TRY_POINTS_2024_04_30_H
