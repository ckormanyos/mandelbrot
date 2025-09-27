///////////////////////////////////////////////////////////////////////////////
// Copyright Christopher Kormanyos 2015 - 2025.
// Distributed under the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt
// or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef MANDELBROT_MANDELBROT_COLOR_FUNCTIONS_H
  #define MANDELBROT_MANDELBROT_COLOR_FUNCTIONS_H

  #include <algorithm>
  #include <cmath>
  #include <cstdint>
  #if (defined(__cpp_lib_math_constants) && (__cpp_lib_math_constants >= 201907L))
  #include <numbers>
  #endif

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

  class color_functions_base
  {
  public:
    // LCOV_EXCL_START
    color_functions_base(const color_functions_base&) = default;
    color_functions_base(color_functions_base&&) noexcept = default;

    auto operator=(const color_functions_base&) -> color_functions_base& = default;
    auto operator=(color_functions_base&&) noexcept -> color_functions_base& = default;
    // LCOV_EXCL_STOP

    virtual ~color_functions_base() = default;

    MANDELBROT_NODISCARD virtual auto color_function_r(const std::uint_fast32_t&) const -> std::uint_fast32_t = 0;
    MANDELBROT_NODISCARD virtual auto color_function_g(const std::uint_fast32_t&) const -> std::uint_fast32_t = 0;
    MANDELBROT_NODISCARD virtual auto color_function_b(const std::uint_fast32_t&) const -> std::uint_fast32_t = 0;

  protected:
    color_functions_base() = default;

    static auto color_phaser_01(std::uint_fast32_t c) -> std::uint_fast32_t
    {
      #if (defined(__cpp_lib_math_constants) && (__cpp_lib_math_constants >= 201907L))
      constexpr float val_pi { std::numbers::pi_v<float> };
      #else
      constexpr float val_pi { 3.1415926535897932385F };
      #endif

      const float
        color_phase
        {
            (static_cast<float>(c) / 255.0F)
          *  static_cast<float>(val_pi * 8.0F)
        };

      using std::sin;

      const float
        my_color
        {
          (std::max)
          (
            static_cast<float>((sin(color_phase) / 2.0F) + 0.5F),
            0.0F
          )
        };

      return static_cast<std::uint_fast32_t>(float { my_color * 255.0F }); // NOLINT(cppcoreguidelines-avoid-magic-numbers,readability-magic-numbers)
    }
  };

  class color_functions_bw final : public color_functions_base
  {
  public:
    color_functions_bw() = default;

    // LCOV_EXCL_START
    color_functions_bw(const color_functions_bw&) = default;
    color_functions_bw(color_functions_bw&&) noexcept = default;

    auto operator=(const color_functions_bw&) -> color_functions_bw& = default;
    auto operator=(color_functions_bw&&) noexcept -> color_functions_bw& = default;
    // LCOV_EXCL_STOP

    ~color_functions_bw() override = default;

  private:
    MANDELBROT_NODISCARD auto color_function_r(const std::uint_fast32_t& c) const -> std::uint_fast32_t override { return color_phaser_01(c); }
    MANDELBROT_NODISCARD auto color_function_g(const std::uint_fast32_t& c) const -> std::uint_fast32_t override { return color_phaser_01(c); }
    MANDELBROT_NODISCARD auto color_function_b(const std::uint_fast32_t& c) const -> std::uint_fast32_t override { return color_phaser_01(c); }
  };

  // LCOV_EXCL_START
  class color_functions_pretty final : public color_functions_base
  {
  public:
    color_functions_pretty() = default;

    color_functions_pretty(const color_functions_pretty&) = default;
    color_functions_pretty(color_functions_pretty&&) noexcept = default;

    auto operator=(const color_functions_pretty&) -> color_functions_pretty& = default;
    auto operator=(color_functions_pretty&&) noexcept -> color_functions_pretty& = default;

    ~color_functions_pretty() override = default;

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
            (static_cast<float>(c) / 255.0F) // NOLINT(cppcoreguidelines-avoid-magic-numbers,readability-magic-numbers)
          * (static_cast<float>(c) /   1.0F)
        );
    }
  };
  // LCOV_EXCL_STOP

  #if (!defined(_MSC_VER) && defined(__cplusplus) && (__cplusplus >= 201703L))
  } // namespace ckormanyos::mandelbrot::color
  #else
  } // namespace color
  } // namespace mandelbrot
  } // namespace ckormanyos
  #endif

#endif // MANDELBROT_MANDELBROT_COLOR_FUNCTIONS_H
