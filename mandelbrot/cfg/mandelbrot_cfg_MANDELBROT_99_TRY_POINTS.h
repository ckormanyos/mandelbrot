///////////////////////////////////////////////////////////////////////////////
//      Copyright Christopher Kormanyos 2022 - 2024.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef MANDELBROT_CFG_MANDELBROT_99_TRY_POINTS_2024_04_30_H
  #define MANDELBROT_CFG_MANDELBROT_99_TRY_POINTS_2024_04_30_H

  // This is a specialized configuration file intended to be used for simply
  // trying out deep dives, such as those found by MandelbrotDiscovery
  // or found by other methods.

  constexpr char MANDELBROT_FILENAME_STRING[]       = "MANDELBROT_99_TRY_POINTS";

  constexpr int  MANDELBROT_COORD_PNT_DIGITS10      =      58;
  constexpr int  MANDELBROT_ITERATION_DIGITS10      =      58;
  constexpr int  MANDELBROT_CALCULATION_PIXELS_X    =    2048;
  constexpr int  MANDELBROT_CALCULATION_PIXELS_Y    =    2048;
  constexpr int  MANDELBROT_CALCULATION_ITERATIONS  =    8000;

  constexpr char MANDELBROT_POINT_DX_HALF[]         = "1.15E-31";
  constexpr char MANDELBROT_POINT_DY_HALF[]         = "1.15E-31";
  constexpr char MANDELBROT_POINT_CENTER_X[]        = "-1.9771841957832528683253271547935727033203125";
  constexpr char MANDELBROT_POINT_CENTER_Y[]        = "+0.0003701587934278647349697471824343197265625";

  #if 0
  constexpr int  MANDELBROT_COORD_PNT_DIGITS10      =     132;
  constexpr int  MANDELBROT_ITERATION_DIGITS10      =     132;
  constexpr int  MANDELBROT_CALCULATION_PIXELS_X    =     512;
  constexpr int  MANDELBROT_CALCULATION_PIXELS_Y    =     512;
  constexpr int  MANDELBROT_CALCULATION_ITERATIONS  =   12000;

  constexpr char MANDELBROT_POINT_DX_HALF[]         = "1.35E-92";
  constexpr char MANDELBROT_POINT_DY_HALF[]         = "1.35E-92";
  constexpr char MANDELBROT_POINT_CENTER_X[]        = "-1.711024498065425783442616962887150075536644429276936212772197371643420276616709106166700677273062220703125";
  constexpr char MANDELBROT_POINT_CENTER_Y[]        = "+0.003998130357843762350089770108611803382417083111382471700501416344256825824943651749566227455277501953125";
  #endif

  #define MANDELBROT_GENERATOR_TYPE mandelbrot_generator_trivial // NOLINT(cppcoreguidelines-macro-usage)

  #include <mandelbrot/cfg/mandelbrot_cfg.h>

#endif // MANDELBROT_CFG_MANDELBROT_99_TRY_POINTS_2024_04_30_H
