///////////////////////////////////////////////////////////////////////////////
//      Copyright Christopher Kormanyos 2022.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef MANDELBROT_CFG_MANDELBROT_09_DEEP_DIVE_02_2022_03_14_H
  #define MANDELBROT_CFG_MANDELBROT_09_DEEP_DIVE_02_2022_03_14_H

  // This is a deep zoom image.
  // Note: Use 79 or more decimal digits for this iteration.

  constexpr char MANDELBROT_FILENAME_STRING[]       = "MANDELBROT_09_DEEP_DIVE_02";

  constexpr int  MANDELBROT_CALCULATION_DIGITS10    =      95;
  constexpr int  MANDELBROT_CALCULATION_PIXELS_1D   =    2048;
  constexpr int  MANDELBROT_CALCULATION_PIXELS_2D   =    2048;
  constexpr int  MANDELBROT_CALCULATION_ITERATIONS  =   15000;

  constexpr char MANDELBROT_POINT_DX_HALF[]         = "2.55E-55";
  constexpr char MANDELBROT_POINT_DY_HALF[]         = "2.55E-55";
  constexpr char MANDELBROT_POINT_CENTER_X[]        = "-1.295189082147777457017064177185681926706566460884888469217456";
  constexpr char MANDELBROT_POINT_CENTER_Y[]        = "0.440936982678320138880903678356262612113214627431396203682661";

  #include <mandelbrot/cfg/mandelbrot_cfg.h>

#endif // MANDELBROT_CFG_MANDELBROT_09_DEEP_DIVE_02_2022_03_14_H
