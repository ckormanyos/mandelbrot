///////////////////////////////////////////////////////////////////////////////
// Copyright Christopher Kormanyos 2024.
// Distributed under the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt
// or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#include <mandelbrot_discovery.h>
#include <mandelbrot_discovery_type.h>
#include <resource.h>
#include <utility.h>

#include <tuple>

namespace local
{
  template<const unsigned Digits10>
  struct cfg_type
  {
    static constexpr auto my_digits10() noexcept -> unsigned { return Digits10; }

    using mandelbrot_coord_pnt_type = boost::multiprecision::number<boost::multiprecision::cpp_dec_float<my_digits10()>, boost::multiprecision::et_off>;
    using mandelbrot_iteration_type = boost::multiprecision::number<boost::multiprecision::cpp_dec_float<my_digits10()>, boost::multiprecision::et_off>;
  };

  static constexpr char str_mandelbrot_point_dx_half [] = "+1.35";
  static constexpr char str_mandelbrot_point_dy_half [] = "+1.35";
  static constexpr char str_mandelbrot_point_center_x[] = "-0.75";
  static constexpr char str_mandelbrot_point_center_y[] = "+0.00";
} // namespace local

//static_assert(local::mandelbrot_calculation_pixels_x == local::mandelbrot_calculation_pixels_y,
//              "Error: This program is only compilable for square geometry");

//static_assert(util::utility::equal(local::mandelbrot_point_dx_half(),
//                                   local::mandelbrot_point_dx_half() + util::utility::strlen(local::cfg_type_0::mandelbrot_point_dx_half()),
//                                   local::mandelbrot_point_dy_half()),
//              "Error: This program is only compilable for square geometry");

template<const unsigned Digits10> auto dx_half () -> typename local::cfg_type<Digits10>::mandelbrot_coord_pnt_type { using local_coord_pnt_type = typename local::cfg_type<Digits10>::mandelbrot_coord_pnt_type; return local_coord_pnt_type { local::str_mandelbrot_point_dx_half  }; }
template<const unsigned Digits10> auto dy_half () -> typename local::cfg_type<Digits10>::mandelbrot_coord_pnt_type { using local_coord_pnt_type = typename local::cfg_type<Digits10>::mandelbrot_coord_pnt_type; return local_coord_pnt_type { local::str_mandelbrot_point_dy_half  }; }
template<const unsigned Digits10> auto center_x() -> typename local::cfg_type<Digits10>::mandelbrot_coord_pnt_type { using local_coord_pnt_type = typename local::cfg_type<Digits10>::mandelbrot_coord_pnt_type; return local_coord_pnt_type { local::str_mandelbrot_point_center_x }; }
template<const unsigned Digits10> auto center_y() -> typename local::cfg_type<Digits10>::mandelbrot_coord_pnt_type { using local_coord_pnt_type = typename local::cfg_type<Digits10>::mandelbrot_coord_pnt_type; return local_coord_pnt_type { local::str_mandelbrot_point_center_y }; }

template<const unsigned Digits10>
using rectangle_from_digits_type = geometry::rectangle_type<typename geometry::point_type<typename local::cfg_type<Digits10>::mandelbrot_coord_pnt_type>>;

constexpr inline auto default_00_digits10() -> unsigned { return unsigned { UINT32_C( 44) }; } // For magnification <=  20
constexpr inline auto default_01_digits10() -> unsigned { return unsigned { UINT32_C(104) }; } // For magnification <=  80
constexpr inline auto default_02_digits10() -> unsigned { return unsigned { UINT32_C(536) }; } // For magnification <= 512

using rectangle_00_type      = rectangle_from_digits_type<default_00_digits10()>;
using rectangle_01_type      = rectangle_from_digits_type<default_01_digits10()>;
using rectangle_02_type      = rectangle_from_digits_type<default_02_digits10()>;

using rectangle_tuple_type   = std::tuple<rectangle_00_type&, rectangle_01_type&, rectangle_02_type&>;

using rectangle_ref_00_type  = typename std::tuple_element<0, rectangle_tuple_type>::type;
using rectangle_ref_01_type  = typename std::tuple_element<1, rectangle_tuple_type>::type;
using rectangle_ref_02_type  = typename std::tuple_element<2, rectangle_tuple_type>::type;

using point_00_type          = typename rectangle_00_type::point_type;
using point_01_type          = typename rectangle_01_type::point_type;
using point_02_type          = typename rectangle_02_type::point_type;

using local_window_type = mandelbrot_discovery<static_cast<int>(INT16_C(800)),
                                               static_cast<int>(INT16_C(800)),
                                               rectangle_tuple_type,
                                               mandelbrot_discovery_detail::WindowTitleDefault,
                                               IDI_MANDELBROT_DISCO>;

auto rectangle_00() -> rectangle_00_type&
{
  static rectangle_00_type my_rect
  {
    point_00_type { center_x<default_00_digits10()>(), center_y<default_00_digits10()>() },
    dx_half<default_00_digits10()>(),
    dy_half<default_00_digits10()>()
  };

  static const bool result_pixel_assoc_is_ok { my_rect.set_pixel_assoc(768, 768) };

  static_cast<void>(result_pixel_assoc_is_ok);

  return my_rect;
}

auto rectangle_01() -> rectangle_01_type&
{
  static rectangle_01_type my_rect
  {
    point_01_type { center_x<default_01_digits10()>(), center_y<default_01_digits10()>() },
    dx_half<default_01_digits10()>(),
    dy_half<default_01_digits10()>()
  };

  static const bool result_pixel_assoc_is_ok { my_rect.set_pixel_assoc(768, 768) };

  static_cast<void>(result_pixel_assoc_is_ok);

  return my_rect;
}

auto rectangle_02() -> rectangle_02_type&
{
  static rectangle_02_type my_rect
  {
    point_02_type { center_x<default_02_digits10()>(), center_y<default_02_digits10()>() },
    dx_half<default_02_digits10()>(),
    dy_half<default_02_digits10()>()
  };

  static const bool result_pixel_assoc_is_ok { my_rect.set_pixel_assoc(768, 768) };

  static_cast<void>(result_pixel_assoc_is_ok);

  return my_rect;
}

auto WINAPI WinMain(_In_ ::HINSTANCE h_wnd, _In_opt_ ::HINSTANCE, _In_ LPSTR, _In_ int) -> int
{
  rectangle_tuple_type rectangle_tuple(rectangle_00(), rectangle_01(), rectangle_02());

  local_window_type::set_rectangle_tuple(rectangle_tuple);

  const auto result_win_main = local_window_type::win_main(h_wnd);

  return result_win_main;
}
