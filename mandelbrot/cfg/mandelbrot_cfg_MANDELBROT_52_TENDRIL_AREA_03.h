///////////////////////////////////////////////////////////////////////////////
//      Copyright Christopher Kormanyos 2025.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef MANDELBROT_CFG_MANDELBROT_52_TENDRIL_AREA_03_2025_04_20_H
  #define MANDELBROT_CFG_MANDELBROT_52_TENDRIL_AREA_03_2025_04_20_H

  #if (!defined(_MSC_VER) && defined(__cplusplus) && (__cplusplus >= 201703L))
  namespace ckormanyos::mandelbrot::config {
  #else
  namespace ckormanyos { namespace mandelbrot { namespace config { // NOLINT(modernize-concat-nested-namespaces)
  #endif

  constexpr char MANDELBROT_FILENAME_STRING[]       = "MANDELBROT_52_TENDRIL_AREA_03";

  constexpr int  MANDELBROT_COORD_PNT_DIGITS10      =      42;
  constexpr int  MANDELBROT_ITERATION_DIGITS10      =      42;
  constexpr int  MANDELBROT_CALCULATION_PIXELS_X    =    2048;
  constexpr int  MANDELBROT_CALCULATION_PIXELS_Y    =    2048;
  constexpr int  MANDELBROT_CALCULATION_ITERATIONS  =    8000;

  // This iteration runs into a stretched Mandelbrot-like
  // figure at a magnification of approximately 10^30.

  // The digit count is relatively low for this particular iteration.
  // The corresponding total time to generate the full 2048*2048 pixel
  // image was comparatively short, at aroud 2 minutes. This iteration
  // image is interesting because it has so many swirls and zero points
  // readily visible with curly tails. It also features a stunning
  // central piece.

  constexpr char MANDELBROT_POINT_DX_HALF[]         = "1.25E-18";
  constexpr char MANDELBROT_POINT_DY_HALF[]         = "1.25E-18";
  constexpr char MANDELBROT_POINT_CENTER_X[]        = "-1.369671024619463911639201171875";
  constexpr char MANDELBROT_POINT_CENTER_Y[]        = "+0.007632976578238272083431640625";

  template<typename CoordPntNumericType, typename IterateNumericType>
  using my_mandelbrot_generator_type = ::ckormanyos::mandelbrot::mandelbrot_generator_trivial<CoordPntNumericType, IterateNumericType>;

  #if (!defined(_MSC_VER) && defined(__cplusplus) && (__cplusplus >= 201703L))
  } // namespace ckormanyos::mandelbrot::config
  #else
  } // namespace config
  } // namespace mandelbrot
  } // namespace ckormanyos
  #endif

#endif // MANDELBROT_CFG_MANDELBROT_52_TENDRIL_AREA_03_2025_04_20_H
