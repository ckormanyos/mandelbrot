///////////////////////////////////////////////////////////////////////////////
//      Copyright Christopher Kormanyos 2022 - 2025.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef MANDELBROT_CFG_MANDELBROT_CFG_05_SEAHORSES_H
  #define MANDELBROT_CFG_MANDELBROT_CFG_05_SEAHORSES_H

  #if defined(__clang__)
    #if defined __has_feature && (__has_feature(thread_sanitizer) || __has_feature(address_sanitizer))
    #if !defined(MANDELBROT_TEST_OPTION_REDUCE_TEST_DEPTH)
    #define MANDELBROT_TEST_OPTION_REDUCE_TEST_DEPTH
    #endif
    #endif
  #elif defined(__GNUC__)
    #if (defined(__SANITIZE_THREAD__) || defined(__SANITIZE_ADDRESS__) || defined(MANDELBROT_HAS_COVERAGE))
    #if !defined(MANDELBROT_TEST_OPTION_REDUCE_TEST_DEPTH)
    #define MANDELBROT_TEST_OPTION_REDUCE_TEST_DEPTH
    #endif
    #endif
  #endif

  #if defined(MANDELBROT_USE_PERTURBATIVE)
  #define MANDELBROT_TEST_OPTION_EXERCISE_PERTURBATIVE
  #endif

  #if (!defined(_MSC_VER) && defined(__cplusplus) && (__cplusplus >= 201703L))
  namespace ckormanyos::mandelbrot::config {
  #else
  namespace ckormanyos { namespace mandelbrot { namespace config { // NOLINT(modernize-concat-nested-namespaces)
  #endif

  // This is a swirly seahorse image.

  constexpr char MANDELBROT_FILENAME_STRING[]       = "MANDELBROT_05_SEAHORSES"; // NOLINT(cppcoreguidelines-avoid-c-arrays,hicpp-avoid-c-arrays,modernize-avoid-c-arrays)

  #if !defined(MANDELBROT_TEST_OPTION_EXERCISE_PERTURBATIVE)
  constexpr int  MANDELBROT_COORD_PNT_DIGITS10      =      32;
  #else
  constexpr int  MANDELBROT_COORD_PNT_DIGITS10      =      48;
  #endif
  constexpr int  MANDELBROT_ITERATION_DIGITS10      =      32;
  #if !defined(MANDELBROT_TEST_OPTION_REDUCE_TEST_DEPTH)
  constexpr int  MANDELBROT_CALCULATION_PIXELS_X    =    2048;
  constexpr int  MANDELBROT_CALCULATION_PIXELS_Y    =    2048;
  #else
  constexpr int  MANDELBROT_CALCULATION_PIXELS_X    =     256;
  constexpr int  MANDELBROT_CALCULATION_PIXELS_Y    =     256;
  #endif
  constexpr int  MANDELBROT_CALCULATION_ITERATIONS  =    2000;

  constexpr char MANDELBROT_POINT_DX_HALF[]         = "1.76E-12";             // NOLINT(cppcoreguidelines-avoid-c-arrays,hicpp-avoid-c-arrays,modernize-avoid-c-arrays)
  constexpr char MANDELBROT_POINT_DY_HALF[]         = "1.76E-12";             // NOLINT(cppcoreguidelines-avoid-c-arrays,hicpp-avoid-c-arrays,modernize-avoid-c-arrays)
  constexpr char MANDELBROT_POINT_CENTER_X[]        = "-0.7453983606667815";  // NOLINT(cppcoreguidelines-avoid-c-arrays,hicpp-avoid-c-arrays,modernize-avoid-c-arrays)
  constexpr char MANDELBROT_POINT_CENTER_Y[]        = "+0.1125046349959942";  // NOLINT(cppcoreguidelines-avoid-c-arrays,hicpp-avoid-c-arrays,modernize-avoid-c-arrays)

  #if !defined(MANDELBROT_TEST_OPTION_EXERCISE_PERTURBATIVE)
  template<typename CoordPntNumericType, typename IterateNumericType>
  using my_mandelbrot_generator_type = ::ckormanyos::mandelbrot::mandelbrot_generator_trivial<CoordPntNumericType, IterateNumericType>;
  #else
  template<typename CoordPntNumericType, typename IterateNumericType>
  using my_mandelbrot_generator_type = ::ckormanyos::mandelbrot::mandelbrot_generator_perturbative<CoordPntNumericType, IterateNumericType>;
  #endif

  #if (!defined(_MSC_VER) && defined(__cplusplus) && (__cplusplus >= 201703L))
  } // namespace ckormanyos::mandelbrot::config
  #else
  } // namespace config
  } // namespace mandelbrot
  } // namespace ckormanyos
  #endif

#endif // MANDELBROT_CFG_MANDELBROT_CFG_05_SEAHORSES_H
