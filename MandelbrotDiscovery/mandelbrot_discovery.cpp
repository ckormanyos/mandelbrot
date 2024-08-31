///////////////////////////////////////////////////////////////////////////////
// Copyright Christopher Kormanyos 2024.
// Distributed under the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt
// or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#include <mandelbrot_discovery.h>
#include <resource.h>
#include <utility.h>

#include <boost/multiprecision/cpp_dec_float.hpp>

namespace local::cfg
{
  constexpr int  MANDELBROT_COORD_PNT_DIGITS10      =     132;
  constexpr int  MANDELBROT_ITERATION_DIGITS10      =     132;
  constexpr int  MANDELBROT_CALCULATION_PIXELS_X    =     768;
  constexpr int  MANDELBROT_CALCULATION_PIXELS_Y    =     768;

  constexpr char MANDELBROT_POINT_DX_HALF[]         = "1.35";
  constexpr char MANDELBROT_POINT_DY_HALF[]         = "1.35";
  constexpr char MANDELBROT_POINT_CENTER_X[]        = "-0.75";
  constexpr char MANDELBROT_POINT_CENTER_Y[]        = "+0.00";
} // namespace local::cfg

static_assert(local::cfg::MANDELBROT_CALCULATION_PIXELS_X == local::cfg::MANDELBROT_CALCULATION_PIXELS_Y,
              "Error: This program is only compilable for square geometry");

static_assert(util::utility::equal(local::cfg::MANDELBROT_POINT_DX_HALF,
                                   local::cfg::MANDELBROT_POINT_DX_HALF + sizeof(local::cfg::MANDELBROT_POINT_DX_HALF),
                                   local::cfg::MANDELBROT_POINT_DY_HALF),
              "Error: This program is only compilable for square geometry");

using mandelbrot_coord_pnt_type = boost::multiprecision::number<boost::multiprecision::cpp_dec_float<local::cfg::MANDELBROT_COORD_PNT_DIGITS10>, boost::multiprecision::et_off>;
using mandelbrot_iteration_type = boost::multiprecision::number<boost::multiprecision::cpp_dec_float<local::cfg::MANDELBROT_ITERATION_DIGITS10>, boost::multiprecision::et_off>;

inline auto dx_half()  -> mandelbrot_coord_pnt_type { return mandelbrot_coord_pnt_type(local::cfg::MANDELBROT_POINT_DX_HALF); }
inline auto dy_half()  -> mandelbrot_coord_pnt_type { return mandelbrot_coord_pnt_type(local::cfg::MANDELBROT_POINT_DY_HALF); }
inline auto center_x() -> mandelbrot_coord_pnt_type { return mandelbrot_coord_pnt_type(local::cfg::MANDELBROT_POINT_CENTER_X); }
inline auto center_y() -> mandelbrot_coord_pnt_type { return mandelbrot_coord_pnt_type(local::cfg::MANDELBROT_POINT_CENTER_Y); }

using local_window_type = mandelbrot_discovery<static_cast<int>(INT16_C(800)),
                                               static_cast<int>(INT16_C(800)),
                                               mandelbrot_coord_pnt_type,
                                               mandelbrot_iteration_type,
                                               mandelbrot_discovery_detail::WindowTitleDefault,
                                               IDI_MANDELBROT_DISCO>;

using point_type     = typename local_window_type::point_type;
using rectangle_type = typename local_window_type::rectangle_type;

auto rectangle() -> rectangle_type&
{
  static rectangle_type my_rect
  {
    point_type { center_x(), center_y() },
    dx_half(),
    dy_half()
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
