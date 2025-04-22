///////////////////////////////////////////////////////////////////////////////
//      Copyright Christopher Kormanyos 2025.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef MANDELBROT_CFG_MANDELBROT_46_SEAHORSE_AREA_02_2025_04_22_H
  #define MANDELBROT_CFG_MANDELBROT_46_SEAHORSE_AREA_02_2025_04_22_H

  #if (!defined(_MSC_VER) && defined(__cplusplus) && (__cplusplus >= 201703L))
  namespace ckormanyos::mandelbrot::config {
  #else
  namespace ckormanyos { namespace mandelbrot { namespace config { // NOLINT(modernize-concat-nested-namespaces)
  #endif

  constexpr char MANDELBROT_FILENAME_STRING[]       = "MANDELBROT_46_SEAHORSE_AREA_02";

  constexpr int  MANDELBROT_COORD_PNT_DIGITS10      =     106;
  constexpr int  MANDELBROT_ITERATION_DIGITS10      =      24;
  constexpr int  MANDELBROT_CALCULATION_PIXELS_X    =    2048;
  constexpr int  MANDELBROT_CALCULATION_PIXELS_Y    =    2048;
  constexpr int  MANDELBROT_CALCULATION_ITERATIONS  =   26000;

  constexpr char MANDELBROT_POINT_DX_HALF[]         = "1.6E-83";
  constexpr char MANDELBROT_POINT_DY_HALF[]         = "1.6E-83";
  constexpr char MANDELBROT_POINT_CENTER_X[]        = "-0.643023330252352437377547424649074672836404177640713265072533519741280502281278990192295124905079271484375";
  constexpr char MANDELBROT_POINT_CENTER_Y[]        = "+0.459082803486384600700518845141947770114149328702324248013617976777208724480460870096490613639362728515625";

  template<typename CoordPntNumericType, typename IterateNumericType>
  using my_mandelbrot_generator_type = ::ckormanyos::mandelbrot::mandelbrot_generator_perturbative<CoordPntNumericType, IterateNumericType>;

  #if (!defined(_MSC_VER) && defined(__cplusplus) && (__cplusplus >= 201703L))
  } // namespace ckormanyos::mandelbrot::config
  #else
  } // namespace config
  } // namespace mandelbrot
  } // namespace ckormanyos
  #endif

#endif // MANDELBROT_CFG_MANDELBROT_46_SEAHORSE_AREA_02_2025_04_22_H
