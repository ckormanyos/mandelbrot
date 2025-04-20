///////////////////////////////////////////////////////////////////////////////
//      Copyright Christopher Kormanyos 2025.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef MANDELBROT_CFG_FORWARD_2025_04_18_H // NOLINT(llvm-header-guard)
  #define MANDELBROT_CFG_FORWARD_2025_04_18_H

  #if (!defined(_MSC_VER) && defined(__cplusplus) && (__cplusplus >= 201703L))
  namespace ckormanyos::mandelbrot {
  #else
  namespace ckormanyos { namespace mandelbrot { // NOLINT(modernize-concat-nested-namespaces)
  #endif

  template<typename CoordPntNumericType, typename IterateNumericType>
  class mandelbrot_generator_trivial;

  template<typename CoordPntNumericType, typename IterateNumericType>
  class mandelbrot_generator_perturbative;

  #if (!defined(_MSC_VER) && defined(__cplusplus) && (__cplusplus >= 201703L))
  } // namespace ckormanyos::mandelbrot
  #else
  } // namespace mandelbrot
  } // namespace ckormanyos
  #endif

#endif // MANDELBROT_CFG_FORWARD_2025_04_18_H
