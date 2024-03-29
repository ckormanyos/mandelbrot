﻿///////////////////////////////////////////////////////////////////////////////
//      Copyright Christopher Kormanyos 2015 - 2023.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef MANDELBROT_COLOR_2015_06_15_H // NOLINT(llvm-header-guard)
  #define MANDELBROT_COLOR_2015_06_15_H

  #include <cmath>
  #include <cstddef>
  #include <cstdint>

  #if(__cplusplus >= 201703L)
  namespace ckormanyos::mandelbrot::color {
  #else
  namespace ckormanyos { namespace mandelbrot { namespace color { // NOLINT(modernize-concat-nested-namespaces)
  #endif

  class color_functions_base
  {
  public:
    color_functions_base() = default;

    color_functions_base(const color_functions_base&) = default;
    color_functions_base(color_functions_base&&) noexcept = default;

    auto operator=(const color_functions_base&) -> color_functions_base& = default;
    auto operator=(color_functions_base&&) noexcept -> color_functions_base& = default;

    virtual ~color_functions_base() = default;

    MANDELBROT_NODISCARD virtual auto color_function_r(const std::uint_fast32_t&) const -> std::uint_fast32_t = 0;
    MANDELBROT_NODISCARD virtual auto color_function_g(const std::uint_fast32_t&) const -> std::uint_fast32_t = 0;
    MANDELBROT_NODISCARD virtual auto color_function_b(const std::uint_fast32_t&) const -> std::uint_fast32_t = 0;

  protected:
    static auto color_phaser_01(std::uint_fast32_t c) -> std::uint_fast32_t
    {
      const auto color_phase =
        static_cast<float>
        (
            static_cast<float>(static_cast<float>(c) / 255.0F)
          * static_cast<float>(3.1415926535897932385F * 8.0F)
        );

      {
        using std::sin;

        const auto my_color =
          static_cast<float>
          (
            static_cast<float>(sin(color_phase) / 2.0F) + 0.5F
          );

        return static_cast<std::uint_fast32_t>(my_color * 255.0F); // NOLINT(cppcoreguidelines-avoid-magic-numbers,readability-magic-numbers)
      }
    }
  };

  class color_functions_bw final : public color_functions_base
  {
  public:
    color_functions_bw() = default;

    color_functions_bw(const color_functions_bw&) = default;
    color_functions_bw(color_functions_bw&&) noexcept = default;

    auto operator=(const color_functions_bw&) -> color_functions_bw& = default;
    auto operator=(color_functions_bw&&) noexcept -> color_functions_bw& = default;

    ~color_functions_bw() override = default;

  private:
    MANDELBROT_NODISCARD auto color_function_r(const std::uint_fast32_t& c) const -> std::uint_fast32_t override { return color_phaser_01(c); }
    MANDELBROT_NODISCARD auto color_function_g(const std::uint_fast32_t& c) const -> std::uint_fast32_t override { return color_phaser_01(c); }
    MANDELBROT_NODISCARD auto color_function_b(const std::uint_fast32_t& c) const -> std::uint_fast32_t override { return color_phaser_01(c); }
  };

  class color_functions_pretty final : public color_functions_base
  {
  public:
    color_functions_pretty() = default;

    color_functions_pretty(const color_functions_pretty&) = default;
    color_functions_pretty(color_functions_pretty&&) noexcept = default;

    ~color_functions_pretty() override = default;

    auto operator=(const color_functions_pretty&) -> color_functions_pretty& = default;
    auto operator=(color_functions_pretty&&) noexcept -> color_functions_pretty& = default;

  private:
    MANDELBROT_NODISCARD auto color_function_r(const std::uint_fast32_t& c) const -> std::uint_fast32_t override
    {
      return color_phaser_01(c);
    }

    MANDELBROT_NODISCARD auto color_function_g(const std::uint_fast32_t& c) const -> std::uint_fast32_t override
    {
      return c;
    }

    MANDELBROT_NODISCARD auto color_function_b(const std::uint_fast32_t& c) const -> std::uint_fast32_t override
    {
      return
        static_cast<std::uint_fast32_t>
        (
          static_cast<float>
          (
              static_cast<float>(static_cast<float>(c)  / 255.0F) // NOLINT(cppcoreguidelines-avoid-magic-numbers,readability-magic-numbers)
            * static_cast<float>(static_cast<float>(c)  /   1.0F)
          )
        );
    }
  };

  class color_stretch_base
  {
  public:
    color_stretch_base() = default;

    color_stretch_base(const color_stretch_base& other) = default;

    color_stretch_base(color_stretch_base&& other) noexcept
      : my_total_pixels(other.my_total_pixels),
        my_sum         (other.my_sum) { }

    virtual ~color_stretch_base() = default;

    auto operator=(const color_stretch_base& other) -> color_stretch_base&
    {
      if(this != &other)
      {
        my_total_pixels = other.my_total_pixels;
        my_sum          = other.my_sum;
      }

      return *this;
    }

    auto operator=(color_stretch_base&& other) noexcept -> color_stretch_base&
    {
      my_total_pixels = other.my_total_pixels;
      my_sum          = other.my_sum;

      return *this;
    }

    auto init(const std::uint_fast32_t total_pixels) const -> void
    {
      my_total_pixels = total_pixels;
      my_sum          = 0U;
    }

    virtual auto color_stretch(std::uint_fast32_t&) const -> void = 0; // NOLINT(google-runtime-references)

  protected:
    mutable std::uint_fast32_t my_total_pixels { }; // NOLINT(cppcoreguidelines-non-private-member-variables-in-classes,misc-non-private-member-variables-in-classes,readability-identifier-naming)
    mutable std::uint_fast32_t my_sum { };          // NOLINT(cppcoreguidelines-non-private-member-variables-in-classes,misc-non-private-member-variables-in-classes,readability-identifier-naming)
  };

  class color_stretch_histogram_method final : public color_stretch_base
  {
  public:
    color_stretch_histogram_method() = default;

    color_stretch_histogram_method(const color_stretch_histogram_method& other)
      : color_stretch_base(static_cast<const color_stretch_base&>(other)) { }

    color_stretch_histogram_method(color_stretch_histogram_method&& other) noexcept
      : color_stretch_base(static_cast<color_stretch_base&&>(other)) { }

    ~color_stretch_histogram_method() override = default;

    auto operator=(const color_stretch_histogram_method& other) -> color_stretch_histogram_method&
    {
      if(this != &other)
      {
        static_cast<void>(color_stretch_base::operator=(static_cast<const color_stretch_base&>(other)));
      }

      return *this;
    }

    auto operator=(color_stretch_histogram_method&& other) noexcept -> color_stretch_histogram_method&
    {
      static_cast<void>(color_stretch_base::operator=(static_cast<color_stretch_base&&>(other)));

      return *this;
    }

    auto color_stretch(std::uint_fast32_t& histogram_entry) const -> void override
    {
      // Perform color stretching using the histogram approach.
      // Convert the histogram entries such that a given entry contains
      // the sum of its own entries plus all previous entries. This provides
      // a set of scale factors for the color. The histogram approach
      // automatically scales to the distribution of pixels in the image.

      my_sum += histogram_entry;

      const auto sum_div_total_pixels =
        static_cast<float>
        (
          static_cast<float>(my_sum) / static_cast<float>(my_total_pixels)
        );

      {
        using std::pow;

        const auto histogram_scale = pow(sum_div_total_pixels, 1.2);

        const auto scaled_histogram_value =
          static_cast<std::uint_fast32_t>
          (
            static_cast<float>(histogram_scale * 255.0F)
          );

        histogram_entry =
          static_cast<std::uint_fast32_t>
          (
            UINT32_C(255) - scaled_histogram_value
          );
      }
    }
  };

  #if(__cplusplus >= 201703L)
  } // namespace ckormanyos::mandelbrot::color
  #else
  } // namespace color
  } // namespace mandelbrot
  } // namespace ckormanyos
  #endif

#endif // MANDELBROT_COLOR_2015_06_15_H
