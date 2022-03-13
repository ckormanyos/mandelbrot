///////////////////////////////////////////////////////////////////////////////
//      Copyright Christopher Kormanyos 2022.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef MANDELBROT_CFG_2022_02_24_H
  #define MANDELBROT_CFG_2022_02_24_H

  #include <mandelbrot/mandelbrot.h>

  #if defined(MANDELBROT_USE_GMP_FLOAT)

  #include <boost/multiprecision/gmp.hpp>

  #define MANDELBROT_NUMBER_TYPE_NAME(mandelbrot_digits10) \
  boost::multiprecision::number<boost::multiprecision::gmp_float<(mandelbrot_digits10)>,\
                                boost::multiprecision::et_off>

  #elif defined(MANDELBROT_USE_WIDE_DECIMAL)

  #include <math/wide_decimal/decwide_t.h>

  #define MANDELBROT_NUMBER_TYPE_NAME(mandelbrot_digits10) \
  math::wide_decimal::decwide_t<static_cast<std::int32_t>(mandelbrot_digits10)>

  #else

  #include <boost/multiprecision/cpp_dec_float.hpp>

  #define MANDELBROT_NUMBER_TYPE_NAME(mandelbrot_digits10) \
  boost::multiprecision::number<boost::multiprecision::cpp_dec_float<(mandelbrot_digits10)>,\
                                boost::multiprecision::et_off>

  #endif

  #if(__cplusplus >= 201703L)
  namespace ckormanyos::mandelbrot::cfg {
  #else
  namespace ckormanyos { namespace mandelbrot { namespace cfg { // NOLINT(modernize-concat-nested-namespaces)
  #endif

  namespace detail {

  using numeric_type = MANDELBROT_NUMBER_TYPE_NAME( MANDELBROT_CALCULATION_DIGITS10 );

  } // namespace local

  inline auto filename() -> std::string { return std::string(std::string("images/tmp/mandelbrot_") + MANDELBROT_FILENAME_STRING + std::string(".jpg")); }

  using mandelbrot_config_type  = ckormanyos::mandelbrot::mandelbrot_config<detail::numeric_type, MANDELBROT_CALCULATION_ITERATIONS, MANDELBROT_CALCULATION_PIXELS_1D>;
  using mandelbrot_numeric_type = typename mandelbrot_config_type::mandelbrot_config_numeric_type;

  inline auto dx_half () -> mandelbrot_numeric_type { return mandelbrot_numeric_type(MANDELBROT_POINT_DX_HALF); }
  inline auto center_x() -> mandelbrot_numeric_type { return mandelbrot_numeric_type(MANDELBROT_POINT_CENTER_X); }
  inline auto center_y() -> mandelbrot_numeric_type { return mandelbrot_numeric_type(MANDELBROT_POINT_CENTER_Y); }

  #if(__cplusplus >= 201703L)
  } // namespace ckormanyos::mandelbrot::cfg
  #else
  } // namespace cfg
  } // namespace mandelbrot
  } // namespace ckormanyos
  #endif

#endif // MANDELBROT_CFG_2022_02_24_H
