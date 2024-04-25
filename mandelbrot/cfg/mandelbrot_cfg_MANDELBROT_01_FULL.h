///////////////////////////////////////////////////////////////////////////////
//      Copyright Christopher Kormanyos 2022 - 2024.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef MANDELBROT_CFG_MANDELBROT_01_FULL_2022_02_24_H
  #define MANDELBROT_CFG_MANDELBROT_01_FULL_2022_02_24_H

  // This is the classic full immage.

  constexpr char MANDELBROT_FILENAME_STRING[]       = "MANDELBROT_01_FULL";

  constexpr int  MANDELBROT_SETUP_DIGITS10          =      37;
  constexpr int  MANDELBROT_CALCULATION_DIGITS10    =      17;
  constexpr int  MANDELBROT_CALCULATION_PIXELS_X    =    2048;
  constexpr int  MANDELBROT_CALCULATION_PIXELS_Y    =    2048;
  constexpr int  MANDELBROT_CALCULATION_ITERATIONS  =    2000;

  constexpr char MANDELBROT_POINT_DX_HALF[]         = "1.35";
  constexpr char MANDELBROT_POINT_DY_HALF[]         = "1.35";
  constexpr char MANDELBROT_POINT_CENTER_X[]        = "-0.75";
  constexpr char MANDELBROT_POINT_CENTER_Y[]        = "+0.00";

  #include <mandelbrot/cfg/mandelbrot_cfg.h>

#endif // MANDELBROT_CFG_MANDELBROT_01_FULL_2022_02_24_H
