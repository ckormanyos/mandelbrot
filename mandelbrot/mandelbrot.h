﻿///////////////////////////////////////////////////////////////////////////////
//      Copyright Christopher Kormanyos 2022 - 2025.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef MANDELBROT_MANDELBROT_H
  #define MANDELBROT_MANDELBROT_H

  #include <mandelbrot/mandelbrot_cfg.h>
  #include <mandelbrot/mandelbrot_generator_perturbative.h>
  #include <mandelbrot/mandelbrot_generator_trivial.h>

  #if (!defined(_MSC_VER) && defined(__cplusplus) && (__cplusplus >= 201703L))
  namespace ckormanyos::mandelbrot::config {
  #else
  namespace ckormanyos { namespace mandelbrot { namespace config { // NOLINT(modernize-concat-nested-namespaces)
  #endif

  namespace detail {

  #if defined(MANDELBROT_USE_CPP_DEC_FLOAT)

  #if !defined(MANDELBROT_USE_CPP_DOUBLE_DOUBLE)

  template<const unsigned MyNumberTypeDigits10>
  using mandelbrot_coord_pnt_number_type = ::boost::multiprecision::number<::boost::multiprecision::cpp_dec_float<MyNumberTypeDigits10>, ::boost::multiprecision::et_off>;

  template<const unsigned MyNumberTypeDigits10>
  using mandelbrot_iteration_number_type = mandelbrot_coord_pnt_number_type<MyNumberTypeDigits10>;

  #else

  template<const unsigned MyNumberTypeDigits10>
  using mandelbrot_coord_pnt_number_type =
    typename std::conditional<static_cast<bool>(MyNumberTypeDigits10 > unsigned { UINT8_C(32) }),
                              ::boost::multiprecision::number<::boost::multiprecision::cpp_dec_float<MyNumberTypeDigits10>, ::boost::multiprecision::et_off>,
                              ::boost::multiprecision::cpp_double_double>::type;

  template<const unsigned MyNumberTypeDigits10>
  using mandelbrot_iteration_number_type =
    typename std::conditional<static_cast<bool>(MyNumberTypeDigits10 > unsigned { UINT8_C(32) }),
                              ::boost::multiprecision::number<::boost::multiprecision::cpp_dec_float<MyNumberTypeDigits10>, ::boost::multiprecision::et_off>,
                              ::boost::multiprecision::cpp_double_double>::type;

  #endif

  #elif defined(MANDELBROT_USE_GMP_FLOAT)

  #if !defined(MANDELBROT_USE_CPP_DOUBLE_DOUBLE)

  template<const unsigned MyNumberTypeDigits10>
  using mandelbrot_coord_pnt_number_type = ::boost::multiprecision::number<boost::multiprecision::gmp_float<MyNumberTypeDigits10>, boost::multiprecision::et_off>;

  template<const unsigned MyNumberTypeDigits10>
  using mandelbrot_iteration_number_type = mandelbrot_coord_pnt_number_type<MyNumberTypeDigits10>;

  #else

  template<const unsigned MyNumberTypeDigits10>
  using mandelbrot_coord_pnt_number_type =
    typename std::conditional<static_cast<bool>(MyNumberTypeDigits10 > unsigned { UINT8_C(32) }),
                              ::boost::multiprecision::number<boost::multiprecision::gmp_float<MyNumberTypeDigits10>, boost::multiprecision::et_off>,
                              ::boost::multiprecision::cpp_double_double>::type;

  template<const unsigned MyNumberTypeDigits10>
  using mandelbrot_iteration_number_type =
    typename std::conditional<static_cast<bool>(MyNumberTypeDigits10 > unsigned { UINT8_C(32) }),
                              ::boost::multiprecision::number<boost::multiprecision::gmp_float<MyNumberTypeDigits10>, boost::multiprecision::et_off>,
                              ::boost::multiprecision::cpp_double_double>::type;

  #endif

  #endif

  using coord_pnt_numeric_type = mandelbrot_coord_pnt_number_type<MANDELBROT_COORD_PNT_DIGITS10>; // NOLINT(cppcoreguidelines-macro-usage)
  using iteration_numeric_type = mandelbrot_iteration_number_type<MANDELBROT_ITERATION_DIGITS10>; // NOLINT(cppcoreguidelines-macro-usage)

  } // namespace detail

  using mandelbrot_config_type  =
    ::ckormanyos::mandelbrot::mandelbrot_config<detail::coord_pnt_numeric_type,
                                                detail::iteration_numeric_type,
                                                static_cast<std::uint_fast32_t>(MANDELBROT_CALCULATION_PIXELS_X),
                                                static_cast<std::uint_fast32_t>(MANDELBROT_CALCULATION_PIXELS_Y)>;

  using coord_pnt_numeric_type = typename mandelbrot_config_type::my_coord_pnt_numeric_type;
  using iteration_numeric_type = typename mandelbrot_config_type::my_iteration_numeric_type;

  inline auto dx_half () -> coord_pnt_numeric_type { return coord_pnt_numeric_type(MANDELBROT_POINT_DX_HALF); }
  inline auto dy_half()  -> coord_pnt_numeric_type { return coord_pnt_numeric_type(MANDELBROT_POINT_DY_HALF); }
  inline auto center_x() -> coord_pnt_numeric_type { return coord_pnt_numeric_type(MANDELBROT_POINT_CENTER_X); }
  inline auto center_y() -> coord_pnt_numeric_type { return coord_pnt_numeric_type(MANDELBROT_POINT_CENTER_Y); }
  inline auto max_iter() -> std::uint_fast32_t     { return static_cast<std::uint_fast32_t>(MANDELBROT_CALCULATION_ITERATIONS); }

  inline auto filename() -> std::string
  {
    return
      {
          std::string("images/tmp/mandelbrot_")
        + MANDELBROT_FILENAME_STRING // NOLINT(cppcoreguidelines-pro-bounds-array-to-pointer-decay,hicpp-no-array-decay)
      };
  }

  #if (!defined(_MSC_VER) && defined(__cplusplus) && (__cplusplus >= 201703L))
  } // namespace ckormanyos::mandelbrot::config
  #else
  } // namespace config
  } // namespace mandelbrot
  } // namespace ckormanyos
  #endif

#endif // MANDELBROT_MANDELBROT_H
