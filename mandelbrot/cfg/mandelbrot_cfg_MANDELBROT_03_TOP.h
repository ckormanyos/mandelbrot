///////////////////////////////////////////////////////////////////////////////
//      Copyright Christopher Kormanyos 2022.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef MANDELBROT_CFG_MANDELBROT_03_TOP_2022_03_14_H
  #define MANDELBROT_CFG_MANDELBROT_03_TOP_2022_03_14_H

  // This is a view of an upper part of the image (near the top of the classic full view).

  #define MANDELBROT_FILENAME_STRING            "MANDELBROT_03_TOP"

  #define MANDELBROT_CALCULATION_DIGITS10       31
  #define MANDELBROT_CALCULATION_PIXELS_1D      2048UL
  #define MANDELBROT_CALCULATION_ITERATIONS     2000UL

  #define MANDELBROT_POINT_DX_HALF              "0.282"
  #define MANDELBROT_POINT_CENTER_X             "-0.130"
  #define MANDELBROT_POINT_CENTER_Y             "0.856"

  #include <mandelbrot/cfg/mandelbrot_cfg.h>

#endif // MANDELBROT_CFG_MANDELBROT_03_TOP_2022_03_14_H
