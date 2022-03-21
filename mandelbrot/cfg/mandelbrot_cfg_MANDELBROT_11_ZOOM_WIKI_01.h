///////////////////////////////////////////////////////////////////////////////
//      Copyright Christopher Kormanyos 2022.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef MANDELBROT_CFG_MANDELBROT_11_ZOOM_WIKI_01_2022_03_14_H
  #define MANDELBROT_CFG_MANDELBROT_11_ZOOM_WIKI_01_2022_03_14_H

  // This is a medium zoom image from the zoom coordinates of:
  // http://en.wikipedia.org/wiki/File:Mandelbrot_sequence_new.gif
  // Note: Use 55 or more decimal digits for this iteration.

  constexpr char MANDELBROT_FILENAME_STRING[]       = "MANDELBROT_11_ZOOM_WIKI_01";

  constexpr int  MANDELBROT_CALCULATION_DIGITS10    =      55;
  constexpr int  MANDELBROT_CALCULATION_PIXELS_1D   =    2048;
  constexpr int  MANDELBROT_CALCULATION_ITERATIONS  =   30000;

  constexpr char MANDELBROT_POINT_DX_HALF[]         =    "3.3E-27";
  constexpr char MANDELBROT_POINT_CENTER_X[]        =    "-0.743643887037158704752191506114774";
  constexpr char MANDELBROT_POINT_CENTER_Y[]        =    "0.131825904205311970493132056385139";

  #include <mandelbrot/cfg/mandelbrot_cfg.h>

#endif // MANDELBROT_CFG_MANDELBROT_11_ZOOM_WIKI_01_2022_03_14_H
