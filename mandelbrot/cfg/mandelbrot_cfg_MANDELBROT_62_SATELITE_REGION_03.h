///////////////////////////////////////////////////////////////////////////////
//      Copyright Christopher Kormanyos 2022 - 2025.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef MANDELBROT_CFG_MANDELBROT_62_SATELITE_REGION_03_2024_08_29_H
  #define MANDELBROT_CFG_MANDELBROT_62_SATELITE_REGION_03_2024_08_29_H

  #if (!defined(_MSC_VER) && defined(__cplusplus) && (__cplusplus >= 201703L))
  namespace ckormanyos::mandelbrot::config {
  #else
  namespace ckormanyos { namespace mandelbrot { namespace config { // NOLINT(modernize-concat-nested-namespaces)
  #endif

  constexpr char MANDELBROT_FILENAME_STRING[]       = "MANDELBROT_62_SATELITE_REGION_03";

  constexpr int  MANDELBROT_COORD_PNT_DIGITS10      =     114;
  constexpr int  MANDELBROT_ITERATION_DIGITS10      =      24;
  constexpr int  MANDELBROT_CALCULATION_PIXELS_X    =    2048;
  constexpr int  MANDELBROT_CALCULATION_PIXELS_Y    =    2048;
  constexpr int  MANDELBROT_CALCULATION_ITERATIONS  =   12000;

  constexpr char MANDELBROT_POINT_DX_HALF[]         = "1.45E-89";
  constexpr char MANDELBROT_POINT_DY_HALF[]         = "1.45E-89";
  constexpr char MANDELBROT_POINT_CENTER_X[]        = "-1.711024498065425783442616962887150075536644429276936212772197371643420276616709106166700677273062220703125";
  constexpr char MANDELBROT_POINT_CENTER_Y[]        = "+0.003998130357843762350089770108611803382417083111382471700501416344256825824943651749566227455277501953125";

  template<typename CoordPntNumericType, typename IterateNumericType>
  using my_mandelbrot_generator_type = ::ckormanyos::mandelbrot::mandelbrot_generator_perturbative<CoordPntNumericType, IterateNumericType>;

  #if (!defined(_MSC_VER) && defined(__cplusplus) && (__cplusplus >= 201703L))
  } // namespace ckormanyos::mandelbrot::config
  #else
  } // namespace config
  } // namespace mandelbrot
  } // namespace ckormanyos
  #endif

#endif // MANDELBROT_CFG_MANDELBROT_62_SATELITE_REGION_03_2024_08_29_H
