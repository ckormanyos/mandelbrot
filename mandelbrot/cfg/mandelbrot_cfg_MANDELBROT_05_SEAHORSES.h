///////////////////////////////////////////////////////////////////////////////
//      Copyright Christopher Kormanyos 2022.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef MANDELBROT_CFG_MANDELBROT_05_SEAHORSES_2022_02_24_H
  #define MANDELBROT_CFG_MANDELBROT_05_SEAHORSES_2022_02_24_H

  #if defined(__clang__)
    #if defined __has_feature && (__has_feature(thread_sanitizer) || __has_feature(address_sanitizer))
    #define MANDELBROT_TEST_OPTION_REDUCE_TEST_DEPTH
    #endif
  #elif defined(__GNUC__)
    #if defined(__SANITIZE_THREAD__) || defined(__SANITIZE_ADDRESS__)
    #define MANDELBROT_TEST_OPTION_REDUCE_TEST_DEPTH
    #endif
  #endif

  // This is a swirly seahorse image.

  #define MANDELBROT_FILENAME_STRING            "MANDELBROT_05_SEAHORSES"

  #define MANDELBROT_CALCULATION_DIGITS10       37
  #if !defined(MANDELBROT_TEST_OPTION_REDUCE_TEST_DEPTH)
  #define MANDELBROT_CALCULATION_PIXELS_1D      2048UL
  #else
  #define MANDELBROT_CALCULATION_PIXELS_1D       512UL
  #endif
  #define MANDELBROT_CALCULATION_ITERATIONS     2000UL

  #define MANDELBROT_POINT_DX_HALF              "1.76E-12"
  #define MANDELBROT_POINT_CENTER_X             "-0.7453983606667815"
  #define MANDELBROT_POINT_CENTER_Y             "0.1125046349959942"

  #include <mandelbrot/cfg/mandelbrot_cfg.h>

#endif // MANDELBROT_CFG_MANDELBROT_05_SEAHORSES_2022_02_24_H
