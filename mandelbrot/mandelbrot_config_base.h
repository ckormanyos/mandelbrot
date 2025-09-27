///////////////////////////////////////////////////////////////////////////////
// Copyright Christopher Kormanyos 2015 - 2025.
// Copyright Sebastian Streubel 2024.
// Distributed under the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt
// or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef MANDELBROT_MANDELBROT_CONFIG_BASE_H
  #define MANDELBROT_MANDELBROT_CONFIG_BASE_H

  #include <cstddef>
  #include <cstdint>
  #include <utility>

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

    explicit mandelbrot_config_base(const my_coord_pnt_numeric_type& x_lo_in, // NOLINT(bugprone-easily-swappable-parameters,modernize-pass-by-value)
                                    const my_coord_pnt_numeric_type& x_hi_in, // NOLINT(bugprone-easily-swappable-parameters,modernize-pass-by-value)
                                    const my_coord_pnt_numeric_type& y_lo_in, // NOLINT(bugprone-easily-swappable-parameters,modernize-pass-by-value)
                                    const my_coord_pnt_numeric_type& y_hi_in, // NOLINT(bugprone-easily-swappable-parameters,modernize-pass-by-value)
                                    const std::uint_fast32_t  iter)
      : my_x_lo  { x_lo_in },
        my_x_hi  { x_hi_in },
        my_y_lo  { y_lo_in },
        my_y_hi  { y_hi_in },
        my_width { std::move(my_x_hi - my_x_lo) },
        my_height{ std::move(my_y_hi - my_y_lo) },
        my_iter  { iter } { }

    virtual ~mandelbrot_config_base() = default;

    auto operator=(const mandelbrot_config_base& other) -> mandelbrot_config_base& = default;

    auto operator=(mandelbrot_config_base&& other) noexcept -> mandelbrot_config_base& = default;

    MANDELBROT_NODISCARD auto x_lo() const -> const my_coord_pnt_numeric_type& { return my_x_lo; }
    MANDELBROT_NODISCARD auto x_hi() const -> const my_coord_pnt_numeric_type& { return my_x_hi; }
    MANDELBROT_NODISCARD auto y_lo() const -> const my_coord_pnt_numeric_type& { return my_y_lo; }
    MANDELBROT_NODISCARD auto y_hi() const -> const my_coord_pnt_numeric_type& { return my_y_hi; }

    MANDELBROT_NODISCARD auto get_width () const -> const my_coord_pnt_numeric_type& { return my_width; }
    MANDELBROT_NODISCARD auto get_height() const -> const my_coord_pnt_numeric_type& { return my_height; }

    MANDELBROT_NODISCARD virtual auto step_x() const -> const my_coord_pnt_numeric_type& = 0;
    MANDELBROT_NODISCARD virtual auto step_y() const -> const my_coord_pnt_numeric_type& = 0;

    MANDELBROT_NODISCARD auto integral_width() const -> std::uint_fast32_t
    {
      return integral_convert(my_width, this->step_x());
    }

    MANDELBROT_NODISCARD auto integral_height() const -> std::uint_fast32_t
    {
      return integral_convert(my_height, this->step_y());
    }

    MANDELBROT_NODISCARD auto get_iterations() const noexcept -> std::uint_fast32_t { return my_iter; }

  private:
    const my_coord_pnt_numeric_type my_x_lo   { };
    const my_coord_pnt_numeric_type my_x_hi   { };
    const my_coord_pnt_numeric_type my_y_lo   { };
    const my_coord_pnt_numeric_type my_y_hi   { };
    const my_coord_pnt_numeric_type my_width  { };
    const my_coord_pnt_numeric_type my_height { };
    const std::uint_fast32_t        my_iter   { }; // NOLINT(readability-identifier-naming)

    MANDELBROT_NODISCARD static auto integral_convert(const my_coord_pnt_numeric_type& my_val, const my_coord_pnt_numeric_type& my_step) -> std::uint_fast32_t
    {
      const auto non_rounded_val2 =
        static_cast<std::uint_fast32_t>
        (
          my_coord_pnt_numeric_type(my_val * std::uint_fast32_t { UINT8_C(2) }) / my_step
        );

      return (non_rounded_val2 + std::uint_fast32_t { UINT8_C(1) }) / std::uint_fast32_t { UINT8_C(2) };
    }
  };

  #if(__cplusplus >= 201703L)
  } // namespace ckormanyos::mandelbrot
  #else
  } // namespace mandelbrot
  } // namespace ckormanyos
  #endif

#endif // MANDELBROT_MANDELBROT_CONFIG_BASE_H
