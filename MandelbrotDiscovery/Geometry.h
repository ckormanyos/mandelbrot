///////////////////////////////////////////////////////////////////////////////
//      Copyright Christopher Kormanyos 2024.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef GEOMETRY_2024_04_13_H
  #define GEOMETRY_2024_04_13_H

  namespace geometry
  {
    template<typename T>
    struct point_type
    {
      using value_type = T;

      explicit point_type(const value_type& x_val = value_type(),
                          const value_type& y_val = value_type())
        : my_x(x_val),
          my_y(y_val) { }

      value_type my_x { };
      value_type my_y { };
    };

    template<typename PointType>
    struct rectangle_type
    {
      using point_type = PointType;
      using value_type = typename point_type::value_type;

      explicit rectangle_type(const point_type& xy_center,
                              const value_type& dx_half,
                              const value_type& dy_half = dx_half)
        : my_xy_upper_left
          (
            xy_center.my_x - dx_half,
            xy_center.my_y + dy_half
          ),
          my_xy_lower_right
          (
            xy_center.my_x + dx_half,
            xy_center.my_y - dy_half
          )
      { }

      rectangle_type() = delete;

      auto set_pixel_assoc(int pa_x, int pa_y) -> bool
      {
        bool result_is_ok { };

        if((pa_x > 0) && (pa_y > 0))
        {
          result_is_ok = true;

          my_pixels_x = pa_x;
          my_pixels_y = pa_y;

          my_dx_pixel = (my_xy_lower_right.my_x - my_xy_upper_left.my_x ) / my_pixels_x;
          my_dy_pixel = (my_xy_upper_left.my_y  - my_xy_lower_right.my_y) / my_pixels_y;
        }

        return result_is_ok;
      }

      auto pixel_to_point(int pa_x, int pa_y, point_type& pt_val) -> bool
      {
        bool result_is_ok { };

        if((pa_x < my_pixels_x) && (pa_y < my_pixels_y))
        {
          result_is_ok = true;

          using local_value_type = typename point_type::value_type;

          const local_value_type delta_x
          {
              (static_cast<local_value_type>(pa_x) * my_dx_pixel)
            + (my_dx_pixel / 2)
          };

          const local_value_type delta_y
          {
              (static_cast<local_value_type>(pa_y) * my_dy_pixel)
            + (my_dy_pixel / 2)
          };

          pt_val.my_x = my_xy_upper_left.my_x + delta_x;
          pt_val.my_y = my_xy_upper_left.my_y - delta_y;
        }

        return result_is_ok;
      }

      point_type my_xy_upper_left  { };
      point_type my_xy_lower_right { };
      int        my_pixels_x       { };
      int        my_pixels_y       { };
      value_type my_dx_pixel       { };
      value_type my_dy_pixel       { };
    };
  } // namespace geometry

#endif // GEOMETRY_2024_04_13_H
