///////////////////////////////////////////////////////////////////////////////
// Copyright Christopher Kormanyos 2015 - 2025.
// Distributed under the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt
// or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef MANDELBROT_COLOR_2015_06_15_H // NOLINT(llvm-header-guard)
  #define MANDELBROT_COLOR_2015_06_15_H

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

  class color_functions_base // NOLINT(cppcoreguidelines-special-member-functions,hicpp-special-member-functions)
  {
  public:
    virtual ~color_functions_base() = default; // LCOV_EXCL_LINE

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
            (std::max)(static_cast<float>(static_cast<float>(sin(color_phase) / 2.0F) + 0.5F), 0.0F)
          );

        return static_cast<std::uint_fast32_t>(my_color * 255.0F); // NOLINT(cppcoreguidelines-avoid-magic-numbers,readability-magic-numbers)
      }
    }
  };

  class color_functions_bw final : public color_functions_base
  {
  private:
    MANDELBROT_NODISCARD auto color_function_r(const std::uint_fast32_t& c) const -> std::uint_fast32_t override { return color_phaser_01(c); }
    MANDELBROT_NODISCARD auto color_function_g(const std::uint_fast32_t& c) const -> std::uint_fast32_t override { return color_phaser_01(c); }
    MANDELBROT_NODISCARD auto color_function_b(const std::uint_fast32_t& c) const -> std::uint_fast32_t override { return color_phaser_01(c); }
  };

  class color_functions_pretty final : public color_functions_base // NOLINT(cppcoreguidelines-special-member-functions,hicpp-special-member-functions)
  {
  public:
    ~color_functions_pretty() override = default; // LCOV_EXCL_LINE

  private:
    // LCOV_EXCL_START
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
    // LCOV_EXCL_STOP
  };

  class color_stretch_base // NOLINT(cppcoreguidelines-special-member-functions,hicpp-special-member-functions)
  {
  public:
    virtual ~color_stretch_base() = default; // LCOV_EXCL_LINE

    auto init(const std::uint_fast32_t total_pixels) const -> void
    {
      my_total_pixels = total_pixels;
      my_sum          = static_cast<std::uint_fast32_t>(UINT8_C(0));
    }

    virtual auto color_stretch(std::uint_fast32_t&) const -> void = 0; // NOLINT(google-runtime-references)

  protected:
    mutable std::uint_fast32_t my_total_pixels { }; // NOLINT(cppcoreguidelines-non-private-member-variables-in-classes,misc-non-private-member-variables-in-classes,readability-identifier-naming)
    mutable std::uint_fast32_t my_sum          { }; // NOLINT(cppcoreguidelines-non-private-member-variables-in-classes,misc-non-private-member-variables-in-classes,readability-identifier-naming)
  };

  class color_stretch_histogram_method final : public color_stretch_base // NOLINT(cppcoreguidelines-special-member-functions,hicpp-special-member-functions)
  {
  public:
    ~color_stretch_histogram_method() override = default; // LCOV_EXCL_LINE

    auto color_stretch(std::uint_fast32_t& histogram_entry) const -> void override
    {
      // Perform color stretching using the histogram approach.
      // Convert the histogram entries such that a given entry contains
      // the sum of its own entries plus all previous entries. This provides
      // a set of scale factors for the color. The histogram approach
      // automatically scales to the distribution of pixels in the image.

      my_sum += histogram_entry;

      const float sum_div_total_pixels
      {
        static_cast<float>(my_sum) / static_cast<float>(my_total_pixels)
      };

      using std::pow;

      histogram_entry =
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
