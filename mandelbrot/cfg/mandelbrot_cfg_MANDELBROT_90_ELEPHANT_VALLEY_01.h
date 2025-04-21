///////////////////////////////////////////////////////////////////////////////
//      Copyright Christopher Kormanyos 2025.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef MANDELBROT_CFG_MANDELBROT_90_ELEPHANT_VALLEY_01_2025_04_21_H
  #define MANDELBROT_CFG_MANDELBROT_90_ELEPHANT_VALLEY_01_2025_04_21_H

  #if (!defined(_MSC_VER) && defined(__cplusplus) && (__cplusplus >= 201703L))
  namespace ckormanyos::mandelbrot::config {
  #else
  namespace ckormanyos { namespace mandelbrot { namespace config { // NOLINT(modernize-concat-nested-namespaces)
  #endif

  // This is a specialized configuration file intended to be used
  // for simply trying out deep dives, such as those found by the
  // MandelbrotDiscovery program or found by other methods.
  constexpr char MANDELBROT_FILENAME_STRING[]       = "MANDELBROT_90_ELEPHANT_VALLEY_01";

  constexpr int  MANDELBROT_COORD_PNT_DIGITS10      =      64;
  constexpr int  MANDELBROT_ITERATION_DIGITS10      =      24;
  constexpr int  MANDELBROT_CALCULATION_PIXELS_X    =    2048;
  constexpr int  MANDELBROT_CALCULATION_PIXELS_Y    =    2048;
  constexpr int  MANDELBROT_CALCULATION_ITERATIONS  =   30000;

  constexpr char MANDELBROT_POINT_DX_HALF[]         = "4.8E-38";
  constexpr char MANDELBROT_POINT_DY_HALF[]         = "4.8E-38";
  constexpr char MANDELBROT_POINT_CENTER_X[]        = "+0.4274238308054431189235745768979341745078162705078125";
  constexpr char MANDELBROT_POINT_CENTER_Y[]        = "+0.2179337474437253842422209514104659052741596646484375";

  template<typename CoordPntNumericType, typename IterateNumericType>
  using my_mandelbrot_generator_type = ::ckormanyos::mandelbrot::mandelbrot_generator_perturbative<CoordPntNumericType, IterateNumericType>;

  #if (!defined(_MSC_VER) && defined(__cplusplus) && (__cplusplus >= 201703L))
  } // namespace ckormanyos::mandelbrot::config
  #else
  } // namespace config
  } // namespace mandelbrot
  } // namespace ckormanyos
  #endif

#endif // MANDELBROT_CFG_MANDELBROT_90_ELEPHANT_VALLEY_01_2025_04_21_H
