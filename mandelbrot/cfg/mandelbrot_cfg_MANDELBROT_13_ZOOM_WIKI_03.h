///////////////////////////////////////////////////////////////////////////////
//      Copyright Christopher Kormanyos 2022 - 2024.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef MANDELBROT_CFG_MANDELBROT_13_ZOOM_WIKI_03_2022_03_16_H
  #define MANDELBROT_CFG_MANDELBROT_13_ZOOM_WIKI_03_2022_03_16_H

  // This is a medium zoom image from the zoom coordinates of:
  // http://en.wikipedia.org/wiki/File:Mandelbrot_sequence_new.gif
  // Note: Use 55 or more decimal digits for this iteration.

  constexpr char MANDELBROT_FILENAME_STRING[]       = "MANDELBROT_13_ZOOM_WIKI_03";

  constexpr int  MANDELBROT_CALCULATION_DIGITS10    =      55;
  constexpr int  MANDELBROT_CALCULATION_PIXELS_1D   =    2048;
  constexpr int  MANDELBROT_CALCULATION_PIXELS_2D   =    2048;
  constexpr int  MANDELBROT_CALCULATION_ITERATIONS  =   40000;

  constexpr char MANDELBROT_POINT_DX_HALF[]         = "2.25E-29";
  constexpr char MANDELBROT_POINT_DY_HALF[]         = "2.25E-29";
  constexpr char MANDELBROT_POINT_CENTER_X[]        = "-0.7436438870371587047521915061147750";
  constexpr char MANDELBROT_POINT_CENTER_Y[]        = "+0.1318259042053119704931320563851375";

  #include <mandelbrot/cfg/mandelbrot_cfg.h>

#endif // MANDELBROT_CFG_MANDELBROT_13_ZOOM_WIKI_03_2022_03_16_H
