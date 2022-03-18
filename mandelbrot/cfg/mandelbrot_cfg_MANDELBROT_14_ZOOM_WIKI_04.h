///////////////////////////////////////////////////////////////////////////////
//      Copyright Christopher Kormanyos 2022.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef MANDELBROT_CFG_MANDELBROT_14_ZOOM_WIKI_04_2022_03_17_H
  #define MANDELBROT_CFG_MANDELBROT_14_ZOOM_WIKI_04_2022_03_17_H

  // This is a medium zoom image from the zoom coordinates of:
  // http://en.wikipedia.org/wiki/File:Mandelbrot_sequence_new.gif
  // Note: Use 55 or more decimal digits for this iteration.

  #define MANDELBROT_FILENAME_STRING            "MANDELBROT_14_ZOOM_WIKI_04"

  #define MANDELBROT_CALCULATION_DIGITS10       55
  #define MANDELBROT_CALCULATION_PIXELS_1D      2048UL
  #define MANDELBROT_CALCULATION_ITERATIONS     40000UL

  #define MANDELBROT_POINT_DX_HALF              "1.45E-30"
  #define MANDELBROT_POINT_CENTER_X             "-0.743643887037158704752191506114774"
  #define MANDELBROT_POINT_CENTER_Y             "0.131825904205311970493132056385139"

  #include <mandelbrot/cfg/mandelbrot_cfg.h>

#endif // MANDELBROT_CFG_MANDELBROT_14_ZOOM_WIKI_04_2022_03_17_H
