///////////////////////////////////////////////////////////////////////////////
//      Copyright Christopher Kormanyos 2022 - 2024.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef MANDELBROT_CFG_MANDELBROT_10_ZOOM_WIKI_00_rect_2024_04_12_H
  #define MANDELBROT_CFG_MANDELBROT_10_ZOOM_WIKI_00_rect_2024_04_12_H

  // This is a medium zoom image from the zoom coordinates of:
  // http://en.wikipedia.org/wiki/File:Mandelbrot_sequence_new.gif
  // Note: Use 55 or more decimal digits for this iteration.

  constexpr char MANDELBROT_FILENAME_STRING[]       = "MANDELBROT_10_ZOOM_WIKI_00_rect";

  constexpr int  MANDELBROT_COORD_PNT_DIGITS10      =      60;
  constexpr int  MANDELBROT_ITERATION_DIGITS10      =      60;
  constexpr int  MANDELBROT_CALCULATION_PIXELS_X    =    3840;
  constexpr int  MANDELBROT_CALCULATION_PIXELS_Y    =    2160;
  constexpr int  MANDELBROT_CALCULATION_ITERATIONS  =  100000;

  constexpr char MANDELBROT_POINT_DX_HALF[]         = "3.910000E-26"; // at 2.2E-32 exists a mandelbrot
  constexpr char MANDELBROT_POINT_DY_HALF[]         = "2.199375E-26";
  constexpr char MANDELBROT_POINT_CENTER_X[]        = "-0.7436438870371587047521915061147785";
  constexpr char MANDELBROT_POINT_CENTER_Y[]        = "+0.1318259042053119704931320563851390";

  #define MANDELBROT_GENERATOR_TYPE mandelbrot_generator_trivial // NOLINT(cppcoreguidelines-macro-usage)

  #include <mandelbrot/cfg/mandelbrot_cfg.h>

#endif // MANDELBROT_CFG_MANDELBROT_10_ZOOM_WIKI_00_rect_2024_04_12_H
