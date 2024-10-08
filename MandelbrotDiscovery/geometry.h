///////////////////////////////////////////////////////////////////////////////
// Copyright Christopher Kormanyos 2024.
// Distributed under the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt
// or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef GEOMETRY_2024_04_13_H
  #define GEOMETRY_2024_04_13_H

  namespace geometry
  {
    template<typename T>
    struct point_type
    {
    public:
      using value_type = T;

      explicit point_type(const value_type& x_val = value_type(),
                          const value_type& y_val = value_type())
        : my_x(x_val),
          my_y(y_val) { }

      auto get_x() const noexcept -> const value_type& { return my_x; }
      auto get_y() const noexcept -> const value_type& { return my_y; }

      auto set_x(const value_type& new_x) noexcept -> void { my_x = new_x; }
      auto set_y(const value_type& new_y) noexcept -> void { my_y = new_y; }

    private:
      value_type my_x { };
      value_type my_y { };
    };

    struct rectangle_base
    {
    public:
      static constexpr auto default_pixels() noexcept -> int { return 768; }

      virtual ~rectangle_base() = default;

    protected:
      rectangle_base() = default;
    };

    template<typename PointType>
    struct rectangle_type : public rectangle_base
    {
    private:
      using base_class_type = rectangle_base;

    public:
      using point_type = PointType;
      using value_type = typename point_type::value_type;

      explicit rectangle_type(const point_type& ctr,
                              const value_type& dxh,
                              const value_type& dyh = dxh) noexcept
        : my_center (ctr),
          my_dx_half(dxh),
          my_dy_half(dyh) { }

      rectangle_type() = delete;

      ~rectangle_type() override = default;

      auto operator*=(const int n) -> rectangle_type&
      {
        static_cast<void>(my_dx_half *= n);
        static_cast<void>(my_dy_half *= n);

        static_cast<void>(set_pixel_assoc(my_pixels_x, my_pixels_y));

        return *this;
      }

      auto operator/=(const int n) -> rectangle_type&
      {
        static_cast<void>(my_dx_half /= n);
        static_cast<void>(my_dy_half /= n);

        static_cast<void>(set_pixel_assoc(my_pixels_x, my_pixels_y));

        return *this;
      }

      auto upper_left() const noexcept -> point_type
      {
        return
          point_type
          (
            my_center.get_x() - my_dx_half,
            my_center.get_y() + my_dy_half
          );
      }

      auto lower_right() const noexcept -> point_type
      {
        return
          point_type
          (
            my_center.get_x() + my_dx_half,
            my_center.get_y() - my_dy_half
          );
      }

      auto dx_half() const noexcept -> value_type { return my_dx_half; }
      auto dy_half() const noexcept -> value_type { return my_dy_half; }

      auto center() const noexcept -> const point_type { return my_center; }

      auto recenter(const point_type& new_center) noexcept -> void
      {
        my_center = new_center;
      }

      auto set_pixel_assoc(const int pa_x, const int pa_y) noexcept -> bool
      {
        bool result_is_ok { };

        if((pa_x > 0) && (pa_y > 0))
        {
          result_is_ok = true;

          my_pixels_x = pa_x;
          my_pixels_y = pa_y;

          const auto& lo_right = lower_right();
          const auto& up_left  = upper_left ();

          my_dx_pixel = (lo_right.get_x() - up_left.get_x() ) / my_pixels_x;
          my_dy_pixel = (up_left.get_y()  - lo_right.get_y()) / my_pixels_y;
        }

        return result_is_ok;
      }

      auto pixel_to_point(const int pa_x, const int pa_y, point_type& pt_val) const noexcept -> bool
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

          pt_val.set_x(up_left.get_x() + delta_x);
          pt_val.set_y(up_left.get_y() - delta_y);
        }

        return result_is_ok;
      }

    private:
      point_type my_center   { };
      value_type my_dx_half  { };
      value_type my_dy_half  { };
      value_type my_dx_pixel { };
      value_type my_dy_pixel { };
      int        my_pixels_x { };
      int        my_pixels_y { };
    };

    template<typename PointType>
    inline auto operator*(const rectangle_type<PointType>& lhs, const int n) -> rectangle_type<PointType>
    {
      using local_point_type = PointType;

      return rectangle_type<local_point_type>(lhs) *= n;
    }

    template<typename PointType>
    inline auto operator/(const rectangle_type<PointType>& lhs, const int n) -> rectangle_type<PointType>
    {
      using local_point_type = PointType;

      return rectangle_type<local_point_type>(lhs) /= n;
    }
  } // namespace geometry

#endif // GEOMETRY_2024_04_13_H
