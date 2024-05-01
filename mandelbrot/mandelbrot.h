///////////////////////////////////////////////////////////////////////////////
//      Copyright Christopher Kormanyos 2015 - 2024.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef MANDELBROT_2015_06_15_H // NOLINT(llvm-header-guard)
  #define MANDELBROT_2015_06_15_H

  #include <concurrency/parallel_for.h>
  #include <mandelbrot/mandelbrot_color.h>
  #include <mandelbrot/mandelbrot_text_output.h>

  #include <boost/gil/extension/io/jpeg/old.hpp>
  #include <boost/gil/image.hpp>
  #include <boost/gil/typedefs.hpp>
  #include <boost/lexical_cast.hpp>

  #include <atomic>
  #include <cstddef>
  #include <iomanip>
  #include <ostream>
  #include <string>

  #if(__cplusplus >= 201703L)
  namespace ckormanyos::mandelbrot {
  #else
  namespace ckormanyos { namespace mandelbrot { // NOLINT(modernize-concat-nested-namespaces)
  #endif

  // Declare a base class for the Mandelbrot configuration.
  template<typename CoordPntNumericType,
           typename IterateNumericType>
  class mandelbrot_config_base
  {
  public:
    using my_coord_pnt_numeric_type = CoordPntNumericType;
    using my_iteration_numeric_type = IterateNumericType;

    mandelbrot_config_base() = delete;

    mandelbrot_config_base(const mandelbrot_config_base& other) = default;

    mandelbrot_config_base(mandelbrot_config_base&& other) noexcept = default;

    mandelbrot_config_base(const my_coord_pnt_numeric_type& xl,
                           const my_coord_pnt_numeric_type& xh, // NOLINT(bugprone-easily-swappable-parameters)
                           const my_coord_pnt_numeric_type& yl,
                           const my_coord_pnt_numeric_type& yh,
                           const std::uint_fast32_t         iter)
      : my_x_lo      (std::move(xl)),
        my_x_hi      (std::move(xh)),
        my_y_lo      (std::move(yl)),
        my_y_hi      (std::move(yh)),
        my_width     (std::move(my_x_hi - my_x_lo)),
        my_height    (std::move(my_y_hi - my_y_lo)),
        my_iterations(iter) { }

    virtual ~mandelbrot_config_base() = default;

    auto operator=(const mandelbrot_config_base& other) -> mandelbrot_config_base& = default;

    auto operator=(mandelbrot_config_base&& other) noexcept -> mandelbrot_config_base& = default;

    MANDELBROT_NODISCARD auto x_lo() const -> const my_coord_pnt_numeric_type& { return my_x_lo; }
    MANDELBROT_NODISCARD auto x_hi() const -> const my_coord_pnt_numeric_type& { return my_x_hi; }
    MANDELBROT_NODISCARD auto y_lo() const -> const my_coord_pnt_numeric_type& { return my_y_lo; }
    MANDELBROT_NODISCARD auto y_hi() const -> const my_coord_pnt_numeric_type& { return my_y_hi; }

    MANDELBROT_NODISCARD auto get_width () const -> const my_coord_pnt_numeric_type& { return my_width; }
    MANDELBROT_NODISCARD auto get_height() const -> const my_coord_pnt_numeric_type& { return my_height; }

    MANDELBROT_NODISCARD virtual auto step_x() const -> const my_coord_pnt_numeric_type & = 0;
    MANDELBROT_NODISCARD virtual auto step_y() const -> const my_coord_pnt_numeric_type & = 0;

    MANDELBROT_NODISCARD auto integral_width() const -> std::uint_fast32_t
    {
      const auto non_rounded_width2 =
        static_cast<std::uint_fast32_t>
        (
          my_coord_pnt_numeric_type(my_width * static_cast<std::uint_fast32_t>(UINT8_C(2))) / this->step_x()
        );

      return
        static_cast<std::uint_fast32_t>
        (
          static_cast<std::uint_fast32_t>
          (
            non_rounded_width2 + static_cast<std::uint_fast32_t>(UINT8_C(1))
          )
          / static_cast<std::uint_fast32_t>(UINT8_C(2))
        );
    }

    MANDELBROT_NODISCARD auto integral_height() const -> std::uint_fast32_t
    {
      const auto non_rounded_height2 =
        static_cast<std::uint_fast32_t>
        (
          my_coord_pnt_numeric_type(my_height * static_cast<std::uint_fast32_t>(UINT8_C(2))) / this->step_y()
        );

      return
        static_cast<std::uint_fast32_t>
        (
            static_cast<std::uint_fast32_t>
            (
              non_rounded_height2 + static_cast<std::uint_fast32_t>(UINT8_C(1))
            )
          / static_cast<std::uint_fast32_t>(UINT8_C(2))
        );
    }

    auto set_iterations(const std::uint_fast32_t iter) const noexcept -> void { my_iterations = iter; }

    MANDELBROT_NODISCARD auto get_iterations() const noexcept -> std::uint_fast32_t { return my_iterations; }

  private:
    const my_coord_pnt_numeric_type my_x_lo;
    const my_coord_pnt_numeric_type my_x_hi;
    const my_coord_pnt_numeric_type my_y_lo;
    const my_coord_pnt_numeric_type my_y_hi;
    const my_coord_pnt_numeric_type my_width;
    const my_coord_pnt_numeric_type my_height;
    mutable std::uint_fast32_t      my_iterations; // NOLINT(readability-identifier-naming)
  };

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

  // This class generates the rows of the mandelbrot iteration.
  // The coordinates are set up according to the Mandelbrot configuration.

  template<typename CoordPntNumericType,
           typename IterateNumericType>
  class mandelbrot_generator // NOLINT(cppcoreguidelines-special-member-functions,hicpp-special-member-functions)
  {
  public:
    using mandelbrot_config_type = mandelbrot_config_base<CoordPntNumericType, IterateNumericType>;

  protected:
    using my_coord_pnt_numeric_type = typename mandelbrot_config_type::my_coord_pnt_numeric_type;
    using my_iteration_numeric_type = typename mandelbrot_config_type::my_iteration_numeric_type;

  private:
    using boost_gil_x_coord_type = boost::gil::rgb8_image_t::x_coord_t;
    using boost_gil_y_coord_type = boost::gil::rgb8_image_t::y_coord_t;

  public:
    explicit mandelbrot_generator(const mandelbrot_config_type& config)
      : mandelbrot_config_object   (config),
        mandelbrot_image           (static_cast<boost_gil_x_coord_type>(config.integral_width()),
                                    static_cast<boost_gil_y_coord_type>(config.integral_height())),
        mandelbrot_view            (boost::gil::view(mandelbrot_image)),
        mandelbrot_iteration_matrix(config.integral_width(),
                                    std::vector<std::uint_fast32_t>(config.integral_height())),
        mandelbrot_color_histogram (static_cast<std::size_t>(config.get_iterations() + 1U), static_cast<std::uint_fast32_t>(UINT32_C(0))) { }

    mandelbrot_generator() = delete;

    mandelbrot_generator(const mandelbrot_generator&) = delete;
    mandelbrot_generator(mandelbrot_generator&&) noexcept = delete;

    MANDELBROT_NODISCARD auto operator=(const mandelbrot_generator&) -> mandelbrot_generator& = delete;
    MANDELBROT_NODISCARD auto operator=(mandelbrot_generator&&) noexcept -> mandelbrot_generator& = delete;

    static auto four_coord_pnt() -> const my_coord_pnt_numeric_type&
    {
      static const my_coord_pnt_numeric_type my_four { static_cast<unsigned>(UINT8_C(4)) };

      return my_four;
    }

    static auto four_iteration() -> const my_iteration_numeric_type&
    {
      static const my_iteration_numeric_type my_four { static_cast<unsigned>(UINT8_C(4)) };

      return my_four;
    }

    auto set_iterations(const std::uint_fast32_t iter) const noexcept -> void { mandelbrot_config_object.set_iterations(iter); }

    MANDELBROT_NODISCARD auto get_iterations() const noexcept -> std::uint_fast32_t { return mandelbrot_config_object.get_iterations(); }

    virtual auto generate_mandelbrot_image_engine(std::vector<my_iteration_numeric_type>&,
                                                  std::vector<my_iteration_numeric_type>&,
                                                  mandelbrot_text_output_base&) -> void = 0;

    auto generate_mandelbrot_image(const std::string&                 str_filename,
                                   const color::color_functions_base& color_functions = color::color_functions_bw(),
                                   const color::color_stretch_base&   color_stretches = color::color_stretch_histogram_method(),
                                         mandelbrot_text_output_base& text_output     = my_standard_output) -> void
    {
      // Setup the x-axis and y-axis coordinates.

      std::vector<my_iteration_numeric_type> x_coord(mandelbrot_config_object.integral_width());  // NOLINT(hicpp-use-nullptr,altera-id-dependent-backward-branch)
      std::vector<my_iteration_numeric_type> y_coord(mandelbrot_config_object.integral_height()); // NOLINT(hicpp-use-nullptr,altera-id-dependent-backward-branch)

      this->generate_mandelbrot_image_engine(x_coord, y_coord, text_output);

      std::string str { };

      str = "\n";
      text_output.write(str);

      str = "Perform color stretching.\n";
      text_output.write(str);
      apply_color_stretches(x_coord, y_coord, color_stretches);

      str = "Apply color functions.\n";
      text_output.write(str);
      apply_color_functions(x_coord, y_coord, color_functions);

      str = "Write output JPEG file " + str_filename + ".\n";
      text_output.write(str);
      boost::gil::jpeg_write_view(str_filename, mandelbrot_view);
    }

  protected:
    const mandelbrot_config_type&  mandelbrot_config_object;    // NOLINT(readability-identifier-naming,cppcoreguidelines-non-private-member-variables-in-classes,misc-non-private-member-variables-in-classes)

  private:
    boost::gil::rgb8_image_t mandelbrot_image; // NOLINT(readability-identifier-naming)
    boost::gil::rgb8_view_t  mandelbrot_view;  // NOLINT(readability-identifier-naming)

  protected:
    std::vector<std::vector<std::uint_fast32_t>> mandelbrot_iteration_matrix; // NOLINT(readability-identifier-naming,cppcoreguidelines-non-private-member-variables-in-classes,misc-non-private-member-variables-in-classes)
    std::vector<std::uint_fast32_t>              mandelbrot_color_histogram;  // NOLINT(readability-identifier-naming,cppcoreguidelines-non-private-member-variables-in-classes,misc-non-private-member-variables-in-classes)

  private:
    static mandelbrot_text_output_cout my_standard_output; // NOLINT(cppcoreguidelines-avoid-non-const-global-variables)

    auto apply_color_stretches(const std::vector<my_iteration_numeric_type>& x_values,
                               const std::vector<my_iteration_numeric_type>& y_values,
                               const color::color_stretch_base& color_stretches) -> void
    {
      color_stretches.init(static_cast<std::uint_fast32_t>(x_values.size() * y_values.size()));

      for(auto& histogram_entry : mandelbrot_color_histogram)
      {
        color_stretches.color_stretch(histogram_entry);
      }
    }

    auto apply_color_functions(const std::vector<my_iteration_numeric_type>&   x_values,
                               const std::vector<my_iteration_numeric_type>&   y_values,
                               const color::color_functions_base& color_functions) -> void
    {
      for(auto   j_row = static_cast<std::uint_fast32_t>(UINT8_C(0));
                 j_row < static_cast<std::uint_fast32_t>(y_values.size());
               ++j_row)
      {
        for(auto   i_col = static_cast<std::uint_fast32_t>(UINT8_C(0));
                   i_col < static_cast<std::uint_fast32_t>(x_values.size());
                 ++i_col)
        {
          const auto hist_color = mandelbrot_color_histogram[mandelbrot_iteration_matrix[i_col][j_row]];

          // Get the three hue values.
          const auto color_r = static_cast<std::uint_fast32_t>((hist_color <= static_cast<std::uint_fast32_t>(UINT8_C(4))) ? hist_color : color_functions.color_function_r(hist_color));
          const auto color_g = static_cast<std::uint_fast32_t>((hist_color <= static_cast<std::uint_fast32_t>(UINT8_C(4))) ? hist_color : color_functions.color_function_g(hist_color));
          const auto color_b = static_cast<std::uint_fast32_t>((hist_color <= static_cast<std::uint_fast32_t>(UINT8_C(4))) ? hist_color : color_functions.color_function_b(hist_color));

          // Mix the color from the hue values.

          auto color_scaler =
            [](const std::uint_fast32_t color) -> std::uint8_t
            {
              return
                static_cast<std::uint8_t>
                (
                  static_cast<std::uint_fast32_t>
                  (
                    static_cast<std::uint_fast32_t>(UINT8_C(255)) * color
                  )
                  / static_cast<std::uint_fast32_t>(UINT8_C(255))
                );
            };

          const boost_gil_x_coord_type x_col { static_cast<boost_gil_x_coord_type>(i_col) };
          const boost_gil_x_coord_type y_row { static_cast<boost_gil_x_coord_type>(j_row) };

          mandelbrot_view(x_col, y_row) =
            boost::gil::rgb8_pixel_t
            {
              color_scaler(color_r),
              color_scaler(color_g),
              color_scaler(color_b)
            };
        }
      }
    }
  };

  template<typename CoordPntNumericType,
           typename IterateNumericType>
  mandelbrot_text_output_cout mandelbrot_generator<CoordPntNumericType, IterateNumericType>::my_standard_output; // NOLINT(cppcoreguidelines-avoid-non-const-global-variables,hicpp-uppercase-literal-suffix,readability-uppercase-literal-suffix)

  #if(__cplusplus >= 201703L)
  } // namespace ckormanyos::mandelbrot
  #else
  } // namespace mandelbrot
  } // namespace ckormanyos
  #endif

#endif // MANDELBROT_2015_06_15_H
