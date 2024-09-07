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

constexpr inline auto default_digits10() -> unsigned { return 132U; }

using local_window_type = mandelbrot_discovery<static_cast<int>(INT16_C(800)),
                                               static_cast<int>(INT16_C(800)),
                                               rectangle_from_digits_type<default_digits10()>,
                                               mandelbrot_discovery_detail::WindowTitleDefault,
                                               IDI_MANDELBROT_DISCO>;

using rectangle_type = rectangle_from_digits_type<default_digits10()>;
using point_type     = typename rectangle_type::point_type;

auto rectangle() -> rectangle_type&
{
  static rectangle_type my_rect
  {
    point_type { center_x<default_digits10()>(), center_y<default_digits10()>() },
    dx_half<default_digits10()>(),
    dy_half<default_digits10()>()
  };

  static const bool result_pixel_assoc_is_ok { my_rect.set_pixel_assoc(768, 768) };

  static_cast<void>(result_pixel_assoc_is_ok);

  return my_rect;
}

auto WINAPI WinMain(_In_ ::HINSTANCE h_wnd, _In_opt_ ::HINSTANCE, _In_ LPSTR, _In_ int) -> int
{
  local_window_type::set_rectangle(rectangle());

  const auto result_win_main = local_window_type::win_main(h_wnd);

  return result_win_main;
}
