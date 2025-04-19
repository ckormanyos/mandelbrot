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

  constexpr char MANDELBROT_FILENAME_STRING[]       = "MANDELBROT_64_SATELITE_REGION_05";

  constexpr int  MANDELBROT_COORD_PNT_DIGITS10      =     118;
  constexpr int  MANDELBROT_ITERATION_DIGITS10      =      24;
  constexpr int  MANDELBROT_CALCULATION_PIXELS_X    =    2048;
  constexpr int  MANDELBROT_CALCULATION_PIXELS_Y    =    2048;
  constexpr int  MANDELBROT_CALCULATION_ITERATIONS  =   24000;

  constexpr char MANDELBROT_POINT_DX_HALF[]         = "1.15E-90";
  constexpr char MANDELBROT_POINT_DY_HALF[]         = "1.15E-90";
  constexpr char MANDELBROT_POINT_CENTER_X[]        = "-1.59406734293114870943885622320332262147623226884990993559394808497475790096244520327632846746191698212890625";
  constexpr char MANDELBROT_POINT_CENTER_Y[]        = "+0.00036409746549833742116296981925342572703527339093141779122949818629407764477376656515696942085305587890625";

  template<typename CoordPntNumericType, typename IterateNumericType>
  using my_mandelbrot_generator_type = ::ckormanyos::mandelbrot::mandelbrot_generator_perturbative<CoordPntNumericType, IterateNumericType>;

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
