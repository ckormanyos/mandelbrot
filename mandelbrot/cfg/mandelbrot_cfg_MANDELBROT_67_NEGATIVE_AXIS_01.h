///////////////////////////////////////////////////////////////////////////////
//      Copyright Christopher Kormanyos 2025.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef MANDELBROT_CFG_MANDELBROT_67_NEGATIVE_AXIS_01_2025_04_21_H
  #define MANDELBROT_CFG_MANDELBROT_67_NEGATIVE_AXIS_01_2025_04_21_H

  #if (!defined(_MSC_VER) && defined(__cplusplus) && (__cplusplus >= 201703L))
  namespace ckormanyos::mandelbrot::config {
  #else
  namespace ckormanyos { namespace mandelbrot { namespace config { // NOLINT(modernize-concat-nested-namespaces)
  #endif

  // This is a specialized configuration file intended to be used
  // for simply trying out deep dives, such as those found by the
  // MandelbrotDiscovery program or found by other methods.

  constexpr char MANDELBROT_FILENAME_STRING[]       = "MANDELBROT_67_NEGATIVE_AXIS_01";

  constexpr int  MANDELBROT_COORD_PNT_DIGITS10      =     136;
  constexpr int  MANDELBROT_ITERATION_DIGITS10      =      24;
  constexpr int  MANDELBROT_CALCULATION_PIXELS_X    =    2048;
  constexpr int  MANDELBROT_CALCULATION_PIXELS_Y    =    2048;
  constexpr int  MANDELBROT_CALCULATION_ITERATIONS  =   12000;

  constexpr char MANDELBROT_POINT_DX_HALF[]         = "1.5E-108";
  constexpr char MANDELBROT_POINT_DY_HALF[]         = "1.5E-108";
  constexpr char MANDELBROT_POINT_CENTER_X[]        = "-1.9994030654508192977322313018607292329333353559332337801250054499901759339401480181983496052224784098917532905442767086063474012069327544921875";
  constexpr char MANDELBROT_POINT_CENTER_Y[]        = "+0.0000005395371128478017098743791365673101704811290227499761757719055417531297887907431186996536532440686941428493488021292413637692047931640625";

  template<typename CoordPntNumericType, typename IterateNumericType>
  using my_mandelbrot_generator_type = ::ckormanyos::mandelbrot::mandelbrot_generator_perturbative<CoordPntNumericType, IterateNumericType>;

  #if (!defined(_MSC_VER) && defined(__cplusplus) && (__cplusplus >= 201703L))
  } // namespace ckormanyos::mandelbrot::config
  #else
  } // namespace config
  } // namespace mandelbrot
  } // namespace ckormanyos
  #endif

#endif // MANDELBROT_CFG_MANDELBROT_67_NEGATIVE_AXIS_01_2025_04_21_H
