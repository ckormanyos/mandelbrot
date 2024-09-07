///////////////////////////////////////////////////////////////////////////////
// Copyright Christopher Kormanyos 2015 - 2024.
// Distributed under the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt
// or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef MANDELBROT_GENERATOR_TRIVIAL_2024_04_28_H // NOLINT(llvm-header-guard)
  #define MANDELBROT_GENERATOR_TRIVIAL_2024_04_28_H

  #include <mandelbrot/mandelbrot.h>

  #include <concurrency/parallel_for.h>

  #include <atomic>

  #if(__cplusplus >= 201703L)
  namespace ckormanyos::mandelbrot {
  #else
  namespace ckormanyos { namespace mandelbrot { // NOLINT(modernize-concat-nested-namespaces)
  #endif

  // This class generates the rows of the mandelbrot iteration.
  // The coordinates are set up according to the Mandelbrot configuration.
  template<typename CoordPntNumericType,
           typename IterateNumericType = CoordPntNumericType> class mandelbrot_generator_trivial final // NOLINT(cppcoreguidelines-special-member-functions,hicpp-special-member-functions)
    : public mandelbrot_generator<CoordPntNumericType, IterateNumericType>
  {
  private:
    static_assert(std::is_same<CoordPntNumericType, IterateNumericType>::value,
                  "Error: The trivial Mandelbrot generator must have equivalent coordinate and iteration types");

    using base_class_type = mandelbrot_generator<CoordPntNumericType, CoordPntNumericType>;

    using mandelbrot_config_type = typename base_class_type::mandelbrot_config_type;

    static_assert(std::numeric_limits<typename base_class_type::my_iteration_numeric_type>::digits == std::numeric_limits<typename base_class_type::my_coord_pnt_numeric_type>::digits,
                  "Error: For trivial iteration coordinate and iteration precision must be the same. Check config.");

  public:
    using my_iteration_numeric_type = typename base_class_type::my_iteration_numeric_type;

    explicit mandelbrot_generator_trivial(const mandelbrot_config_type& config)
      : base_class_type(config) { }

    mandelbrot_generator_trivial() = delete;

    mandelbrot_generator_trivial(const mandelbrot_generator_trivial&) = delete;
    mandelbrot_generator_trivial(mandelbrot_generator_trivial&&) noexcept = delete;

    ~mandelbrot_generator_trivial() override = default; // LCOV_EXCL_LINE

    auto operator=(const mandelbrot_generator_trivial&) -> mandelbrot_generator_trivial& = delete;
    auto operator=(mandelbrot_generator_trivial&&) noexcept -> mandelbrot_generator_trivial& = delete;

    auto generate_mandelbrot_image_engine(std::vector<my_iteration_numeric_type>& x_coord,
                                          std::vector<my_iteration_numeric_type>& y_coord,
                                          text_output_base& text_output) -> void override
    {
      // Initialize the x-y coordinates.
      {
        my_iteration_numeric_type x_val(base_class_type::mandelbrot_config_object.x_lo());
        my_iteration_numeric_type y_val(base_class_type::mandelbrot_config_object.y_hi());

        const my_iteration_numeric_type dx { static_cast<my_iteration_numeric_type>(base_class_type::mandelbrot_config_object.step_x()) };
        const my_iteration_numeric_type dy { static_cast<my_iteration_numeric_type>(base_class_type::mandelbrot_config_object.step_y()) };

        for(auto& x : x_coord) { x = x_val; x_val += dx; }
        for(auto& y : y_coord) { y = y_val; y_val -= dy; }
      }

      std::atomic_flag mandelbrot_iteration_lock { };

      std::size_t unordered_parallel_row_count { static_cast<std::size_t>(UINT8_C(0)) };

      my_concurrency::parallel_for
      (
        static_cast<std::size_t>(UINT8_C(0)),
        y_coord.size(),
        [&mandelbrot_iteration_lock, &unordered_parallel_row_count, &text_output, &x_coord, &y_coord, this](std::size_t j_row)
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

            std::stringstream strm { };

            strm << "Calculating Mandelbrot image at row "
                 << unordered_parallel_row_count
                 << " of "
                 << y_coord.size()
                 << ". Total processed so far: "
                 << std::fixed
                 << std::setprecision(1)
                 << percent
                 << "%. Have patience.\r";

            text_output.write(strm.str());
          }

          mandelbrot_iteration_lock.clear();

          for(auto   i_col = static_cast<std::size_t>(UINT8_C(0));
                     i_col < x_coord.size(); // NOLINT(altera-id-dependent-backward-branch)
                   ++i_col)
          {
            my_iteration_numeric_type zr  { static_cast<unsigned>(UINT8_C(0)) };
            my_iteration_numeric_type zi  { static_cast<unsigned>(UINT8_C(0)) };
            my_iteration_numeric_type zr2 { static_cast<unsigned>(UINT8_C(0)) };
            my_iteration_numeric_type zi2 { static_cast<unsigned>(UINT8_C(0)) };

            // Use an optimized complex-numbered multiplication scheme.
            // Thereby reduce the main work of the Mandelbrot iteration to
            // three real-valued multiplications and several real-valued
            // addition/subtraction operations.

            auto iteration_result = static_cast<std::uint_fast32_t>(UINT8_C(0));

            // Perform the iteration sequence for generating the Mandelbrot set.
            // Here is the main work of the program.

            while((iteration_result < base_class_type::get_iterations()) && ((zr2 + zi2) < base_class_type::four_iteration())) // NOLINT(altera-id-dependent-backward-branch)
            {
              // The inner loop performs optimized complex multiply and add.
              // This is the main work of the fractal iteration scheme.

              zi *= zr;

              zi += (zi + y_coord[j_row]);
              zr  = (zr2 - zi2) + x_coord[i_col];

              zr2 = zr * zr;
              zi2 = zi * zi;

              ++iteration_result;
            }

            base_class_type::mandelbrot_iteration_matrix[i_col][j_row] = iteration_result;

            std::atomic<std::uint_fast32_t>*
              ptr_hist
              {
                reinterpret_cast<std::atomic<std::uint_fast32_t>*> // NOLINT(cppcoreguidelines-pro-type-reinterpret-cast)
                (
                  &base_class_type::mandelbrot_color_histogram[static_cast<std::size_t>(iteration_result)]
                )
              };

            std::atomic_fetch_add(ptr_hist, static_cast<std::uint_fast32_t>(UINT8_C(1)));
          }
        }
      );
    }
  };

  #if(__cplusplus >= 201703L)
  } // namespace ckormanyos::mandelbrot
  #else
  } // namespace mandelbrot
  } // namespace ckormanyos
  #endif

#endif // MANDELBROT_GENERATOR_TRIVIAL_2024_04_28_H
