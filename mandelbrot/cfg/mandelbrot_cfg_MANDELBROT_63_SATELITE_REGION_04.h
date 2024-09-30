///////////////////////////////////////////////////////////////////////////////
// Copyright Christopher Kormanyos 2024.
// Distributed under the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt
// or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef MANDELBROT_CFG_MANDELBROT_63_SATELITE_REGION_04_2024_09_30_H
  #define MANDELBROT_CFG_MANDELBROT_63_SATELITE_REGION_04_2024_09_30_H

  // This is a specialized configuration file intended to be used for simply
  // trying out deep dives, such as those found by MandelbrotDiscovery
  // or found by other methods.

  constexpr char MANDELBROT_FILENAME_STRING[]       = "MANDELBROT_63_SATELITE_REGION_04";

  constexpr int  MANDELBROT_COORD_PNT_DIGITS10      =     214;
  constexpr int  MANDELBROT_ITERATION_DIGITS10      =      24;
  constexpr int  MANDELBROT_CALCULATION_PIXELS_X    =    2048;
  constexpr int  MANDELBROT_CALCULATION_PIXELS_Y    =    2048;
  constexpr int  MANDELBROT_CALCULATION_ITERATIONS  =   14000;

  constexpr char MANDELBROT_POINT_DX_HALF[]         = "8.0E-190";
  constexpr char MANDELBROT_POINT_DY_HALF[]         = "8.0E-190";
  constexpr char MANDELBROT_POINT_CENTER_X[]        = "-1.8699746396068234286692870030368768342037915453642718845509028250103459986994857328215914371327608244573050112378162372813745137414275903616640983656639053254827407629999158221608411935399712125613169306975303341796875";
  constexpr char MANDELBROT_POINT_CENTER_Y[]        = "+0.0014397083058718932815517159691261764084009958345476625415401283362782412191970631987534414177842258005688394204420205338263522643408260217088410151729628883966663578850294616803557413620305357059671210545313455078125";

  #define MANDELBROT_GENERATOR_TYPE mandelbrot_generator_perturbative // NOLINT(cppcoreguidelines-macro-usage)

  #include <mandelbrot/cfg/mandelbrot_cfg.h>

#endif // MANDELBROT_CFG_MANDELBROT_63_SATELITE_REGION_04_2024_09_30_H
