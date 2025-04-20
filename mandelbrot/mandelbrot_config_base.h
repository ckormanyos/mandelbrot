///////////////////////////////////////////////////////////////////////////////
// Copyright Christopher Kormanyos 2015 - 2025.
// Copyright Sebastian Streubel 2024.
// Distributed under the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt
// or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef MANDELBROT_CONFIG_BASE_2015_06_15_H // NOLINT(llvm-header-guard)
  #define MANDELBROT_CONFIG_BASE_2015_06_15_H

  #include <cstddef>
  #include <cstdint>

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

  #if(__cplusplus >= 201703L)
  } // namespace ckormanyos::mandelbrot
  #else
  } // namespace mandelbrot
  } // namespace ckormanyos
  #endif

#endif // MANDELBROT_CONFIG_BASE_2015_06_15_H
