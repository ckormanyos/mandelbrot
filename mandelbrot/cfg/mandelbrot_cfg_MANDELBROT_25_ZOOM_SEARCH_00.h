///////////////////////////////////////////////////////////////////////////////
//      Copyright Christopher Kormanyos 2024.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef MANDELBROT_CFG_MANDELBROT_25_ZOOM_SEARCH_00_2024_04_07_H
  #define MANDELBROT_CFG_MANDELBROT_25_ZOOM_SEARCH_00_2024_04_07_H

  constexpr char MANDELBROT_FILENAME_STRING[]       = "MANDELBROT_25_ZOOM_SEARCH";

  constexpr int  MANDELBROT_CALCULATION_DIGITS10    =      42;
  constexpr int  MANDELBROT_CALCULATION_PIXELS_1D   =    1536;
  constexpr int  MANDELBROT_CALCULATION_ITERATIONS  =   40000;

  //constexpr char MANDELBROT_POINT_DX_HALF[]         = "1.1E-18";
  constexpr char MANDELBROT_POINT_DX_HALF[]         = "1.1E-13";
  constexpr char MANDELBROT_POINT_CENTER_X[]        = "+0.360964144650305208600";
  constexpr char MANDELBROT_POINT_CENTER_Y[]        = "-0.615180770532733982050";

  #include <mandelbrot/cfg/mandelbrot_cfg.h>

#endif // MANDELBROT_CFG_MANDELBROT_25_ZOOM_SEARCH_00_2024_04_07_H
