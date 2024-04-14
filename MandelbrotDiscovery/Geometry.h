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

      point_type(const value_type& x_val = value_type(),
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

      explicit rectangle_type(const point_type& center,
                              const value_type& dx_half,
                              const value_type& dy_half = dx_half)
        : my_center (center),
          my_dx_half(dx_half),
          my_dy_half(dy_half) { }

      rectangle_type() = delete;

      auto operator/=(const int n) -> rectangle_type&
      {
        my_dx_half /= n;
        my_dy_half /= n;

        static_cast<void>(set_pixel_assoc(my_pixels_x, my_pixels_y));

        return *this;
      }

      auto upper_left() const -> point_type
      {
        return
          {
            my_center.my_x - my_dx_half,
            my_center.my_y + my_dy_half
          };
      }

      auto lower_right() const -> point_type
      {
        return
          {
            my_center.my_x + my_dx_half,
            my_center.my_y - my_dy_half
          };
      }

      auto recenter(const point_type& new_center) -> void
      {
        my_center = new_center;
      }

      auto set_pixel_assoc(const int pa_x, const int pa_y) -> bool
      {
        bool result_is_ok { };

        if((pa_x > 0) && (pa_y > 0))
        {
          result_is_ok = true;

          my_pixels_x = pa_x;
          my_pixels_y = pa_y;

          const auto lo_right = lower_right();
          const auto up_left  = upper_left ();

          my_dx_pixel = (lo_right.my_x - up_left.my_x ) / my_pixels_x;
          my_dy_pixel = (up_left.my_y  - lo_right.my_y) / my_pixels_y;
        }

        return result_is_ok;
      }

      auto pixel_to_point(const int pa_x, const int pa_y, point_type& pt_val) const -> bool
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

          const auto up_left = upper_left();

          pt_val.my_x = up_left.my_x + delta_x;
          pt_val.my_y = up_left.my_y - delta_y;
        }

        return result_is_ok;
      }

      point_type my_center   { };
      value_type my_dx_half  { };
      value_type my_dy_half  { };
      value_type my_dx_pixel { };
      value_type my_dy_pixel { };
      int        my_pixels_x { };
      int        my_pixels_y { };
    };
  } // namespace geometry

#endif // GEOMETRY_2024_04_13_H
