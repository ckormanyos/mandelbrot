///////////////////////////////////////////////////////////////////////////////
//      Copyright Christopher Kormanyos 2024.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef MANDELBROT_CFG_MANDELBROT_25_ZOOM_SEARCH_01_2024_04_07_H
  #define MANDELBROT_CFG_MANDELBROT_25_ZOOM_SEARCH_01_2024_04_07_H

  constexpr char MANDELBROT_FILENAME_STRING[]       = "MANDELBROT_25_ZOOM_SEARCH_01";

  constexpr int  MANDELBROT_COORD_PNT_DIGITS10      =      48;
  constexpr int  MANDELBROT_ITERATION_DIGITS10      =      48;
  constexpr int  MANDELBROT_CALCULATION_PIXELS_X    =    2048;
  constexpr int  MANDELBROT_CALCULATION_PIXELS_Y    =    2048;
  constexpr int  MANDELBROT_CALCULATION_ITERATIONS  =  140000;

  // This was a fun point. It ends up hitting a Mandelbrot
  // figure at around order 25 (I'm not sure if it was a
  // Mandelbrot figure or if I just did not iterate deeply
  // enough). Anyway, for some reason, this point needs quite
  // a high iteration count for a relatively low digit count.

  // For the image, I walked this point back to Magnification
  // order 10^21 where a nice dipole-like structure is observed.
  // In the dipole areas it looks like little animals are meandering
  // about the inner circumferences of the enclosing ovals.

  constexpr char MANDELBROT_POINT_DX_HALF[]         = "5.8E-21";
  constexpr char MANDELBROT_POINT_DY_HALF[]         = "5.8E-21";
  constexpr char MANDELBROT_POINT_CENTER_X[]        = "-0.1528532287297766170184556480";
  constexpr char MANDELBROT_POINT_CENTER_Y[]        = "-1.0396895160836967088522828690";

  #define MANDELBROT_GENERATOR_TYPE mandelbrot_generator_trivial // NOLINT(cppcoreguidelines-macro-usage)

  #include <mandelbrot/cfg/mandelbrot_cfg.h>

#endif // MANDELBROT_CFG_MANDELBROT_25_ZOOM_SEARCH_01_2024_04_07_H
