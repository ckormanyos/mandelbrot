///////////////////////////////////////////////////////////////////////////////
// Copyright Christopher Kormanyos 2015 - 2025.
// Copyright Sebastian Streubel 2024.
// Distributed under the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt
// or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef MANDELBROT_CONFIG_2015_06_15_H // NOLINT(llvm-header-guard)
  #define MANDELBROT_CONFIG_2015_06_15_H

  #include <mandelbrot/mandelbrot_config_base.h>

  #include <boost/lexical_cast.hpp>

  #include <string>

  #if(__cplusplus >= 201703L)
  namespace ckormanyos::mandelbrot {
  #else
  namespace ckormanyos { namespace mandelbrot { // NOLINT(modernize-concat-nested-namespaces)
  #endif

  // Make a template class that represents the Mandelbrot configuration.
  // This class automatically creates sensible parameters based on
  // the resolution of the fixed-point type supplied in the template
  // parameter. If a custom pixel count is required, the step()
  // method can be modified accordingly.
  template<typename CoordPntNumericType,
           typename IterateNumericType,
           const std::uint_fast32_t PixelCountX,
           const std::uint_fast32_t PixelCountY>
  class mandelbrot_config final : public mandelbrot_config_base<CoordPntNumericType, IterateNumericType> // NOLINT(cppcoreguidelines-special-member-functions,hicpp-special-member-functions)
  {
  private:
    using base_class_type = mandelbrot_config_base<CoordPntNumericType, IterateNumericType>;

  public:
    using my_coord_pnt_numeric_type = typename base_class_type::my_coord_pnt_numeric_type;
    using my_iteration_numeric_type = typename base_class_type::my_iteration_numeric_type;

    mandelbrot_config(const my_coord_pnt_numeric_type& xl,
                      const my_coord_pnt_numeric_type& xh,
                      const my_coord_pnt_numeric_type& yl,
                      const my_coord_pnt_numeric_type& yh,
                      const std::uint_fast32_t         iter)
      : base_class_type(xl, xh, yl, yh, iter),
        my_step_x(base_class_type::get_width()  / PixelCountX),
        my_step_y(base_class_type::get_height() / PixelCountY) { } // NOLINT

    mandelbrot_config(const std::string& str_xl,
                      const std::string& str_xh,
                      const std::string& str_yl,
                      const std::string& str_yh)
      : base_class_type(boost::lexical_cast<my_coord_pnt_numeric_type>(str_xl),
                        boost::lexical_cast<my_coord_pnt_numeric_type>(str_xh),
                        boost::lexical_cast<my_coord_pnt_numeric_type>(str_yl),
                        boost::lexical_cast<my_coord_pnt_numeric_type>(str_yh)),
        my_step_x(base_class_type::get_width()  / PixelCountX),
        my_step_y(base_class_type::get_height() / PixelCountY) { }

    mandelbrot_config(const char* pc_xl,
                      const char* pc_xh,
                      const char* pc_yl,
                      const char* pc_yh)
      : base_class_type(boost::lexical_cast<my_coord_pnt_numeric_type>(std::string(pc_xl)),
                        boost::lexical_cast<my_coord_pnt_numeric_type>(std::string(pc_xh)),
                        boost::lexical_cast<my_coord_pnt_numeric_type>(std::string(pc_yl)),
                        boost::lexical_cast<my_coord_pnt_numeric_type>(std::string(pc_yh))),
        my_step_x(base_class_type::get_width()  / PixelCountX),
        my_step_y(base_class_type::get_height() / PixelCountY) { }

    ~mandelbrot_config() override = default; // LCOV_EXCL_LINE

  private:
    my_coord_pnt_numeric_type my_step_x;      // NOLINT(readability-identifier-naming)
    my_coord_pnt_numeric_type my_step_y;      // NOLINT(readability-identifier-naming)

    MANDELBROT_NODISCARD auto step_x() const -> const my_coord_pnt_numeric_type & override { return my_step_x; }
    MANDELBROT_NODISCARD auto step_y() const -> const my_coord_pnt_numeric_type & override { return my_step_y; }
  };

  #if(__cplusplus >= 201703L)
  } // namespace ckormanyos::mandelbrot
  #else
  } // namespace mandelbrot
  } // namespace ckormanyos
  #endif

#endif // MANDELBROT_CONFIG_2015_06_15_H
