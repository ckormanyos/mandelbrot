///////////////////////////////////////////////////////////////////////////////
//      Copyright Christopher Kormanyos 2022 - 2024.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef MANDELBROT_CFG_MANDELBROT_20_ZOOM_VERY_DEEP_00_MAGNIFY_51_2022_02_24_H
  #define MANDELBROT_CFG_MANDELBROT_20_ZOOM_VERY_DEEP_00_MAGNIFY_51_2022_02_24_H

  constexpr char MANDELBROT_FILENAME_STRING[]       = "MANDELBROT_20_ZOOM_VERY_DEEP_00_magnify51";

  constexpr int  MANDELBROT_COORD_PNT_DIGITS10      =      76;
  constexpr int  MANDELBROT_ITERATION_DIGITS10      =      76;
  constexpr int  MANDELBROT_CALCULATION_PIXELS_X    =    2048;
  constexpr int  MANDELBROT_CALCULATION_PIXELS_Y    =    2048;
  constexpr int  MANDELBROT_CALCULATION_ITERATIONS  =   30000;

  constexpr char MANDELBROT_POINT_DX_HALF[]         = "1.4E-51";
  constexpr char MANDELBROT_POINT_DY_HALF[]         = "1.4E-51";
  constexpr char MANDELBROT_POINT_CENTER_X[]        = "+0.360240443437614363236125244449545308482607807958585750488";
  constexpr char MANDELBROT_POINT_CENTER_Y[]        = "-0.641313061064803174860375015179302066579494952282305259556";

  #define MANDELBROT_GENERATOR_TYPE mandelbrot_generator_trivial // NOLINT(cppcoreguidelines-macro-usage)

  #include <mandelbrot/cfg/mandelbrot_cfg.h>

#endif // MANDELBROT_CFG_MANDELBROT_20_ZOOM_VERY_DEEP_00_MAGNIFY_51_2022_02_24_H
