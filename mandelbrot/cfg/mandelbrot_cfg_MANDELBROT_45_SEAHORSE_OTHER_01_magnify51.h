///////////////////////////////////////////////////////////////////////////////
//      Copyright Christopher Kormanyos 2024.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef MANDELBROT_CFG_MANDELBROT_45_SEAHORSE_OTHER_01_MAGNIFY_51_2024_04_01_H
  #define MANDELBROT_CFG_MANDELBROT_45_SEAHORSE_OTHER_01_MAGNIFY_51_2024_04_01_H

  constexpr char MANDELBROT_FILENAME_STRING[]       = "MANDELBROT_45_SEAHORSE_OTHER_01_magnify51";

  constexpr int  MANDELBROT_COORD_PNT_DIGITS10      =     76;
  constexpr int  MANDELBROT_ITERATION_DIGITS10      =     76;
  constexpr int  MANDELBROT_CALCULATION_PIXELS_X    =   2048;
  constexpr int  MANDELBROT_CALCULATION_PIXELS_Y    =   2048;
  constexpr int  MANDELBROT_CALCULATION_ITERATIONS  =  30000;

  constexpr char MANDELBROT_POINT_DX_HALF[]         = "1.4E-51";
  constexpr char MANDELBROT_POINT_DY_HALF[]         = "1.4E-51";
  constexpr char MANDELBROT_POINT_CENTER_X[]        = "-0.745605122368264995520769522753086369510716449777505626833";
  constexpr char MANDELBROT_POINT_CENTER_Y[]        = "+0.112859495427252849953537572395520089297826357072986239717";

  #define MANDELBROT_GENERATOR_TYPE mandelbrot_generator_trivial // NOLINT(cppcoreguidelines-macro-usage)

  #include <mandelbrot/cfg/mandelbrot_cfg.h>

#endif // MANDELBROT_CFG_MANDELBROT_45_SEAHORSE_OTHER_01_MAGNIFY_51_2024_04_01_H
