///////////////////////////////////////////////////////////////////////////////
//      Copyright Christopher Kormanyos 2022 - 2025.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef MANDELBROT_CFG_MANDELBROT_80_SEARCH_HALO_01_2024_04_28_H
  #define MANDELBROT_CFG_MANDELBROT_80_SEARCH_HALO_01_2024_04_28_H

  #if (!defined(_MSC_VER) && defined(__cplusplus) && (__cplusplus >= 201703L))
  namespace ckormanyos::mandelbrot::config {
  #else
  namespace ckormanyos { namespace mandelbrot { namespace config { // NOLINT(modernize-concat-nested-namespaces)
  #endif

  constexpr char MANDELBROT_FILENAME_STRING[]       = "MANDELBROT_80_SEARCH_HALO_01";

  constexpr int  MANDELBROT_COORD_PNT_DIGITS10      =      96;
  constexpr int  MANDELBROT_ITERATION_DIGITS10      =      96;
  constexpr int  MANDELBROT_CALCULATION_PIXELS_X    =    2048;
  constexpr int  MANDELBROT_CALCULATION_PIXELS_Y    =    2048;
  constexpr int  MANDELBROT_CALCULATION_ITERATIONS  =   30000;

  constexpr char MANDELBROT_POINT_DX_HALF[]         = "2.35E-68";
  constexpr char MANDELBROT_POINT_DY_HALF[]         = "2.35E-68";

  constexpr char MANDELBROT_POINT_CENTER_X[]        = "-0.1527954200232027963683438945980760107549567318352795868646210533745261025390625";
  constexpr char MANDELBROT_POINT_CENTER_Y[]        = "-1.0401418443849923493531926993772070499842930810917161061808470829825106373046875";

  template<typename CoordPntNumericType, typename IterateNumericType>
  using my_mandelbrot_generator_type = ::ckormanyos::mandelbrot::mandelbrot_generator_trivial<CoordPntNumericType, IterateNumericType>;

  #if (!defined(_MSC_VER) && defined(__cplusplus) && (__cplusplus >= 201703L))
  } // namespace ckormanyos::mandelbrot::config
  #else
  } // namespace config
  } // namespace mandelbrot
  } // namespace ckormanyos
  #endif

#endif // MANDELBROT_CFG_MANDELBROT_80_SEARCH_HALO_01_2024_04_28_H
