///////////////////////////////////////////////////////////////////////////////
//      Copyright Christopher Kormanyos 2024.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef MANDELBROT_CFG_MANDELBROT_72_DOUADY_RABBIT_03_2024_04_07_H
  #define MANDELBROT_CFG_MANDELBROT_72_DOUADY_RABBIT_03_2024_04_07_H

  constexpr char MANDELBROT_FILENAME_STRING[]       = "MANDELBROT_72_DOUADY_RABBIT_03";

  constexpr int  MANDELBROT_COORD_PNT_DIGITS10      =      51;
  constexpr int  MANDELBROT_ITERATION_DIGITS10      =      51;
  constexpr int  MANDELBROT_CALCULATION_PIXELS_X    =    2048;
  constexpr int  MANDELBROT_CALCULATION_PIXELS_Y    =    2048;
  constexpr int  MANDELBROT_CALCULATION_ITERATIONS  =  100000;

  // This iteration runs into a stretched Mandelbrot-like
  // figure at a magnification of approximately 10^30.

  // Even though the digit count is relatively low for this
  // particular iteration, it required quite a long total
  // time to generate the full 2048*2048 pixel image.

  constexpr char MANDELBROT_POINT_DX_HALF[]         = "1.4E-27";
  constexpr char MANDELBROT_POINT_DY_HALF[]         = "1.4E-27";

  constexpr char MANDELBROT_POINT_CENTER_X[]        = "-0.780153913683993748718568584494930";
  constexpr char MANDELBROT_POINT_CENTER_Y[]        = "+0.133486730987968990041228128620890";

  #define MANDELBROT_GENERATOR_TYPE mandelbrot_generator_trivial // NOLINT(cppcoreguidelines-macro-usage)

  #include <mandelbrot/cfg/mandelbrot_cfg.h>

#endif // MANDELBROT_CFG_MANDELBROT_72_DOUADY_RABBIT_03_2024_04_07_H
