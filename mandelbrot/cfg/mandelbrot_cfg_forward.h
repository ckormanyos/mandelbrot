///////////////////////////////////////////////////////////////////////////////
//      Copyright Christopher Kormanyos 2025 - 2026.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef MANDELBROT_CFG_MANDELBROT_CFG_FORWARD_H
  #define MANDELBROT_CFG_MANDELBROT_CFG_FORWARD_H

  #if defined(_MSC_VER)
  #define MANDELBROT_MSVC _MSC_VER
  #elif defined(__clang__)
  #define MANDELBROT_CLANG __clang__
  #elif defined(__GNUC__)
  #define MANDELBROT_GCC __GNUC__
  #else
  #error "Unknown compiler (none of MSVC, Clang, GCC)."
  #endif

  // --------------------------------------------------------------------------
  // Obtain the C++ language standard.
  // --------------------------------------------------------------------------

  #if defined(MANDELBROT_MSVC)
  #define MANDELBROT_CXX_VERSION _MSVC_LANG
  #else
  #define MANDELBROT_CXX_VERSION __cplusplus // NOLINT(cppcoreguidelines-macro-usage)
  #endif

  #if !defined(MANDELBROT_NODISCARD)
  #if defined(MANDELBROT_MSVC)
  #define MANDELBROT_NODISCARD [[nodiscard]]
  #else
  #if (defined(MANDELBROT_CXX_VERSION) && (MANDELBROT_CXX_VERSION >= 201703L))
  #define MANDELBROT_NODISCARD  [[nodiscard]] // NOLINT(cppcoreguidelines-macro-usage)
  #else
  #define MANDELBROT_NODISCARD
  #endif
  #endif
  #endif

  #if (defined(MANDELBROT_CXX_VERSION) && (MANDELBROT_CXX_VERSION >= 201703L))
  namespace ckormanyos::mandelbrot {
  #else
  namespace ckormanyos { namespace mandelbrot { // NOLINT(modernize-concat-nested-namespaces)
  #endif

  template<typename CoordPntNumericType, typename IterateNumericType>
  class mandelbrot_generator_trivial;

  template<typename CoordPntNumericType, typename IterateNumericType>
  class mandelbrot_generator_perturbative;

  #if (defined(MANDELBROT_CXX_VERSION) && (MANDELBROT_CXX_VERSION >= 201703L))
  } // namespace ckormanyos::mandelbrot
  #else
  } // namespace mandelbrot
  } // namespace ckormanyos
  #endif

#endif // MANDELBROT_CFG_MANDELBROT_CFG_FORWARD_H
