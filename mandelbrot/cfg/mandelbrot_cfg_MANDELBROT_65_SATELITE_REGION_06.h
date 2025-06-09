///////////////////////////////////////////////////////////////////////////////
//      Copyright Christopher Kormanyos 2025.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef MANDELBROT_CFG_MANDELBROT_65_SATELITE_REGION_06_2025_06_09_H
  #define MANDELBROT_CFG_MANDELBROT_65_SATELITE_REGION_06_2025_06_09_H

  #if (!defined(_MSC_VER) && defined(__cplusplus) && (__cplusplus >= 201703L))
  namespace ckormanyos::mandelbrot::config {
  #else
  namespace ckormanyos { namespace mandelbrot { namespace config { // NOLINT(modernize-concat-nested-namespaces)
  #endif

  constexpr char MANDELBROT_FILENAME_STRING[]       = "MANDELBROT_65_SATELITE_REGION_06";

  constexpr int  MANDELBROT_COORD_PNT_DIGITS10      =     114;
  constexpr int  MANDELBROT_ITERATION_DIGITS10      =      28;
  constexpr int  MANDELBROT_CALCULATION_PIXELS_X    =    2048;
  constexpr int  MANDELBROT_CALCULATION_PIXELS_Y    =    2048;
  constexpr int  MANDELBROT_CALCULATION_ITERATIONS  =    8000;

  constexpr char MANDELBROT_POINT_DX_HALF[]         = "1.6E-86";
  constexpr char MANDELBROT_POINT_DY_HALF[]         = "1.6E-86";
  constexpr char MANDELBROT_POINT_CENTER_X[]        = "-1.91710624582008166413637767462377377136035732211519892053715977968643588923928406914423337960498046875";
  constexpr char MANDELBROT_POINT_CENTER_Y[]        = "-0.00080239511275102961678084558713700781375737773447051675741221038731668157885508873626070776447265625";

  template<typename CoordPntNumericType, typename IterateNumericType>
  using my_mandelbrot_generator_type = ::ckormanyos::mandelbrot::mandelbrot_generator_perturbative<CoordPntNumericType, IterateNumericType>;

  #if (!defined(_MSC_VER) && defined(__cplusplus) && (__cplusplus >= 201703L))
  } // namespace ckormanyos::mandelbrot::config
  #else
  } // namespace config
  } // namespace mandelbrot
  } // namespace ckormanyos
  #endif

#endif // MANDELBROT_CFG_MANDELBROT_65_SATELITE_REGION_06_2025_06_09_H
