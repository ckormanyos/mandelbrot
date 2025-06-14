///////////////////////////////////////////////////////////////////////////////
// Copyright Christopher Kormanyos 2024 - 2025.
// Distributed under the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt
// or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef MANDELBROT_TEXT_OUTPUT_2024_04_14_H // NOLINT(llvm-header-guard)
  #define MANDELBROT_TEXT_OUTPUT_2024_04_14_H

  #include <mandelbrot/cfg/mandelbrot_cfg_forward.h>

  #include <cstddef>
  #include <iostream>
  #include <string>

  #if (!defined(_MSC_VER) && defined(__cplusplus) && (__cplusplus >= 201703L))
  namespace ckormanyos::mandelbrot {
  #else
  namespace ckormanyos { namespace mandelbrot {
  #endif

  class mandelbrot_text_output_base
  {
  public:
    mandelbrot_text_output_base(const mandelbrot_text_output_base&) = delete;
    mandelbrot_text_output_base(mandelbrot_text_output_base&&) noexcept = delete;

    auto operator=(const mandelbrot_text_output_base&) -> mandelbrot_text_output_base& = delete;
    auto operator=(mandelbrot_text_output_base&&) noexcept -> mandelbrot_text_output_base& = delete;

    virtual ~mandelbrot_text_output_base() = default;

    MANDELBROT_NODISCARD virtual auto write(const std::string&) const -> bool = 0;

  protected:
    using callback_function_type = auto(*)(const std::string&) -> bool;

    mandelbrot_text_output_base() = default;
  };

  class mandelbrot_text_output_cout final : public mandelbrot_text_output_base
  {
  public:
    mandelbrot_text_output_cout() = default;

    mandelbrot_text_output_cout(const mandelbrot_text_output_cout&) = delete;
    mandelbrot_text_output_cout(mandelbrot_text_output_cout&&) noexcept = delete;

    auto operator=(const mandelbrot_text_output_cout&) -> mandelbrot_text_output_cout& = delete;
    auto operator=(mandelbrot_text_output_cout&&) noexcept -> mandelbrot_text_output_cout& = delete;

    ~mandelbrot_text_output_cout() override = default;

    MANDELBROT_NODISCARD auto write(const std::string& str_to_write) const -> bool override
    {
      std::cout << str_to_write;

      return true;
    }
  };

  #if (!defined(_MSC_VER) && defined(__cplusplus) && (__cplusplus >= 201703L))
  } // namespace ckormanyos::mandelbrot
  #else
  } // namespace mandelbrot
  } // namespace ckormanyos
  #endif

#endif // MANDELBROT_TEXT_OUTPUT_2024_04_14_H
