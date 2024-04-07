///////////////////////////////////////////////////////////////////////////////
//      Copyright Christopher Kormanyos 2024.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef MANDELBROT_CFG_MANDELBROT_70_DOUADY_RABBIT_03_2024_04_07_H
  #define MANDELBROT_CFG_MANDELBROT_70_DOUADY_RABBIT_03_2024_04_07_H

  constexpr char MANDELBROT_FILENAME_STRING[]       = "MANDELBROT_70_DOUADY_RABBIT_03";

  constexpr int  MANDELBROT_CALCULATION_DIGITS10    =      52;
  constexpr int  MANDELBROT_CALCULATION_PIXELS_1D   =     128;
  constexpr int  MANDELBROT_CALCULATION_ITERATIONS  =   80000;

  constexpr char MANDELBROT_POINT_DX_HALF[]         = "1.1E-28";

  constexpr char MANDELBROT_POINT_CENTER_X[]        = "-0.7801539136839937487185685844950";
  constexpr char MANDELBROT_POINT_CENTER_Y[]        = "+0.1334867309879689900412281286100";

  #if 0
  constexpr int  MANDELBROT_CALCULATION_DIGITS10    =      48;
  constexpr int  MANDELBROT_CALCULATION_PIXELS_1D   =    2048;
  constexpr int  MANDELBROT_CALCULATION_ITERATIONS  =   70000;

  constexpr char MANDELBROT_POINT_DX_HALF[]         = "1.1E-21";
  //constexpr char MANDELBROT_POINT_DX_HALF[]         = "1.1E-23";

  constexpr char MANDELBROT_POINT_CENTER_X[]        = "-0.78015391368399374871881775";
  constexpr char MANDELBROT_POINT_CENTER_Y[]        = "+0.13348673098796899004137610";
  #endif


  #include <mandelbrot/cfg/mandelbrot_cfg.h>

#endif // MANDELBROT_CFG_MANDELBROT_70_DOUADY_RABBIT_03_2024_04_07_H
