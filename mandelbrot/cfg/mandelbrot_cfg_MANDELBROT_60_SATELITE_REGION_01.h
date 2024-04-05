///////////////////////////////////////////////////////////////////////////////
//      Copyright Christopher Kormanyos 2024.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef MANDELBROT_CFG_MANDELBROT_60_SATELITE_REGION_01_2024_05_02_H
  #define MANDELBROT_CFG_MANDELBROT_60_SATELITE_REGION_01_2024_05_02_H

  constexpr char MANDELBROT_FILENAME_STRING[]       = "MANDELBROT_60_SATELITE_REGION_01";

  constexpr int  MANDELBROT_CALCULATION_DIGITS10    =     128;
  constexpr int  MANDELBROT_CALCULATION_PIXELS_1D   =     512;
  constexpr int  MANDELBROT_CALCULATION_ITERATIONS  =   40000;

  //constexpr char MANDELBROT_POINT_DX_HALF[]         = "1.1E-93";
  constexpr char MANDELBROT_POINT_DX_HALF[]         = "1.4E-91";

  constexpr char MANDELBROT_POINT_CENTER_X[]        = "-1.768383004964872269289001501904369831795935387249737499530591410673515130916173089923343510834080";
  constexpr char MANDELBROT_POINT_CENTER_Y[]        = "-0.003556475605158041908563559891422827086849758892921873014162330845720513141999768578085607152010";

  #include <mandelbrot/cfg/mandelbrot_cfg.h>

#endif // MANDELBROT_CFG_MANDELBROT_60_SATELITE_REGION_01_2024_05_02_H
