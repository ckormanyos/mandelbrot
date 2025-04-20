///////////////////////////////////////////////////////////////////////////////
// Copyright Christopher Kormanyos 2024.
// Distributed under the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt
// or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef MANDELBROT_DISCOVERY_TYPE_2024_09_02_H
  #define MANDELBROT_DISCOVERY_TYPE_2024_09_02_H

  #include <geometry.h>

  #include <mandelbrot/mandelbrot.h>

  #include <type_traits>

  template<const int Digits10>
  struct mandelbrot_discovery_type
  {
    // TBD: Use conditionals based on Digits10.
    using mandelbrot_coord_pnt_type = boost::multiprecision::number<boost::multiprecision::cpp_dec_float<Digits10>, boost::multiprecision::et_off>;
    using mandelbrot_iteration_type = boost::multiprecision::number<boost::multiprecision::cpp_dec_float<Digits10>, boost::multiprecision::et_off>;

    using rectangle_type       = geometry::rectangle_type<typename geometry::point_type<mandelbrot_coord_pnt_type>>;
    using rectangle_point_type = typename rectangle_type::point_type;
  };

#endif // MANDELBROT_DISCOVERY_TYPE_2024_09_02_H
