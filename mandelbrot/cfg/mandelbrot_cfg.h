///////////////////////////////////////////////////////////////////////////////
//      Copyright Christopher Kormanyos 2022.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef MANDELBROT_CFG_2022_02_24_H // NOLINT(llvm-header-guard)
  #define MANDELBROT_CFG_2022_02_24_H

  #if defined(__GNUC__)
  #define MANDELBROT_NODISCARD  [[nodiscard]]
  #else
  #define MANDELBROT_NODISCARD
  #endif

  #include <mandelbrot/mandelbrot.h>

  // NOLINTBEGIN(*)

  #if defined(MANDELBROT_USE_GMP_FLOAT)

  #include <boost/multiprecision/gmp.hpp>

  #define MANDELBROT_NUMBER_TYPE_NAME(mandelbrot_digits10) \
  boost::multiprecision::number<boost::multiprecision::gmp_float<static_cast<unsigned>(mandelbrot_digits10)>,\
                                boost::multiprecision::et_off>

  #else

  #include <boost/multiprecision/cpp_dec_float.hpp>

  #define MANDELBROT_NUMBER_TYPE_NAME(mandelbrot_digits10) /* NOLINT(cppcoreguidelines-macro-usage) */ \
  boost::multiprecision::number<boost::multiprecision::cpp_dec_float<static_cast<unsigned>(mandelbrot_digits10)>,\
                                boost::multiprecision::et_off>

  #endif

  #if(__cplusplus >= 201703L)
  namespace ckormanyos::mandelbrot::cfg {
  #else
  namespace ckormanyos { namespace mandelbrot { namespace cfg { // NOLINT(modernize-concat-nested-namespaces)
  #endif

  namespace detail {

  using numeric_type = MANDELBROT_NUMBER_TYPE_NAME( MANDELBROT_CALCULATION_DIGITS10 ); // NOLINT(cppcoreguidelines-macro-usage)

  } // namespace detail

  inline auto filename() -> std::string
  {
    return
      std::string
      (
          std::string("images/tmp/mandelbrot_")
        + MANDELBROT_FILENAME_STRING // NOLINT(cppcoreguidelines-pro-bounds-array-to-pointer-decay,hicpp-no-array-decay)
        + std::string(".jpg")
      );
  }

  using mandelbrot_config_type  =
    ckormanyos::mandelbrot::mandelbrot_config<detail::numeric_type,
                                              static_cast<std::uint_fast32_t>(MANDELBROT_CALCULATION_ITERATIONS),
                                              static_cast<std::uint_fast32_t>(MANDELBROT_CALCULATION_PIXELS_1D)>;

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

  // NOLINTEND(*)

#endif // MANDELBROT_CFG_2022_02_24_H
