///////////////////////////////////////////////////////////////////////////////
//      Copyright Christopher Kormanyos 2022 - 2024.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef MANDELBROT_CFG_2022_02_24_H // NOLINT(llvm-header-guard)
  #define MANDELBROT_CFG_2022_02_24_H

  #if !defined(MANDELBROT_NODISCARD)
  #if defined(_MSC_VER) && !defined(__GNUC__)
  #define MANDELBROT_NODISCARD
  #else
  #if (defined(__cplusplus) && (__cplusplus >= 201703L))
  #define MANDELBROT_NODISCARD  [[nodiscard]] // NOLINT(cppcoreguidelines-macro-usage)
  #else
  #define MANDELBROT_NODISCARD
  #endif
  #endif
  #endif

  #include <mandelbrot/mandelbrot_generator_perturbative.h>
  #include <mandelbrot/mandelbrot_generator_trivial.h>

  #include <cstdint>
  #include <string>

  // NOLINTBEGIN(*)

  #if defined(MANDELBROT_USE_GMP_FLOAT)

  #include <boost/multiprecision/gmp.hpp>

  #define MANDELBROT_COORD_PNT_NUMBER_TYPE(MB_DIGITS10) /* NOLINT(cppcoreguidelines-macro-usage) */ \
  boost::multiprecision::number<boost::multiprecision::gmp_float<static_cast<unsigned>(MB_DIGITS10)>,\
                                boost::multiprecision::et_off>

  #define MANDELBROT_ITERATION_NUMBER_TYPE(MB_DIGITS10) MANDELBROT_COORD_PNT_NUMBER_TYPE(MB_DIGITS10) // NOLINT(cppcoreguidelines-macro-usage)

  #else

  #include <boost/multiprecision/cpp_dec_float.hpp>

  #define MANDELBROT_COORD_PNT_NUMBER_TYPE(MB_DIGITS10) /* NOLINT(cppcoreguidelines-macro-usage) */ \
  boost::multiprecision::number<boost::multiprecision::cpp_dec_float<static_cast<unsigned>(MB_DIGITS10)>,\
                                boost::multiprecision::et_off>

  #define MANDELBROT_ITERATION_NUMBER_TYPE(MB_DIGITS10) MANDELBROT_COORD_PNT_NUMBER_TYPE(MB_DIGITS10) // NOLINT(cppcoreguidelines-macro-usage)

  #endif

  #if(__cplusplus >= 201703L)
  namespace ckormanyos::mandelbrot::cfg {
  #else
  namespace ckormanyos { namespace mandelbrot { namespace cfg { // NOLINT(modernize-concat-nested-namespaces)
  #endif

  namespace detail {

  using coord_pnt_numeric_type = MANDELBROT_COORD_PNT_NUMBER_TYPE( MANDELBROT_COORD_PNT_DIGITS10 ); // NOLINT(cppcoreguidelines-macro-usage)
  using iteration_numeric_type = MANDELBROT_ITERATION_NUMBER_TYPE( MANDELBROT_ITERATION_DIGITS10 ); // NOLINT(cppcoreguidelines-macro-usage)

  } // namespace detail

  inline auto filename() -> std::string
  {
    return
      {
          std::string("images/tmp/mandelbrot_")
        + MANDELBROT_FILENAME_STRING // NOLINT(cppcoreguidelines-pro-bounds-array-to-pointer-decay,hicpp-no-array-decay)
      };
  }

  using mandelbrot_config_type  =
    ckormanyos::mandelbrot::mandelbrot_config<detail::coord_pnt_numeric_type,
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

  #if(__cplusplus >= 201703L)
  } // namespace ckormanyos::mandelbrot::cfg
  #else
  } // namespace cfg
  } // namespace mandelbrot
  } // namespace ckormanyos
  #endif

  // NOLINTEND(*)

#endif // MANDELBROT_CFG_2022_02_24_H
