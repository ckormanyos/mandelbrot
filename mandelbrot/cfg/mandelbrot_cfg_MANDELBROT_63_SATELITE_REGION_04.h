///////////////////////////////////////////////////////////////////////////////
//      Copyright Christopher Kormanyos 2022 - 2025.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef MANDELBROT_CFG_MANDELBROT_63_SATELITE_REGION_04_2024_09_30_H
  #define MANDELBROT_CFG_MANDELBROT_63_SATELITE_REGION_04_2024_09_30_H

  #if (!defined(_MSC_VER) && defined(__cplusplus) && (__cplusplus >= 201703L))
  namespace ckormanyos::mandelbrot::config {
  #else
  namespace ckormanyos { namespace mandelbrot { namespace config { // NOLINT(modernize-concat-nested-namespaces)
  #endif

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

  template<typename CoordPntNumericType, typename IterateNumericType>
  using my_mandelbrot_generator_type = ::ckormanyos::mandelbrot::mandelbrot_generator_perturbative<CoordPntNumericType, IterateNumericType>;

  #if (!defined(_MSC_VER) && defined(__cplusplus) && (__cplusplus >= 201703L))
  } // namespace ckormanyos::mandelbrot::config
  #else
  } // namespace config
  } // namespace mandelbrot
  } // namespace ckormanyos
  #endif

#endif // MANDELBROT_CFG_MANDELBROT_63_SATELITE_REGION_04_2024_09_30_H
