///////////////////////////////////////////////////////////////////////////////
// Copyright Christopher Kormanyos 2015 - 2025.
// Distributed under the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt
// or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef MANDELBROT_COLOR_2015_06_15_H // NOLINT(llvm-header-guard)
  #define MANDELBROT_COLOR_2015_06_15_H

  #include <algorithm>
  #include <cmath>
  #include <cstdint>

  #if !defined(MANDELBROT_NODISCARD)
  #if defined(_MSC_VER) && !defined(__GNUC__)
  #define MANDELBROT_NODISCARD
  #else
  #if (defined(__cplusplus) && (__cplusplus >= 201703L))
  #define MANDELBROT_NODISCARD  [[nodiscard]] // NOLINT(cppcoreguidelines-macro-usage)
  #else
  #define MANDELBROT_NODISCARD
  #endif
  #endif
  #endif

  #if (!defined(_MSC_VER) && defined(__cplusplus) && (__cplusplus >= 201703L))
  namespace ckormanyos::mandelbrot::color {
  #else
  namespace ckormanyos { namespace mandelbrot { namespace color { // NOLINT(modernize-concat-nested-namespaces)
  #endif

  class color_stretch_base
  {
  public:
    // LCOV_EXCL_START
    color_stretch_base(const color_stretch_base&) = default;
    color_stretch_base(color_stretch_base&&) noexcept = default;

    auto operator=(const color_stretch_base&) -> color_stretch_base& = default;
    auto operator=(color_stretch_base&&) noexcept -> color_stretch_base& = default;
    // LCOV_EXCL_STOP

    virtual ~color_stretch_base() = default;

    auto init(const std::uint_fast32_t total_pixels) -> void
    {
      set_total_pixels(total_pixels);
      set_sum(static_cast<std::uint_fast32_t>(UINT8_C(0)));
    }

    virtual auto color_stretch(std::uint_fast32_t) -> std::uint_fast32_t = 0;

  protected:
    auto set_total_pixels(std::uint_fast32_t val) noexcept -> void { my_total_pixels = val; }
    auto set_sum         (std::uint_fast32_t val) noexcept -> void { my_sum = val; }

    MANDELBROT_NODISCARD auto get_total_pixels() const noexcept -> std::uint_fast32_t { return my_total_pixels; }
    MANDELBROT_NODISCARD auto get_sum         () const noexcept -> std::uint_fast32_t { return my_sum; }

    color_stretch_base() noexcept = default;

  private:
    std::uint_fast32_t my_total_pixels { }; // NOLINT(readability-identifier-naming)
    std::uint_fast32_t my_sum          { }; // NOLINT(readability-identifier-naming)
  };

  class color_stretch_histogram_method final : public color_stretch_base
  {
  public:
    color_stretch_histogram_method() noexcept = default;

    // LCOV_EXCL_START
    color_stretch_histogram_method(const color_stretch_histogram_method&) = default;
    color_stretch_histogram_method(color_stretch_histogram_method&&) noexcept = default;

    auto operator=(const color_stretch_histogram_method&) -> color_stretch_histogram_method& = default;
    auto operator=(color_stretch_histogram_method&&) noexcept -> color_stretch_histogram_method& = default;
    // LCOV_EXCL_STOP

    ~color_stretch_histogram_method() override = default;

    auto color_stretch(std::uint_fast32_t hist_entry_val) -> std::uint_fast32_t override
    {
      // Perform color stretching using the histogram approach.
      // Convert the histogram entries such that a given entry contains
      // the sum of its own entries plus all previous entries. This provides
      // a set of scale factors for the color. The histogram approach
      // automatically scales to the distribution of pixels in the image.

      std::uint_fast32_t sum { color_stretch_base::get_sum() };
      sum += hist_entry_val;

      color_stretch_base::set_sum(sum);

      const float sum_div_total_pixels
      {
        static_cast<float>(sum) / static_cast<float>(color_stretch_base::get_total_pixels())
      };

      using std::pow;

      return
        static_cast<std::uint_fast32_t>
        (
            static_cast<std::uint_fast32_t>(UINT8_C(255))
          - static_cast<std::uint_fast32_t>
            (
              static_cast<float>(pow(sum_div_total_pixels, 1.2F) * 255.0F) // NOLINT(cppcoreguidelines-avoid-magic-numbers,readability-magic-numbers)
            )
        );
    }
  };

  #if (!defined(_MSC_VER) && defined(__cplusplus) && (__cplusplus >= 201703L))
  } // namespace ckormanyos::mandelbrot::color
  #else
  } // namespace color
  } // namespace mandelbrot
  } // namespace ckormanyos
  #endif

#endif // MANDELBROT_COLOR_2015_06_15_H
