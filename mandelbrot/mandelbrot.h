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
  template<typename NumericType,
           typename CalcNumericType,
           const std::uint_fast32_t MaxIterations>
  class mandelbrot_config_base
  {
  protected:
    using mandelbrot_config_numeric_type = NumericType;
    using mandelbrot_config_calc_numeric_type = CalcNumericType;

  public:
    static constexpr auto max_iterations = static_cast<std::uint_fast32_t>(MaxIterations);

    mandelbrot_config_base() = delete;

    mandelbrot_config_base(const mandelbrot_config_base& other) = default;

    mandelbrot_config_base(mandelbrot_config_base&& other) noexcept = default;

    mandelbrot_config_base(const mandelbrot_config_numeric_type& xl,
                           const mandelbrot_config_numeric_type& xh, // NOLINT(bugprone-easily-swappable-parameters)
                           const mandelbrot_config_numeric_type& yl,
                           const mandelbrot_config_numeric_type& yh)
      : my_x_lo  (std::move(xl)),
        my_x_hi  (std::move(xh)),
        my_y_lo  (std::move(yl)),
        my_y_hi  (std::move(yh)),
        my_width (std::move(my_x_hi - my_x_lo)),
        my_height(std::move(my_y_hi - my_y_lo)) { }

    virtual ~mandelbrot_config_base() = default;

    auto operator=(const mandelbrot_config_base& other) -> mandelbrot_config_base& = default;

    auto operator=(mandelbrot_config_base&& other) noexcept -> mandelbrot_config_base& = default;

    MANDELBROT_NODISCARD auto x_lo() const -> const mandelbrot_config_numeric_type& { return my_x_lo; }
    MANDELBROT_NODISCARD auto x_hi() const -> const mandelbrot_config_numeric_type& { return my_x_hi; }
    MANDELBROT_NODISCARD auto y_lo() const -> const mandelbrot_config_numeric_type& { return my_y_lo; }
    MANDELBROT_NODISCARD auto y_hi() const -> const mandelbrot_config_numeric_type& { return my_y_hi; }

    MANDELBROT_NODISCARD auto get_width () const -> const mandelbrot_config_numeric_type& { return my_width; }
    MANDELBROT_NODISCARD auto get_height() const -> const mandelbrot_config_numeric_type& { return my_height; }

    MANDELBROT_NODISCARD virtual auto step_x() const -> const mandelbrot_config_numeric_type & = 0;
    MANDELBROT_NODISCARD virtual auto step_y() const -> const mandelbrot_config_numeric_type & = 0;

    MANDELBROT_NODISCARD auto integral_width() const -> std::uint_fast32_t
    {
      const auto non_rounded_width2 =
        static_cast<std::uint_fast32_t>
        (
          mandelbrot_config_numeric_type(my_width * static_cast<std::uint_fast32_t>(UINT8_C(2))) / this->step_x()
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
          mandelbrot_config_numeric_type(my_height * static_cast<std::uint_fast32_t>(UINT8_C(2))) / this->step_y()
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

  private:
    const mandelbrot_config_numeric_type my_x_lo;
    const mandelbrot_config_numeric_type my_x_hi;
    const mandelbrot_config_numeric_type my_y_lo;
    const mandelbrot_config_numeric_type my_y_hi;
    const mandelbrot_config_numeric_type my_width;
    const mandelbrot_config_numeric_type my_height;
  };

  // Make a template class that represents the Mandelbrot configuration.
  // This class automatically creates sensible parameters based on
  // the resolution of the fixed-point type supplied in the template
  // parameter. If a custom pixel count is required, the step()
  // method can be modified accordingly.
  template<typename NumericType,
           typename CalcNumericType,
           const std::uint_fast32_t MaxIterations,
           const std::uint_fast32_t PixelCountX,
           const std::uint_fast32_t PixelCountY>
  class mandelbrot_config final : public mandelbrot_config_base<NumericType, CalcNumericType, MaxIterations> // NOLINT(cppcoreguidelines-special-member-functions,hicpp-special-member-functions)
  {
  private:
    using base_class_type = mandelbrot_config_base<NumericType, CalcNumericType, MaxIterations>;

  public:
    using my_mandelbrot_config_numeric_type = typename base_class_type::mandelbrot_config_numeric_type;
    using my_mandelbrot_config_calc_numeric_type = typename base_class_type::mandelbrot_config_calc_numeric_type;

    mandelbrot_config(const my_mandelbrot_config_numeric_type& xl,
                      const my_mandelbrot_config_numeric_type& xh,
                      const my_mandelbrot_config_numeric_type& yl,
                      const my_mandelbrot_config_numeric_type& yh)
      : base_class_type(xl, xh, yl, yh),
        my_step_x(base_class_type::get_width()  / PixelCountX),
        my_step_y(base_class_type::get_height() / PixelCountY) { } // NOLINT

    mandelbrot_config(const std::string& str_xl,
                      const std::string& str_xh,
                      const std::string& str_yl,
                      const std::string& str_yh)
      : base_class_type(boost::lexical_cast<my_mandelbrot_config_numeric_type>(str_xl),
                        boost::lexical_cast<my_mandelbrot_config_numeric_type>(str_xh),
                        boost::lexical_cast<my_mandelbrot_config_numeric_type>(str_yl),
                        boost::lexical_cast<my_mandelbrot_config_numeric_type>(str_yh)),
        my_step_x(base_class_type::get_width()  / PixelCountX),
        my_step_y(base_class_type::get_height() / PixelCountY) { }

    mandelbrot_config(const char* pc_xl,
                      const char* pc_xh,
                      const char* pc_yl,
                      const char* pc_yh)
      : base_class_type(boost::lexical_cast<my_mandelbrot_config_numeric_type>(std::string(pc_xl)),
                        boost::lexical_cast<my_mandelbrot_config_numeric_type>(std::string(pc_xh)),
                        boost::lexical_cast<my_mandelbrot_config_numeric_type>(std::string(pc_yl)),
                        boost::lexical_cast<my_mandelbrot_config_numeric_type>(std::string(pc_yh))),
        my_step_x(base_class_type::get_width()  / PixelCountX),
        my_step_y(base_class_type::get_height() / PixelCountY) { }

    ~mandelbrot_config() override = default; // LCOV_EXCL_LINE

  private:
    my_mandelbrot_config_numeric_type my_step_x; // NOLINT(readability-identifier-naming)
    my_mandelbrot_config_numeric_type my_step_y; // NOLINT(readability-identifier-naming)

    MANDELBROT_NODISCARD auto step_x() const -> const my_mandelbrot_config_numeric_type & override { return my_step_x; }
    MANDELBROT_NODISCARD auto step_y() const -> const my_mandelbrot_config_numeric_type & override { return my_step_y; }
  };

  // This class generates the rows of the mandelbrot iteration.
  // The coordinates are set up according to the Mandelbrot configuration.
  template<typename NumericType,
           typename CalcNumericType,
           const std::uint_fast32_t MaxIterations>
  class mandelbrot_generator final // NOLINT(cppcoreguidelines-special-member-functions,hicpp-special-member-functions)
  {
  private:
    using numeric_type = NumericType;
    using calc_numberic_type = CalcNumericType;

    static constexpr auto max_iterations = static_cast<std::uint_fast32_t>(MaxIterations);

    using boost_gil_x_coord_type = boost::gil::rgb8_image_t::x_coord_t;
    using boost_gil_y_coord_type = boost::gil::rgb8_image_t::y_coord_t;

  public:
    using mandelbrot_config_type = mandelbrot_config_base<numeric_type, calc_numberic_type, max_iterations>;

    explicit mandelbrot_generator(const mandelbrot_config_type& config)
      : mandelbrot_config_object   (config),
        mandelbrot_image           (static_cast<boost_gil_x_coord_type>(config.integral_width()),
                                    static_cast<boost_gil_y_coord_type>(config.integral_height())),
        mandelbrot_view            (boost::gil::view(mandelbrot_image)),
        mandelbrot_iteration_matrix(config.integral_width(),
                                    std::vector<std::uint_fast32_t>(config.integral_height())),
        mandelbrot_color_histogram (static_cast<std::size_t>(max_iterations + 1U), static_cast<std::uint_fast32_t>(UINT32_C(0))) { }

    mandelbrot_generator() = delete;

    mandelbrot_generator(const mandelbrot_generator&) = delete;
    mandelbrot_generator(mandelbrot_generator&&) noexcept = delete;

    auto operator=(const mandelbrot_generator&) -> mandelbrot_generator& = delete;
    auto operator=(mandelbrot_generator&&) noexcept -> mandelbrot_generator& = delete;

    static auto four() -> const numeric_type&
    {
      static const numeric_type my_four { static_cast<unsigned>(UINT8_C(4)) };

      return my_four;
    }

    auto generate_mandelbrot_image(const std::string&                 str_filename,
                                   const color::color_functions_base& color_functions = color::color_functions_bw(),
                                   const color::color_stretch_base&   color_stretches = color::color_stretch_histogram_method(),
                                         std::ostream&                output_stream   = std::cout) -> void
    {
      // Setup the x-axis and y-axis coordinates.

      const auto flg = output_stream.flags();

      output_stream.setf(std::ios::fixed);
      output_stream.precision(static_cast<std::streamsize>(INT8_C(1)));

      std::vector<numeric_type> zkr(mandelbrot_config_object.max_iterations + static_cast<std::uint_fast32_t>(UINT8_C(1)));
      std::vector<numeric_type> zki(mandelbrot_config_object.max_iterations + static_cast<std::uint_fast32_t>(UINT8_C(1)));

      using std::floor;
      numeric_type x_center(static_cast<numeric_type>((mandelbrot_config_object.x_lo() + mandelbrot_config_object.x_hi()) / static_cast<numeric_type>(UINT8_C(2))));
      numeric_type y_center(static_cast<numeric_type>((mandelbrot_config_object.y_lo() + mandelbrot_config_object.y_hi()) / static_cast<numeric_type>(UINT8_C(2))));

      // Initialize the Zk-Komponence of the central point, assumption: max itterations is reached
      {
        zkr[0] = static_cast<numeric_type>(UINT8_C(0));
        zki[0] = static_cast<numeric_type>(UINT8_C(0));
        numeric_type zr2{ static_cast<numeric_type>(UINT8_C(0)) };
        numeric_type zi2{ static_cast<numeric_type>(UINT8_C(0)) };

        auto iteration_result = static_cast<std::uint_fast32_t>(UINT8_C(1));

        while ((iteration_result < (max_iterations + static_cast<std::uint_fast32_t>(UINT8_C(1)))) && ((zr2 + zi2) < four())) // NOLINT(altera-id-dependent-backward-branch)
        {
          // The inner loop performs optimized complex multiply and add.
          // This is the main work of the fractal iteration scheme.

          zki[iteration_result] = zki[iteration_result-1] * zkr[iteration_result-1];

          zki[iteration_result] += (zki[iteration_result] + y_center);
          zkr[iteration_result] = (zr2 - zi2) + x_center;

          zr2 = zkr[iteration_result] * zkr[iteration_result];
          zi2 = zki[iteration_result] * zki[iteration_result];

          ++iteration_result;
        }

        if (iteration_result < (max_iterations + static_cast<std::uint_fast32_t>(UINT8_C(1))))
        {
          output_stream << "central point escalates \n";
        }
      }

      std::vector<numeric_type> x_coord(mandelbrot_config_object.integral_width());  // NOLINT(hicpp-use-nullptr,altera-id-dependent-backward-branch)
      std::vector<numeric_type> y_coord(mandelbrot_config_object.integral_height()); // NOLINT(hicpp-use-nullptr,altera-id-dependent-backward-branch)

      // Initialize the x-y coordinates.
      {
        numeric_type x_val(mandelbrot_config_object.x_lo() - x_center);
        numeric_type y_val(mandelbrot_config_object.y_hi() - y_center);

        for (auto& x : x_coord) { x = x_val; x_val += mandelbrot_config_object.step_x(); }
        for (auto& y : y_coord) { y = y_val; y_val -= mandelbrot_config_object.step_y(); }
      }

      std::atomic_flag mandelbrot_iteration_lock { };

      std::size_t unordered_parallel_row_count { static_cast<std::size_t>(UINT8_C(0)) };

      my_concurrency::parallel_for
      (
        static_cast<std::size_t>(UINT8_C(0)),
        y_coord.size(),
        [&mandelbrot_iteration_lock, &unordered_parallel_row_count, &output_stream, &x_coord, &y_coord, &zkr, &zki, this](std::size_t j_row)
        {
          while(mandelbrot_iteration_lock.test_and_set()) { ; }

          {
            ++unordered_parallel_row_count;

            const auto percent =
              static_cast<float>
              (
                  static_cast<float>(100.0F * static_cast<float>(unordered_parallel_row_count))
                / static_cast<float>(y_coord.size())
              );

            output_stream << "Calculating Mandelbrot image at row "
                          << unordered_parallel_row_count
                          << " of "
                          << y_coord.size()
                          << ". Total processed so far: "
                          << std::fixed
                          << std::setprecision(1)
                          << percent
                          << "%. Have patience.\r";
          }

          mandelbrot_iteration_lock.clear();

          for(auto   i_col = static_cast<std::size_t>(UINT8_C(0));
                     i_col < x_coord.size(); // NOLINT(altera-id-dependent-backward-branch)
                   ++i_col)
          {
            calc_numberic_type er  { static_cast<unsigned>(UINT8_C(0)) };
            calc_numberic_type ei  { static_cast<unsigned>(UINT8_C(0)) };

            calc_numberic_type zr2 { static_cast<unsigned>(UINT8_C(0)) };
            calc_numberic_type zi2 { static_cast<unsigned>(UINT8_C(0)) };
            calc_numberic_type zer { static_cast<unsigned>(UINT8_C(0)) };
            calc_numberic_type zei { static_cast<unsigned>(UINT8_C(0)) };
            calc_numberic_type zkrTemp{ static_cast<unsigned>(UINT8_C(0)) };
            calc_numberic_type zkiTemp{ static_cast<unsigned>(UINT8_C(0)) };

            // Use an optimized complex-numbered multiplication scheme.
            // Thereby reduce the main work of the Mandelbrot iteration to
            // three real-valued multiplications and several real-valued
            // addition/subtraction operations.

            auto iteration_result = static_cast<std::uint_fast32_t>(UINT8_C(1));

            // Perform the iteration sequence for generating the Mandelbrot set.
            // Here is the main work of the program.

            while((iteration_result < (max_iterations + static_cast<std::uint_fast32_t>(UINT8_C(1)))) && ((zr2 + zi2) < four())) // NOLINT(altera-id-dependent-backward-branch)
            {

              // core funktionality original formular is:
              //  z_{k+1} = z_{k}^2 + c
              // -> delta transformation z_{k+1} -> z_{k+1} + e_{k+1}; z_{k} -> z_{k} + e_{k}; c -> c + d;
              // get it in to the formular we end with:
              // z_{k+1} + e_{k+1} = z_{k} + c + e_{k}^2 + 2*z{k}*e_{k} + d
              // getting rid of the original formular:
              //           e_{k+1} =             e_{k}^2 + 2*z{k}*e_{k} + d
              // where as zk is the precalucated value.


              ei *= (er + zkrTemp);
              ei += (zkiTemp * er);
              ei += ei + static_cast<calc_numberic_type>(y_coord[j_row]);
              er = zer - zei + static_cast<calc_numberic_type>(x_coord[i_col]);

              zkrTemp = static_cast<calc_numberic_type>(zkr[static_cast<std::size_t>(iteration_result)]);
              zkiTemp = static_cast<calc_numberic_type>(zki[static_cast<std::size_t>(iteration_result)]);

              zer = er;
              zer *= (static_cast<calc_numberic_type>(UINT8_C(2)) * zkrTemp) + er;

              zei = ei;
              zei *= (static_cast<calc_numberic_type>(UINT8_C(2)) * zkiTemp) + ei;
              //2*er *t + er *er = er * (2*t + er)

              zr2 = zer + (zkrTemp * zkrTemp);
              zi2 = zei + (zkiTemp * zkiTemp);
              
              // comment: zr2 = zr*zr; zi2= zi*zi is OK ish if four is 400 with some inacuraty

              ++iteration_result;
            }

            // The itaration are shifted by one, to get the same color scaling we subtract the last one
            --iteration_result;

            mandelbrot_iteration_matrix[i_col][j_row] = iteration_result;

            std::atomic<std::uint_fast32_t>*
              ptr_hist
              {
                reinterpret_cast<std::atomic<std::uint_fast32_t>*> // NOLINT(cppcoreguidelines-pro-type-reinterpret-cast)
                (
                  &mandelbrot_color_histogram[static_cast<std::size_t>(iteration_result)]
                )
              };

            std::atomic_fetch_add(ptr_hist, static_cast<std::uint_fast32_t>(UINT8_C(1)));
          }
        }
      );

      output_stream << '\n';

      output_stream << "Perform color stretching." << '\n';
      apply_color_stretches(x_coord, y_coord, color_stretches);

      output_stream << "Apply color functions." << '\n';
      apply_color_functions(x_coord, y_coord, color_functions);

      output_stream << "Write output JPEG file " << str_filename << "." << '\n';
      boost::gil::jpeg_write_view(str_filename, mandelbrot_view);

      output_stream.flags(flg);
    }

  private:
    const mandelbrot_config_type&                      mandelbrot_config_object;    // NOLINT(readability-identifier-naming)

          boost::gil::rgb8_image_t                     mandelbrot_image;            // NOLINT(readability-identifier-naming)
          boost::gil::rgb8_view_t                      mandelbrot_view;             // NOLINT(readability-identifier-naming)

          std::vector<std::vector<std::uint_fast32_t>> mandelbrot_iteration_matrix; // NOLINT(readability-identifier-naming)
          std::vector<std::uint_fast32_t>              mandelbrot_color_histogram;  // NOLINT(readability-identifier-naming)

    auto apply_color_stretches(const std::vector<numeric_type>& x_values,
                               const std::vector<numeric_type>& y_values,
                               const color::color_stretch_base& color_stretches) -> void
    {
      color_stretches.init(static_cast<std::uint_fast32_t>(x_values.size() * y_values.size()));

      for(auto& histogram_entry : mandelbrot_color_histogram)
      {
        color_stretches.color_stretch(histogram_entry);
      }
    }

    auto apply_color_functions(const std::vector<numeric_type>&   x_values,
                               const std::vector<numeric_type>&   y_values,
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
            [](const std::uint_fast32_t color)
            {
              return
                static_cast<std::uint8_t>
                (
                  static_cast<std::uint_fast32_t>
                  (
                    static_cast<std::uint_fast32_t>
                    (
                      static_cast<std::uint_fast32_t>(UINT8_C(255)) * color
                    )
                    / static_cast<std::uint_fast32_t>(UINT8_C(255))
                  )
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

  #if(__cplusplus >= 201703L)
  } // namespace ckormanyos::mandelbrot
  #else
  } // namespace mandelbrot
  } // namespace ckormanyos
  #endif

#endif // MANDELBROT_2015_06_15_H
