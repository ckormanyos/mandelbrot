///////////////////////////////////////////////////////////////////////////////
//      Copyright Christopher Kormanyos 2022.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef MANDELBROT_CFG_MANDELBROT_04_SWIRL_2022_03_14_H
  #define MANDELBROT_CFG_MANDELBROT_04_SWIRL_2022_03_14_H

    // This is a fanning swirl image.

  #define MANDELBROT_FILENAME_STRING            "MANDELBROT_04_SWIRL"

  #define MANDELBROT_CALCULATION_DIGITS10       31
  #define MANDELBROT_CALCULATION_PIXELS_1D      2048UL
  #define MANDELBROT_CALCULATION_ITERATIONS     2000UL

  #define MANDELBROT_POINT_DX_HALF              "0.0002315"
  #define MANDELBROT_POINT_CENTER_X             "-0.749730"
  #define MANDELBROT_POINT_CENTER_Y             "-0.046608"

  #include <mandelbrot/cfg/mandelbrot_cfg.h>

#endif // MANDELBROT_CFG_MANDELBROT_04_SWIRL_2022_03_14_H
