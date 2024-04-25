///////////////////////////////////////////////////////////////////////////////
//      Copyright Christopher Kormanyos 2024.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef MANDELBROT_CFG_MANDELBROT_50_TENDRIL_AREA_01_2024_04_02_H
  #define MANDELBROT_CFG_MANDELBROT_50_TENDRIL_AREA_01_2024_04_02_H

  constexpr char MANDELBROT_FILENAME_STRING[]       = "MANDELBROT_50_TENDRIL_AREA_01";

  constexpr int  MANDELBROT_COORD_PNT_DIGITS10          =      84;
  constexpr int  MANDELBROT_ITERATION_DIGITS10      =      20;
  constexpr int  MANDELBROT_CALCULATION_PIXELS_X    =    2048;
  constexpr int  MANDELBROT_CALCULATION_PIXELS_Y    =    2048;
  constexpr int  MANDELBROT_CALCULATION_ITERATIONS  =   20000;

  constexpr char MANDELBROT_POINT_DX_HALF[]         = "1.1E-57";
  constexpr char MANDELBROT_POINT_DY_HALF[]         = "1.1E-57";

  constexpr char MANDELBROT_POINT_CENTER_X[]        = "-1.25250830004782505863756256180595437771848402389262488689839351384765625";
  constexpr char MANDELBROT_POINT_CENTER_Y[]        = "-0.03469751802386917577721220226386151287449426134677692355346511193359375";

  #include <mandelbrot/cfg/mandelbrot_cfg.h>

#endif // MANDELBROT_CFG_MANDELBROT_50_TENDRIL_AREA_01_2024_04_02_H
