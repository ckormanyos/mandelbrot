///////////////////////////////////////////////////////////////////////////////
//      Copyright Christopher Kormanyos 2022 - 2024.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef MANDELBROT_CFG_MANDELBROT_99_TRY_POINTS_2024_04_30_H
  #define MANDELBROT_CFG_MANDELBROT_99_TRY_POINTS_2024_04_30_H

  // This is the classic full immage.

  constexpr char MANDELBROT_FILENAME_STRING[]       = "MANDELBROT_99_TRY_POINTS";

  constexpr int  MANDELBROT_COORD_PNT_DIGITS10      =      82;
  constexpr int  MANDELBROT_ITERATION_DIGITS10      =      82;
  constexpr int  MANDELBROT_CALCULATION_PIXELS_X    =    2048;
  constexpr int  MANDELBROT_CALCULATION_PIXELS_Y    =    2048;
  constexpr int  MANDELBROT_CALCULATION_ITERATIONS  =   20000;

  constexpr char MANDELBROT_POINT_DX_HALF[]         = "9.8E-54";
  constexpr char MANDELBROT_POINT_DY_HALF[]         = "9.8E-54";
  constexpr char MANDELBROT_POINT_CENTER_X[]        = "-1.252508293681668981848141890554793831651285056960614677979723771484375";
  constexpr char MANDELBROT_POINT_CENTER_Y[]        = "-0.034697514077867448435398475652836924954212095455636155250775048828125";

  #if 0
  constexpr int  MANDELBROT_COORD_PNT_DIGITS10      =      64;
  constexpr int  MANDELBROT_ITERATION_DIGITS10      =      64;
  constexpr int  MANDELBROT_CALCULATION_PIXELS_X    =    2048;
  constexpr int  MANDELBROT_CALCULATION_PIXELS_Y    =    2048;
  constexpr int  MANDELBROT_CALCULATION_ITERATIONS  =   20000;

  constexpr char MANDELBROT_POINT_DX_HALF[]         = "8.8E-37";
  constexpr char MANDELBROT_POINT_DY_HALF[]         = "8.8E-37";
  constexpr char MANDELBROT_POINT_CENTER_X[]        = "-0.86163746968572280977496717541865570064658203125";
  constexpr char MANDELBROT_POINT_CENTER_Y[]        = "-0.27782204381125878606894596506117674816369140625";
  #endif

  #define MANDELBROT_GENERATOR_TYPE mandelbrot_generator_trivial // NOLINT(cppcoreguidelines-macro-usage)

  #include <mandelbrot/cfg/mandelbrot_cfg.h>

#endif // MANDELBROT_CFG_MANDELBROT_99_TRY_POINTS_2024_04_30_H
