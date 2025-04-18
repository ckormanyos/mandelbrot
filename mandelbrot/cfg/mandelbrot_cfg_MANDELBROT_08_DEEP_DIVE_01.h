﻿///////////////////////////////////////////////////////////////////////////////
//      Copyright Christopher Kormanyos 2022 - 2025.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef MANDELBROT_CFG_MANDELBROT_08_DEEP_DIVE_01_2022_03_14_H
  #define MANDELBROT_CFG_MANDELBROT_08_DEEP_DIVE_01_2022_03_14_H

  #if (!defined(_MSC_VER) && defined(__cplusplus) && (__cplusplus >= 201703L))
  namespace ckormanyos::mandelbrot::config {
  #else
  namespace ckormanyos { namespace mandelbrot { namespace config { // NOLINT(modernize-concat-nested-namespaces)
  #endif

  // This is a deep zoom image.
  // Note: Use 143 or more decimal digits for this iteration.

  constexpr char MANDELBROT_FILENAME_STRING[]       = "MANDELBROT_08_DEEP_DIVE_01";

  constexpr int  MANDELBROT_COORD_PNT_DIGITS10      =     143;
  constexpr int  MANDELBROT_ITERATION_DIGITS10      =      24;
  constexpr int  MANDELBROT_CALCULATION_PIXELS_X    =    2048;
  constexpr int  MANDELBROT_CALCULATION_PIXELS_Y    =    2048;
  constexpr int  MANDELBROT_CALCULATION_ITERATIONS  =    2000;

  constexpr char MANDELBROT_POINT_DX_HALF[]         = "1.25E-107";
  constexpr char MANDELBROT_POINT_DY_HALF[]         = "1.25E-107";
  constexpr char MANDELBROT_POINT_CENTER_X[]        = "-1.99999999913827011875827476290869498831680913663682095950680227271547027727918984035447670553861909622481524124";
  constexpr char MANDELBROT_POINT_CENTER_Y[]        = "+0.00000000000001314895443507637575136247566806505002151700520912095709529449343530548994027524594471095886432006";

  template<typename CoordPntNumericType, typename IterateNumericType>
  using my_mandelbrot_generator_type = ::ckormanyos::mandelbrot::mandelbrot_generator_perturbative<CoordPntNumericType, IterateNumericType>;

  #if (!defined(_MSC_VER) && defined(__cplusplus) && (__cplusplus >= 201703L))
  } // namespace ckormanyos::mandelbrot::config
  #else
  } // namespace config
  } // namespace mandelbrot
  } // namespace ckormanyos
  #endif

#endif // MANDELBROT_CFG_MANDELBROT_08_DEEP_DIVE_01_2022_03_14_H
