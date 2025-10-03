///////////////////////////////////////////////////////////////////////////////
//      Copyright Christopher Kormanyos 2025.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef MANDELBROT_CFG_MANDELBROT_66_SATELITE_REGION_07_2025_10_02_H
  #define MANDELBROT_CFG_MANDELBROT_66_SATELITE_REGION_07_2025_10_02_H

  #if (defined(MANDELBROT_CXX_VERSION) && (MANDELBROT_CXX_VERSION >= 201703L))
  namespace ckormanyos::mandelbrot::config {
  #else
  namespace ckormanyos { namespace mandelbrot { namespace config { // NOLINT(modernize-concat-nested-namespaces)
  #endif

  constexpr char MANDELBROT_FILENAME_STRING[]       = "MANDELBROT_66_SATELITE_REGION_07";

  constexpr int  MANDELBROT_COORD_PNT_DIGITS10      =     157;
  constexpr int  MANDELBROT_ITERATION_DIGITS10      =      28;
  constexpr int  MANDELBROT_CALCULATION_PIXELS_X    =    2048;
  constexpr int  MANDELBROT_CALCULATION_PIXELS_Y    =    2048;
  constexpr int  MANDELBROT_CALCULATION_ITERATIONS  =    8000;

  constexpr char MANDELBROT_POINT_DX_HALF[]         = "1.65E-133";
  constexpr char MANDELBROT_POINT_DY_HALF[]         = "1.65E-133";
  constexpr char MANDELBROT_POINT_CENTER_X[]        = "-1.8616232544883360529602450898015071725914787445582037123672213750149210035031846489116392559493757840073589454444715781914346543843561264826973586764795059068359375";
  constexpr char MANDELBROT_POINT_CENTER_Y[]        = "-0.0107182541995913923944394281023498707764951066261331142836986012299852442789108307988267795631771400988019431621979295574127566901526006435306843465419623068359375";

  template<typename CoordPntNumericType, typename IterateNumericType>
  using my_mandelbrot_generator_type = ::ckormanyos::mandelbrot::mandelbrot_generator_perturbative<CoordPntNumericType, IterateNumericType>;

  #if (defined(MANDELBROT_CXX_VERSION) && (MANDELBROT_CXX_VERSION >= 201703L))
  } // namespace ckormanyos::mandelbrot::config
  #else
  } // namespace config
  } // namespace mandelbrot
  } // namespace ckormanyos
  #endif

#endif // MANDELBROT_CFG_MANDELBROT_66_SATELITE_REGION_07_2025_10_02_H
