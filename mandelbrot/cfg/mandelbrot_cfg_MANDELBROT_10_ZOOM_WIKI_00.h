///////////////////////////////////////////////////////////////////////////////
//      Copyright Christopher Kormanyos 2022 - 2024.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef MANDELBROT_CFG_MANDELBROT_10_ZOOM_WIKI_00_2022_03_14_H
  #define MANDELBROT_CFG_MANDELBROT_10_ZOOM_WIKI_00_2022_03_14_H

  // This is a medium zoom image from the zoom coordinates of:
  // http://en.wikipedia.org/wiki/File:Mandelbrot_sequence_new.gif
  // Note: Use 55 or more decimal digits for this iteration.

  constexpr char MANDELBROT_FILENAME_STRING[]       = "MANDELBROT_10_ZOOM_WIKI_00";

  constexpr int  MANDELBROT_SETUPs_DIGITS10         =      55;
  constexpr int  MANDELBROT_ITERATION_DIGITS10      =      55;
  constexpr int  MANDELBROT_CALCULATION_PIXELS_X    =    2048;
  constexpr int  MANDELBROT_CALCULATION_PIXELS_Y    =    2048;
  constexpr int  MANDELBROT_CALCULATION_ITERATIONS  =   20000;

  constexpr char MANDELBROT_POINT_DX_HALF[]         = "3.1E-25";
  constexpr char MANDELBROT_POINT_DY_HALF[]         = "3.1E-25";
  constexpr char MANDELBROT_POINT_CENTER_X[]        = "-0.7436438870371587047521915061147750";
  constexpr char MANDELBROT_POINT_CENTER_Y[]        = "+0.1318259042053119704931320563851375";

  #define MANDELBROT_GENERATOR_TYPE mandelbrot_generator_trivial // NOLINT(cppcoreguidelines-macro-usage)

  #include <mandelbrot/cfg/mandelbrot_cfg.h>

#endif // MANDELBROT_CFG_MANDELBROT_10_ZOOM_WIKI_00_2022_03_14_H
