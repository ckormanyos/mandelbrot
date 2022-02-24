///////////////////////////////////////////////////////////////////////////////
//      Copyright Christopher Kormanyos 2022.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef MANDELBROT_CFG_MANDELBROT_01_FULL_2022_02_24_H
  #define MANDELBROT_CFG_MANDELBROT_01_FULL_2022_02_24_H

  // This is the classic full immage.

  #define MANDELBROT_FILENAME_STRING            "MANDELBROT_01_FULL"

  #define MANDELBROT_CALCULATION_DIGITS10       37
  #define MANDELBROT_CALCULATION_PIXELS_1D      2048UL
  #define MANDELBROT_CALCULATION_ITERATIONS     2000UL

  #define MANDELBROT_POINT_DX_HALF              +1.25L
  #define MANDELBROT_POINT_CENTER_X             -0.75L
  #define MANDELBROT_POINT_CENTER_Y             +0.0L

  #include <mandelbrot/cfg/mandelbrot_cfg.h>

#endif // MANDELBROT_CFG_MANDELBROT_01_FULL_2022_02_24_H
