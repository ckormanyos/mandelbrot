///////////////////////////////////////////////////////////////////////////////
// Copyright Christopher Kormanyos 2024.
// Distributed under the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt
// or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef MANDELBROT_CFG_MANDELBROT_61_SATELITE_REGION_02_2024_08_29_H
  #define MANDELBROT_CFG_MANDELBROT_61_SATELITE_REGION_02_2024_08_29_H

  constexpr char MANDELBROT_FILENAME_STRING[]       = "MANDELBROT_61_SATELITE_REGION_02";

  constexpr int  MANDELBROT_COORD_PNT_DIGITS10      =      58;
  constexpr int  MANDELBROT_ITERATION_DIGITS10      =      58;
  constexpr int  MANDELBROT_CALCULATION_PIXELS_X    =    2048;
  constexpr int  MANDELBROT_CALCULATION_PIXELS_Y    =    2048;
  constexpr int  MANDELBROT_CALCULATION_ITERATIONS  =    8000;

  constexpr char MANDELBROT_POINT_DX_HALF[]         = "1.15E-31";
  constexpr char MANDELBROT_POINT_DY_HALF[]         = "1.15E-31";
  constexpr char MANDELBROT_POINT_CENTER_X[]        = "-1.9771841957832528683253271547935727033203125";
  constexpr char MANDELBROT_POINT_CENTER_Y[]        = "+0.0003701587934278647349697471824343197265625";

  #define MANDELBROT_GENERATOR_TYPE mandelbrot_generator_trivial // NOLINT(cppcoreguidelines-macro-usage)

  #include <mandelbrot/cfg/mandelbrot_cfg.h>

#endif // MANDELBROT_CFG_MANDELBROT_61_SATELITE_REGION_02_2024_08_29_H
