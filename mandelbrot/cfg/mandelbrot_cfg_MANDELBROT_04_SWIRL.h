///////////////////////////////////////////////////////////////////////////////
//      Copyright Christopher Kormanyos 2022.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef MANDELBROT_CFG_MANDELBROT_04_SWIRL_2022_03_14_H
  #define MANDELBROT_CFG_MANDELBROT_04_SWIRL_2022_03_14_H

    // This is a fanning swirl image.

  constexpr char MANDELBROT_FILENAME_STRING[]       = "MANDELBROT_04_SWIRL";

  constexpr int  MANDELBROT_COORD_PNT_DIGITS10      =      31;
  constexpr int  MANDELBROT_ITERATION_DIGITS10      =      20;
  constexpr int  MANDELBROT_CALCULATION_PIXELS_X    =    2048;
  constexpr int  MANDELBROT_CALCULATION_PIXELS_Y    =    2048;
  constexpr int  MANDELBROT_CALCULATION_ITERATIONS  =    2000;

  constexpr char MANDELBROT_POINT_DX_HALF[]         = "0.0002315";
  constexpr char MANDELBROT_POINT_DY_HALF[]         = "0.0002315";
  constexpr char MANDELBROT_POINT_CENTER_X[]        = "-0.749730";
  constexpr char MANDELBROT_POINT_CENTER_Y[]        = "-0.046608";

  #include <mandelbrot/cfg/mandelbrot_cfg.h>

#endif // MANDELBROT_CFG_MANDELBROT_04_SWIRL_2022_03_14_H
