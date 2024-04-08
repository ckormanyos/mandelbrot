///////////////////////////////////////////////////////////////////////////////
//      Copyright Christopher Kormanyos 2024.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef MANDELBROT_CFG_MANDELBROT_25_ZOOM_SEARCH_00_2024_04_07_H
  #define MANDELBROT_CFG_MANDELBROT_25_ZOOM_SEARCH_00_2024_04_07_H

  constexpr char MANDELBROT_FILENAME_STRING[]       = "MANDELBROT_25_ZOOM_SEARCH_00";

  constexpr int  MANDELBROT_CALCULATION_DIGITS10    =      58;
  constexpr int  MANDELBROT_CALCULATION_PIXELS_1D   =    2048;
  constexpr int  MANDELBROT_CALCULATION_ITERATIONS  =    8000;

  // There are countless points to iterate that dive on and on,
  // deeper and deeper without showing any interesting variation.
  // There are, however, some interesting scenes such as this one.
  // The image resembles huge towers or wobbly columns
  // with meandering roads or streams below.

  constexpr char MANDELBROT_POINT_DX_HALF[]         = "1.1E-32";
  //constexpr char MANDELBROT_POINT_DX_HALF[]         = "1.1E-36";
  constexpr char MANDELBROT_POINT_CENTER_X[]        = "+0.364780049945910647420847479526784741020";
  constexpr char MANDELBROT_POINT_CENTER_Y[]        = "-0.629477855705057324723497932015414892010";

  #include <mandelbrot/cfg/mandelbrot_cfg.h>

#endif // MANDELBROT_CFG_MANDELBROT_25_ZOOM_SEARCH_00_2024_04_07_H
