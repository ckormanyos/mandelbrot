///////////////////////////////////////////////////////////////////////////////
//      Copyright Christopher Kormanyos 2022 - 2025.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef MANDELBROT_CFG_2022_02_24_H // NOLINT(llvm-header-guard)
  #define MANDELBROT_CFG_2022_02_24_H

  #include <mandelbrot/cfg/mandelbrot_cfg_forward.h>

  //#include <mandelbrot/cfg/mandelbrot_cfg_MANDELBROT_01_FULL.h>
  //#include <mandelbrot/cfg/mandelbrot_cfg_MANDELBROT_03_TOP.h>
  //#include <mandelbrot/cfg/mandelbrot_cfg_MANDELBROT_04_SWIRL.h>
  #include <mandelbrot/cfg/mandelbrot_cfg_MANDELBROT_05_SEAHORSES.h>
  //#include <mandelbrot/cfg/mandelbrot_cfg_MANDELBROT_06_BRANCHES.h>
  //#include <mandelbrot/cfg/mandelbrot_cfg_MANDELBROT_07_SEAHORSE_VALLEY.h>
  //#include <mandelbrot/cfg/mandelbrot_cfg_MANDELBROT_08_DEEP_DIVE_01.h>
  //#include <mandelbrot/cfg/mandelbrot_cfg_MANDELBROT_08_DEEP_DIVE_01_magnify51.h>
  //#include <mandelbrot/cfg/mandelbrot_cfg_MANDELBROT_09_DEEP_DIVE_02.h>
  //#include <mandelbrot/cfg/mandelbrot_cfg_MANDELBROT_10_ZOOM_WIKI_00.h>
  //#include <mandelbrot/cfg/mandelbrot_cfg_MANDELBROT_10_ZOOM_WIKI_00_rect.h>
  //#include <mandelbrot/cfg/mandelbrot_cfg_MANDELBROT_11_ZOOM_WIKI_01.h>
  //#include <mandelbrot/cfg/mandelbrot_cfg_MANDELBROT_12_ZOOM_WIKI_02.h>
  //#include <mandelbrot/cfg/mandelbrot_cfg_MANDELBROT_13_ZOOM_WIKI_03.h>
  //#include <mandelbrot/cfg/mandelbrot_cfg_MANDELBROT_14_ZOOM_WIKI_04.h>
  //#include <mandelbrot/cfg/mandelbrot_cfg_MANDELBROT_20_ZOOM_VERY_DEEP_00.h>
  //#include <mandelbrot/cfg/mandelbrot_cfg_MANDELBROT_20_ZOOM_VERY_DEEP_00_magnify51.h>
  //#include <mandelbrot/cfg/mandelbrot_cfg_MANDELBROT_20_ZOOM_VERY_DEEP_612.h>
  //#include <mandelbrot/cfg/mandelbrot_cfg_MANDELBROT_25_ZOOM_SEARCH_00.h>
  //#include <mandelbrot/cfg/mandelbrot_cfg_MANDELBROT_25_ZOOM_SEARCH_01.h>
  //#include <mandelbrot/cfg/mandelbrot_cfg_MANDELBROT_30_ZOOM_ANOTHER_00.h>
  //#include <mandelbrot/cfg/mandelbrot_cfg_MANDELBROT_30_ZOOM_ANOTHER_00_magnify51.h>
  //#include <mandelbrot/cfg/mandelbrot_cfg_MANDELBROT_31_ZOOM_ANOTHER_01.h>
  //#include <mandelbrot/cfg/mandelbrot_cfg_MANDELBROT_32_ZOOM_ANOTHER_02.h>
  //#include <mandelbrot/cfg/mandelbrot_cfg_MANDELBROT_33_ZOOM_EVEN_MORE_03.h>
  //#include <mandelbrot/cfg/mandelbrot_cfg_MANDELBROT_40_SEAHORSE_DIVE_01.h>
  //#include <mandelbrot/cfg/mandelbrot_cfg_MANDELBROT_45_SEAHORSE_OTHER_01_magnify51.h>
  //#include <mandelbrot/cfg/mandelbrot_cfg_MANDELBROT_50_TENDRIL_AREA_01.h>
  //#include <mandelbrot/cfg/mandelbrot_cfg_MANDELBROT_60_SATELITE_REGION_01.h>
  //#include <mandelbrot/cfg/mandelbrot_cfg_MANDELBROT_61_SATELITE_REGION_02.h>
  //#include <mandelbrot/cfg/mandelbrot_cfg_MANDELBROT_62_SATELITE_REGION_03.h>
  //#include <mandelbrot/cfg/mandelbrot_cfg_MANDELBROT_63_SATELITE_REGION_04.h>
  //#include <mandelbrot/cfg/mandelbrot_cfg_MANDELBROT_70_DOUADY_RABBIT_01.h>
  //#include <mandelbrot/cfg/mandelbrot_cfg_MANDELBROT_72_DOUADY_RABBIT_03.h>
  //#include <mandelbrot/cfg/mandelbrot_cfg_MANDELBROT_80_SEARCH_HALO_01.h>
  //#include <mandelbrot/cfg/mandelbrot_cfg_MANDELBROT_99_TRY_POINTS.h>

  #include <mandelbrot/mandelbrot_generator_perturbative.h>
  #include <mandelbrot/mandelbrot_generator_trivial.h>

  #if defined(MANDELBROT_USE_GMP_FLOAT)
  #include <boost/multiprecision/gmp.hpp>
  #else
  #include <boost/multiprecision/cpp_dec_float.hpp>
  #endif

  #include <cstdint>
  #include <string>

  #if (!defined(_MSC_VER) && defined(__cplusplus) && (__cplusplus >= 201703L))
  namespace ckormanyos::mandelbrot::config {
  #else
  namespace ckormanyos { namespace mandelbrot { namespace config { // NOLINT(modernize-concat-nested-namespaces)
  #endif

  namespace detail {

  #if defined(MANDELBROT_USE_GMP_FLOAT)

  template<const unsigned MyNumberTypeDigits10>
  using mandelbrot_coord_pnt_number_type =
  boost::multiprecision::number<boost::multiprecision::gmp_float<MyNumberTypeDigits10>,
                                boost::multiprecision::et_off>;

  template<const unsigned MyNumberTypeDigits10>
  using mandelbrot_iteration_number_type = mandelbrot_coord_pnt_number_type<MyNumberTypeDigits10>;

  #else

  template<const unsigned MyNumberTypeDigits10>
  using mandelbrot_coord_pnt_number_type =
    ::boost::multiprecision::number<::boost::multiprecision::cpp_dec_float<MyNumberTypeDigits10>,
                                    ::boost::multiprecision::et_off>;

  template<const unsigned MyNumberTypeDigits10>
  using mandelbrot_iteration_number_type = mandelbrot_coord_pnt_number_type<MyNumberTypeDigits10>;

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

#endif // MANDELBROT_CFG_2022_02_24_H
