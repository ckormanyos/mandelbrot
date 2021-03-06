///////////////////////////////////////////////////////////////////////////////
//      Copyright Christopher Kormanyos 2022.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef MANDELBROT_CFG_MANDELBROT_06_BRANCHES_2022_03_14_H
  #define MANDELBROT_CFG_MANDELBROT_06_BRANCHES_2022_03_14_H

  // This is a spiral image of branches.

  constexpr char MANDELBROT_FILENAME_STRING[]       = "MANDELBROT_06_BRANCHES";

  constexpr int  MANDELBROT_CALCULATION_DIGITS10    =      31;
  constexpr int  MANDELBROT_CALCULATION_PIXELS_1D   =    2048;
  constexpr int  MANDELBROT_CALCULATION_ITERATIONS  =    2000;

  constexpr char MANDELBROT_POINT_DX_HALF[]         = "4.2E-12";
  constexpr char MANDELBROT_POINT_CENTER_X[]        = "0.3369844464873";
  constexpr char MANDELBROT_POINT_CENTER_Y[]        = "0.0487782196791";

  #include <mandelbrot/cfg/mandelbrot_cfg.h>

#endif // MANDELBROT_CFG_MANDELBROT_06_BRANCHES_2022_03_14_H
