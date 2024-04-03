///////////////////////////////////////////////////////////////////////////////
//      Copyright Christopher Kormanyos 2024.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef MANDELBROT_CFG_MANDELBROT_50_TENDRIL_AREA_01_2024_04_02_H
  #define MANDELBROT_CFG_MANDELBROT_50_TENDRIL_AREA_01_2024_04_02_H

  constexpr char MANDELBROT_FILENAME_STRING[]       = "MANDELBROT_50_TENDRIL_AREA_01";

  constexpr int  MANDELBROT_CALCULATION_DIGITS10    =     48;
  constexpr int  MANDELBROT_CALCULATION_PIXELS_1D   =   2048;
  constexpr int  MANDELBROT_CALCULATION_ITERATIONS  =  30000;

  constexpr char MANDELBROT_POINT_DX_HALF[]         = "1.0E-25";
  //constexpr char MANDELBROT_POINT_DX_HALF[]         = "1.0E-28";

  constexpr char MANDELBROT_POINT_CENTER_X[]        = "-1.2501996588423823189520585598095";
  constexpr char MANDELBROT_POINT_CENTER_Y[]        = "+0.0132428097146356623937316874660";

  #include <mandelbrot/cfg/mandelbrot_cfg.h>

#endif // MANDELBROT_CFG_MANDELBROT_50_TENDRIL_AREA_01_2024_04_02_H
