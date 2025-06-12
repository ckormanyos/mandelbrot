///////////////////////////////////////////////////////////////////////////////
// Copyright Christopher Kormanyos 2015 - 2025.
// Copyright Sebastian Streubel 2024.
// Distributed under the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt
// or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef MANDELBROT_GENERATOR_2015_06_15_H // NOLINT(llvm-header-guard)
  #define MANDELBROT_GENERATOR_2015_06_15_H

  #include <concurrency/parallel_for.h>
  #include <mandelbrot/mandelbrot_color.h>
  #include <mandelbrot/mandelbrot_config.h>
  #include <mandelbrot/mandelbrot_text_output.h>

  #include <boost/gil/extension/io/jpeg/old.hpp>
  #include <boost/gil/extension/io/png/old.hpp>
  #include <boost/gil/image.hpp>
  #include <boost/gil/typedefs.hpp>

  #include <iomanip>
  #include <ostream>
  #include <string>

  #if(__cplusplus >= 201703L)
  namespace ckormanyos::mandelbrot {
  #else
  namespace ckormanyos { namespace mandelbrot { // NOLINT(modernize-concat-nested-namespaces)
  #endif

  // This class generates the rows of the mandelbrot iteration.
  // The coordinates are set up according to the Mandelbrot configuration.

  template<typename CoordPntNumericType,
           typename IterateNumericType>
  class mandelbrot_generator
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

    // LCOV_EXCL_START

    mandelbrot_generator() = delete;

    mandelbrot_generator(const mandelbrot_generator&) = delete;
    mandelbrot_generator(mandelbrot_generator&&) noexcept = delete;

    virtual ~mandelbrot_generator() = default;

    MANDELBROT_NODISCARD auto operator=(const mandelbrot_generator&) -> mandelbrot_generator& = delete;
    MANDELBROT_NODISCARD auto operator=(mandelbrot_generator&&) noexcept -> mandelbrot_generator& = delete;

    // LCOV_EXCL_STOP

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
                                         mandelbrot_text_output_base& my_text_output  = my_standard_output) -> void
    {
      // Setup the x-axis and y-axis coordinates.

      std::vector<my_iteration_numeric_type> x_coord(mandelbrot_config_object.integral_width());  // NOLINT(hicpp-use-nullptr,altera-id-dependent-backward-branch,cppcoreguidelines-init-variables)
      std::vector<my_iteration_numeric_type> y_coord(mandelbrot_config_object.integral_height()); // NOLINT(hicpp-use-nullptr,altera-id-dependent-backward-branch,cppcoreguidelines-init-variables)

      this->generate_mandelbrot_image_engine(x_coord, y_coord, my_text_output);

      my_text_output.write("\n");

      my_text_output.write("Perform color stretching.\n");
      apply_color_stretches(x_coord, y_coord, color_stretches);

      my_text_output.write("Apply color functions.\n");
      apply_color_functions(x_coord, y_coord, color_functions);

      my_text_output.write("Write output JPEG file " + str_filename + ".\n");

      boost::gil::jpeg_write_view(str_filename + std::string(".jpg"), mandelbrot_view);
      boost::gil::png_write_view (str_filename + std::string(".png"), mandelbrot_view);
    }

  protected:
    const mandelbrot_config_type&  mandelbrot_config_object;    // NOLINT(readability-identifier-naming,cppcoreguidelines-non-private-member-variables-in-classes,misc-non-private-member-variables-in-classes)

  private:
    static mandelbrot_text_output_cout my_standard_output; // NOLINT(cppcoreguidelines-avoid-non-const-global-variables)

    boost::gil::rgb8_image_t mandelbrot_image { }; // NOLINT(readability-identifier-naming)
    boost::gil::rgb8_view_t  mandelbrot_view { };  // NOLINT(readability-identifier-naming)

  protected:
    std::vector<std::vector<std::uint_fast32_t>> mandelbrot_iteration_matrix { }; // NOLINT(readability-identifier-naming,cppcoreguidelines-non-private-member-variables-in-classes,misc-non-private-member-variables-in-classes)
    std::vector<std::uint_fast32_t>              mandelbrot_color_histogram { };  // NOLINT(readability-identifier-naming,cppcoreguidelines-non-private-member-variables-in-classes,misc-non-private-member-variables-in-classes)

  private:
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
