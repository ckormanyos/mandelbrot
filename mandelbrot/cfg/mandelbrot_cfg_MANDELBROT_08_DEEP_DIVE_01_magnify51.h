///////////////////////////////////////////////////////////////////////////////
//      Copyright Christopher Kormanyos 2022 - 2025.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef MANDELBROT_CFG_MANDELBROT_08_DEEP_DIVE_01_MAGNIFY_51_2022_03_14_H
  #define MANDELBROT_CFG_MANDELBROT_08_DEEP_DIVE_01_MAGNIFY_51_2022_03_14_H

  #if (!defined(_MSC_VER) && defined(__cplusplus) && (__cplusplus >= 201703L))
  namespace ckormanyos::mandelbrot::config {
  #else
  namespace ckormanyos { namespace mandelbrot { namespace config { // NOLINT(modernize-concat-nested-namespaces)
  #endif

  // This is a deep zoom image.
  // Note: Use 143 or more decimal digits for this iteration.

  constexpr char MANDELBROT_FILENAME_STRING[]       = "MANDELBROT_08_DEEP_DIVE_01_magnify51";

  constexpr int  MANDELBROT_COORD_PNT_DIGITS10      =      76;
  constexpr int  MANDELBROT_ITERATION_DIGITS10      =      76;
  constexpr int  MANDELBROT_CALCULATION_PIXELS_X    =    2048;
  constexpr int  MANDELBROT_CALCULATION_PIXELS_Y    =    2048;
  constexpr int  MANDELBROT_CALCULATION_ITERATIONS  =    2000;

  constexpr char MANDELBROT_POINT_DX_HALF[]         = "1.4E-51";
  constexpr char MANDELBROT_POINT_DY_HALF[]         = "1.4E-51";
  constexpr char MANDELBROT_POINT_CENTER_X[]        = "-1.999999999138270118758274762908694988316809136636820959506";
  constexpr char MANDELBROT_POINT_CENTER_Y[]        = "+0.000000000000013148954435076375751362475668065050021517005";

  template<typename CoordPntNumericType, typename IterateNumericType>
  using my_mandelbrot_generator_type = ::ckormanyos::mandelbrot::mandelbrot_generator_trivial<CoordPntNumericType, IterateNumericType>;

  #if (!defined(_MSC_VER) && defined(__cplusplus) && (__cplusplus >= 201703L))
  } // namespace ckormanyos::mandelbrot::config
  #else
  } // namespace config
  } // namespace mandelbrot
  } // namespace ckormanyos
  #endif

#endif // MANDELBROT_CFG_MANDELBROT_08_DEEP_DIVE_01_MAGNIFY_51_2022_03_14_H
