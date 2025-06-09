///////////////////////////////////////////////////////////////////////////////
//      Copyright Christopher Kormanyos 2022 - 2025.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef MANDELBROT_CFG_2022_02_24_H // NOLINT(llvm-header-guard)
  #define MANDELBROT_CFG_2022_02_24_H

  // --------------------------------------------------------------------------
  // You can optionally define MANDELBROT_USE_CPP_DOUBLE_DOUBLE here or
  // on the command line in order to use the cpp_double_double class
  // when available. Do note, however, that the cpp_double_double number
  // type will only be used for decimal digit counts of 32 or lower.
  // This is automatically ensured by conditional logic checks in the code
  // (when this option is activated).

  //#if !defined(MANDELBROT_USE_CPP_DOUBLE_DOUBLE)
  //#define MANDELBROT_USE_CPP_DOUBLE_DOUBLE
  //#endif

  // --------------------------------------------------------------------------

  // You can optionally define MANDELBROT_USE_GMP_FLOAT here or
  // on the command line in order to use the gmp_float class
  // when available.

  //#if !defined(MANDELBROT_USE_GMP_FLOAT)
  //#define MANDELBROT_USE_GMP_FLOAT
  //#endif

  // --------------------------------------------------------------------------

  #if (!defined(MANDELBROT_USE_CPP_DEC_FLOAT) && !defined(MANDELBROT_USE_GMP_FLOAT))
  #define MANDELBROT_USE_CPP_DEC_FLOAT
  #endif

  #if (!defined(MANDELBROT_USE_CPP_DEC_FLOAT) && !defined(MANDELBROT_USE_GMP_FLOAT))
  #error "Error: Define one of MANDELBROT_USE_CPP_DEC_FLOAT or MANDELBROT_USE_GMP_FLOAT"
  #endif

  #if (defined(MANDELBROT_USE_CPP_DEC_FLOAT) && defined(MANDELBROT_USE_GMP_FLOAT))
  #error "Error: You can not define both MANDELBROT_USE_CPP_DEC_FLOAT or MANDELBROT_USE_GMP_FLOAT"
  #endif

  #if !defined(MANDELBROT_NODISCARD)
  #if defined(_MSC_VER) && !defined(__GNUC__)
  #define MANDELBROT_NODISCARD
  #else
  #if (defined(__cplusplus) && (__cplusplus >= 201703L))
  #define MANDELBROT_NODISCARD  [[nodiscard]] // NOLINT(cppcoreguidelines-macro-usage)
  #else
  #define MANDELBROT_NODISCARD
  #endif
  #endif
  #endif

  #include <mandelbrot/cfg/mandelbrot_cfg_forward.h>

  #if defined(MANDELBROT_USE_CPP_DEC_FLOAT)
  #include <boost/multiprecision/cpp_dec_float.hpp>
  #elif defined(MANDELBROT_USE_GMP_FLOAT)
  #include <boost/multiprecision/gmp.hpp>
  #endif

  #if defined(MANDELBROT_USE_CPP_DOUBLE_DOUBLE)
  #include <boost/multiprecision/cpp_double_fp.hpp>
  #endif

  //#include <mandelbrot/cfg/mandelbrot_cfg_MANDELBROT_01_FULL.h>
  //#include <mandelbrot/cfg/mandelbrot_cfg_MANDELBROT_03_TOP.h>
  //#include <mandelbrot/cfg/mandelbrot_cfg_MANDELBROT_04_SWIRL.h>
  #include <mandelbrot/cfg/mandelbrot_cfg_MANDELBROT_05_SEAHORSES.h>
  //#include <mandelbrot/cfg/mandelbrot_cfg_MANDELBROT_06_BRANCHES.h>
  //#include <mandelbrot/cfg/mandelbrot_cfg_MANDELBROT_07_SEAHORSE_VALLEY.h>
  //#include <mandelbrot/cfg/mandelbrot_cfg_MANDELBROT_08_DEEP_DIVE_01.h>
  //#include <mandelbrot/cfg/mandelbrot_cfg_MANDELBROT_08_DEEP_DIVE_01_magnify51.h>
  //#include <mandelbrot/cfg/mandelbrot_cfg_MANDELBROT_09_DEEP_DIVE_02.h>
  //#include <mandelbrot/cfg/mandelbrot_cfg_MANDELBROT_10_ZOOM_WIKI_00.h>
  //#include <mandelbrot/cfg/mandelbrot_cfg_MANDELBROT_10_ZOOM_WIKI_00_rect.h>
  //#include <mandelbrot/cfg/mandelbrot_cfg_MANDELBROT_11_ZOOM_WIKI_01.h>
  //#include <mandelbrot/cfg/mandelbrot_cfg_MANDELBROT_12_ZOOM_WIKI_02.h>
  //#include <mandelbrot/cfg/mandelbrot_cfg_MANDELBROT_13_ZOOM_WIKI_03.h>
  //#include <mandelbrot/cfg/mandelbrot_cfg_MANDELBROT_14_ZOOM_WIKI_04.h>
  //#include <mandelbrot/cfg/mandelbrot_cfg_MANDELBROT_20_ZOOM_VERY_DEEP_00.h>
  //#include <mandelbrot/cfg/mandelbrot_cfg_MANDELBROT_20_ZOOM_VERY_DEEP_00_magnify51.h>
  //#include <mandelbrot/cfg/mandelbrot_cfg_MANDELBROT_20_ZOOM_VERY_DEEP_612.h>
  //#include <mandelbrot/cfg/mandelbrot_cfg_MANDELBROT_25_ZOOM_SEARCH_00.h>
  //#include <mandelbrot/cfg/mandelbrot_cfg_MANDELBROT_25_ZOOM_SEARCH_01.h>
  //#include <mandelbrot/cfg/mandelbrot_cfg_MANDELBROT_30_ZOOM_ANOTHER_00.h>
  //#include <mandelbrot/cfg/mandelbrot_cfg_MANDELBROT_30_ZOOM_ANOTHER_00_magnify51.h>
  //#include <mandelbrot/cfg/mandelbrot_cfg_MANDELBROT_31_ZOOM_ANOTHER_01.h>
  //#include <mandelbrot/cfg/mandelbrot_cfg_MANDELBROT_32_ZOOM_ANOTHER_02.h>
  //#include <mandelbrot/cfg/mandelbrot_cfg_MANDELBROT_33_ZOOM_EVEN_MORE_03.h>
  //#include <mandelbrot/cfg/mandelbrot_cfg_MANDELBROT_40_SEAHORSE_DIVE_01.h>
  //#include <mandelbrot/cfg/mandelbrot_cfg_MANDELBROT_45_SEAHORSE_OTHER_01_magnify51.h>
  //#include <mandelbrot/cfg/mandelbrot_cfg_MANDELBROT_46_SEAHORSE_AREA_02.h>
  //#include <mandelbrot/cfg/mandelbrot_cfg_MANDELBROT_50_TENDRIL_AREA_01.h>
  //#include <mandelbrot/cfg/mandelbrot_cfg_MANDELBROT_51_TENDRIL_AREA_02.h>
  //#include <mandelbrot/cfg/mandelbrot_cfg_MANDELBROT_52_TENDRIL_AREA_03.h>
  //#include <mandelbrot/cfg/mandelbrot_cfg_MANDELBROT_53_TENDRIL_AREA_04.h>
  //#include <mandelbrot/cfg/mandelbrot_cfg_MANDELBROT_53_TENDRIL_AREA_04_prior.h>
  //#include <mandelbrot/cfg/mandelbrot_cfg_MANDELBROT_60_SATELITE_REGION_01.h>
  //#include <mandelbrot/cfg/mandelbrot_cfg_MANDELBROT_61_SATELITE_REGION_02.h>
  //#include <mandelbrot/cfg/mandelbrot_cfg_MANDELBROT_62_SATELITE_REGION_03.h>
  //#include <mandelbrot/cfg/mandelbrot_cfg_MANDELBROT_63_SATELITE_REGION_04.h>
  //#include <mandelbrot/cfg/mandelbrot_cfg_MANDELBROT_64_SATELITE_REGION_05.h>
  //#include <mandelbrot/cfg/mandelbrot_cfg_MANDELBROT_65_SATELITE_REGION_06.h>
  //#include <mandelbrot/cfg/mandelbrot_cfg_MANDELBROT_67_NEGATIVE_AXIS_01.h>
  //#include <mandelbrot/cfg/mandelbrot_cfg_MANDELBROT_70_DOUADY_RABBIT_01.h>
  //#include <mandelbrot/cfg/mandelbrot_cfg_MANDELBROT_72_DOUADY_RABBIT_03.h>
  //#include <mandelbrot/cfg/mandelbrot_cfg_MANDELBROT_80_SEARCH_HALO_01.h>
  //#include <mandelbrot/cfg/mandelbrot_cfg_MANDELBROT_90_ELEPHANT_VALLEY_01.h>
  //#include <mandelbrot/cfg/mandelbrot_cfg_MANDELBROT_91_ELEPHANT_VALLEY_02.h>
  //#include <mandelbrot/cfg/mandelbrot_cfg_MANDELBROT_XX_TRY_POINTS.h>

#endif // MANDELBROT_CFG_CONFIG_2022_02_24_H
