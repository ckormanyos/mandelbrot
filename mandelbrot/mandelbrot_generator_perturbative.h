///////////////////////////////////////////////////////////////////////////////
//      Copyright Sebastian Streubel 2024.
//     Copyright Christopher Kormanyos 2024.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef MANDELBROT_GENERATOR_PERTURBATIVE_2024_04_28_H // NOLINT(llvm-header-guard)
  #define MANDELBROT_GENERATOR_PERTURBATIVE_2024_04_28_H

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
           typename IterateNumericType,
           const std::uint_fast32_t MaxIterations> class mandelbrot_generator_perturbative final // NOLINT(cppcoreguidelines-special-member-functions,hicpp-special-member-functions)
    : public mandelbrot_generator<CoordPntNumericType, IterateNumericType, MaxIterations>
  {
  private:
    using base_class_type = mandelbrot_generator<CoordPntNumericType, IterateNumericType, MaxIterations>;

    using mandelbrot_config_type = typename base_class_type::mandelbrot_config_type;

    using my_coord_pnt_numeric_type = typename base_class_type::my_coord_pnt_numeric_type;
    using my_iteration_numeric_type = typename base_class_type::my_iteration_numeric_type;

    static_assert(std::numeric_limits<my_iteration_numeric_type>::digits <= std::numeric_limits<my_coord_pnt_numeric_type>::digits,
                  "Error: The iteration precision must be less than or equal to the coordinate precision. Check config.");

  public:
    explicit mandelbrot_generator_perturbative(const mandelbrot_config_type& config)
      : base_class_type(config) { }

    mandelbrot_generator_perturbative() = delete;

    mandelbrot_generator_perturbative(const mandelbrot_generator_perturbative&) = delete;
    mandelbrot_generator_perturbative(mandelbrot_generator_perturbative&&) noexcept = delete;

    auto operator=(const mandelbrot_generator_perturbative&) -> mandelbrot_generator_perturbative& = delete;
    auto operator=(mandelbrot_generator_perturbative&&) noexcept -> mandelbrot_generator_perturbative& = delete;

    auto generate_mandelbrot_image_engine(std::vector<my_iteration_numeric_type>& x_coord,
                                          std::vector<my_iteration_numeric_type>& y_coord,
                                          mandelbrot_text_output_base& text_output) -> void override
    {
      std::vector<my_iteration_numeric_type> zkr(base_class_type::mandelbrot_config_object.max_iterations + static_cast<std::uint_fast32_t>(UINT8_C(1)));
      std::vector<my_iteration_numeric_type> zki(base_class_type::mandelbrot_config_object.max_iterations + static_cast<std::uint_fast32_t>(UINT8_C(1)));

      using std::floor;

      my_coord_pnt_numeric_type
        x_center
        {
          static_cast<my_coord_pnt_numeric_type>
          (
              (base_class_type::mandelbrot_config_object.x_lo() + base_class_type::mandelbrot_config_object.x_hi())
            / static_cast<my_coord_pnt_numeric_type>(UINT8_C(2))
          )
        };

      my_coord_pnt_numeric_type
        y_center
        {
          static_cast<my_coord_pnt_numeric_type>
          (
              (base_class_type::mandelbrot_config_object.y_lo() + base_class_type::mandelbrot_config_object.y_hi())
            / static_cast<my_coord_pnt_numeric_type>(UINT8_C(2))
          )
        };

      // Initialize the Zk-Components of the central point.
      // Assumption: The max iterations is reached.

      {
        zkr.front() = static_cast<my_iteration_numeric_type>(UINT8_C(0));
        zki.front() = static_cast<my_iteration_numeric_type>(UINT8_C(0));

        my_coord_pnt_numeric_type zr  { static_cast<my_coord_pnt_numeric_type>(UINT8_C(0)) };
        my_coord_pnt_numeric_type zi  { static_cast<my_coord_pnt_numeric_type>(UINT8_C(0)) };
        my_coord_pnt_numeric_type zr2 { static_cast<my_coord_pnt_numeric_type>(UINT8_C(0)) };
        my_coord_pnt_numeric_type zi2 { static_cast<my_coord_pnt_numeric_type>(UINT8_C(0)) };


        auto iteration_result = static_cast<std::uint_fast32_t>(UINT8_C(0));

        while ((iteration_result < base_class_type::max_iterations) && ((zr2 + zi2) < base_class_type::four_coord_pnt())) // NOLINT(altera-id-dependent-backward-branch)
        {
          // The inner loop performs optimized complex multiply and add.
          // This is the main work of the fractal iteration scheme.

          zi *= zr;

          zi += (zi + y_center);
          zr = (zr2 - zi2) + x_center;

          zr2 = zr * zr;
          zi2 = zi * zi;

          ++iteration_result;

          zkr[static_cast<std::size_t>(iteration_result)] = static_cast<my_iteration_numeric_type>(zr);
          zki[static_cast<std::size_t>(iteration_result)] = static_cast<my_iteration_numeric_type>(zi);
        }
      }

      // Initialize the x-y coordinates.
      {
        auto x_val(static_cast<my_iteration_numeric_type>(base_class_type::mandelbrot_config_object.x_lo() - x_center));
        auto y_val(static_cast<my_iteration_numeric_type>(base_class_type::mandelbrot_config_object.y_hi() - y_center));

        for (auto& x : x_coord) { x = x_val; x_val += static_cast<my_iteration_numeric_type>(base_class_type::mandelbrot_config_object.step_x()); }
        for (auto& y : y_coord) { y = y_val; y_val -= static_cast<my_iteration_numeric_type>(base_class_type::mandelbrot_config_object.step_y()); }
      }

      std::atomic_flag mandelbrot_iteration_lock { };

      std::size_t unordered_parallel_row_count { static_cast<std::size_t>(UINT8_C(0)) };

      my_concurrency::parallel_for
      (
        static_cast<std::size_t>(UINT8_C(0)),
        y_coord.size(),
        [&mandelbrot_iteration_lock, &unordered_parallel_row_count, &text_output, &x_coord, &y_coord, &zkr, &zki, this](std::size_t j_row)
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
            my_iteration_numeric_type er          { static_cast<unsigned>(UINT8_C(0)) };
            my_iteration_numeric_type ei          { static_cast<unsigned>(UINT8_C(0)) };
            my_iteration_numeric_type quad_length { static_cast<unsigned>(UINT8_C(0)) };
            my_iteration_numeric_type zer         { static_cast<unsigned>(UINT8_C(0)) };
            my_iteration_numeric_type zei         { static_cast<unsigned>(UINT8_C(0)) };
            my_iteration_numeric_type zkr_temp    { static_cast<unsigned>(UINT8_C(0)) };
            my_iteration_numeric_type zki_temp    { static_cast<unsigned>(UINT8_C(0)) };

            // Use an optimized complex-numbered multiplication scheme.
            // Thereby reduce the main work of the Mandelbrot iteration to
            // three real-valued multiplications and several real-valued
            // addition/subtraction operations.

            auto iteration_result = static_cast<std::uint_fast32_t>(UINT8_C(1));

            // Perform the iteration sequence for generating the Mandelbrot set.
            // Here is the main work of the program.

            while(   (iteration_result < (base_class_type::max_iterations + static_cast<std::uint_fast32_t>(UINT8_C(1)))) // NOLINT(altera-id-dependent-backward-branch)
                  && (quad_length < base_class_type::four_iteration()))                                                   // NOLINT(altera-id-dependent-backward-branch)
            {
              // The core functionality of the original formula is:
              //   z_{k+1} = z_{k}^2 + C

              // -> delta transformation z_{k+1} -> z_{k+1} + e_{k+1}; z_{k} -> z_{k} + e_{k}; C -> c + d;

              // Get it in to the formula we end with:
              //   z_{k+1} + e_{k+1} = z_{k} + c + e_{k}^2 + 2*z_{k}*e_{k} + d

              // This replaces the original formula, resulting in:
              //   e_{k+1} = e_{k}^2 + 2*z_{k}*e_{k} + d
              //   where z_{k} is the pre-calculated value.

              ei *= (er + zkr_temp);
              ei += (zki_temp * er);
              ei += ei + y_coord[j_row];
              er  = zer - zei + x_coord[i_col];

              zkr_temp = zkr[static_cast<std::size_t>(iteration_result)];
              zki_temp = zki[static_cast<std::size_t>(iteration_result)];

              zer  = er;
              zer *= (zkr_temp * static_cast<unsigned>(UINT8_C(2))) + er;

              zei  = ei;
              zei *= (zki_temp * static_cast<unsigned>(UINT8_C(2))) + ei;
              //2*er *t + er *er = er * (2*t + er)


              quad_length = (zer + (zkr_temp * zkr_temp)) + (zei + (zki_temp * zki_temp));

              // Note: zr2 = zr*zr; zi2 = zi*zi is OK-ish, if four is 400 with some inacuracy.

              ++iteration_result;
            }

            // The iterations are shifted by one, and need to be corrected down by one.
            // In order to achieve the same color scaling we subtract the last one.

            --iteration_result;

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

#endif // MANDELBROT_GENERATOR_PERTURBATIVE_2024_04_28_H
