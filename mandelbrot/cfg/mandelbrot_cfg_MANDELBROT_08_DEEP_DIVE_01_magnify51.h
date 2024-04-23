///////////////////////////////////////////////////////////////////////////////
//      Copyright Christopher Kormanyos 2022 - 2024.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef MANDELBROT_CFG_MANDELBROT_08_DEEP_DIVE_01_MAGNIFY_51_2022_03_14_H
  #define MANDELBROT_CFG_MANDELBROT_08_DEEP_DIVE_01_MAGNIFY_51_2022_03_14_H

  // This is a deep zoom image.
  // Note: Use 143 or more decimal digits for this iteration.

  constexpr char MANDELBROT_FILENAME_STRING[]       = "MANDELBROT_08_DEEP_DIVE_01_magnify51";

  constexpr int  MANDELBROT_SETUP_DIGITS10          =      76;
  constexpr int  MANDELBROT_CALCULATION_DIGITS10    =      20;
  constexpr int  MANDELBROT_CALCULATION_PIXELS_X    =    2048;
  constexpr int  MANDELBROT_CALCULATION_PIXELS_Y    =    2048;
  constexpr int  MANDELBROT_CALCULATION_ITERATIONS  =    2000;

  constexpr char MANDELBROT_POINT_DX_HALF[]         = "1.4E-51";
  constexpr char MANDELBROT_POINT_DY_HALF[]         = "1.4E-51";
  constexpr char MANDELBROT_POINT_CENTER_X[]        = "-1.999999999138270118758274762908694988316809136636820959506";
  constexpr char MANDELBROT_POINT_CENTER_Y[]        = "+0.000000000000013148954435076375751362475668065050021517005";

  #include <mandelbrot/cfg/mandelbrot_cfg.h>

#endif // MANDELBROT_CFG_MANDELBROT_08_DEEP_DIVE_01_MAGNIFY_51_2022_03_14_H
