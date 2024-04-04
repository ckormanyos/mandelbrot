///////////////////////////////////////////////////////////////////////////////
//      Copyright Christopher Kormanyos 2024.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef MANDELBROT_CFG_MANDELBROT_45_SEAHORSE_OTHER_01_2024_04_01_H
  #define MANDELBROT_CFG_MANDELBROT_45_SEAHORSE_OTHER_01_2024_04_01_H

  constexpr char MANDELBROT_FILENAME_STRING[]       = "MANDELBROT_45_SEAHORSE_OTHER_01";

  constexpr int  MANDELBROT_CALCULATION_DIGITS10    =     49;
  constexpr int  MANDELBROT_CALCULATION_PIXELS_1D   =   2048;
  constexpr int  MANDELBROT_CALCULATION_PIXELS_2D   =   2048;
  constexpr int  MANDELBROT_CALCULATION_ITERATIONS  =  20000;

  //constexpr char MANDELBROT_POINT_DX_HALF[]         = "1.0E-27";
  constexpr char MANDELBROT_POINT_DX_HALF[]         = "1.0E-21";
  constexpr char MANDELBROT_POINT_DY_HALF[]         = "1.0E-21";
  //constexpr char MANDELBROT_POINT_DX_HALF[]         = "1.0E-30";
  constexpr char MANDELBROT_POINT_CENTER_X[]        = "-0.745605122368264995520769522753080";
  constexpr char MANDELBROT_POINT_CENTER_Y[]        = "+0.112859495427252849953537572395510";

  #include <mandelbrot/cfg/mandelbrot_cfg.h>

#endif // MANDELBROT_CFG_MANDELBROT_45_SEAHORSE_OTHER_01_2024_04_01_H
