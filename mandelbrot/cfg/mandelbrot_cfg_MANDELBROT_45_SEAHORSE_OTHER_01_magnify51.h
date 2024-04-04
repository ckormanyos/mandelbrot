///////////////////////////////////////////////////////////////////////////////
//      Copyright Christopher Kormanyos 2024.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef MANDELBROT_CFG_MANDELBROT_45_SEAHORSE_OTHER_01_MAGNIFY_51_2024_04_01_H
  #define MANDELBROT_CFG_MANDELBROT_45_SEAHORSE_OTHER_01_MAGNIFY_51_2024_04_01_H

  constexpr char MANDELBROT_FILENAME_STRING[]       = "MANDELBROT_45_SEAHORSE_OTHER_01_magnify51";

  constexpr int  MANDELBROT_CALCULATION_DIGITS10    =     82;
  constexpr int  MANDELBROT_CALCULATION_PIXELS_1D   =   2048;
  constexpr int  MANDELBROT_CALCULATION_ITERATIONS  =  30000;

  //constexpr char MANDELBROT_POINT_DX_HALF[]         = "1.0E-50";
  constexpr char MANDELBROT_POINT_DX_HALF[]         = "1.0E-47";
  constexpr char MANDELBROT_POINT_CENTER_X[]        = "-0.74560512236826499552076952275308636951071644977750550";
  constexpr char MANDELBROT_POINT_CENTER_Y[]        = "+0.11285949542725284995353757239552008929782635707298645";

  #include <mandelbrot/cfg/mandelbrot_cfg.h>

#endif // MANDELBROT_CFG_MANDELBROT_45_SEAHORSE_OTHER_01_MAGNIFY_51_2024_04_01_H
