﻿///////////////////////////////////////////////////////////////////////////////
// Copyright Christopher Kormanyos 2024 - 2025.
// Distributed under the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt
// or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef MANDELBROT_TEXT_OUTPUT_2024_04_14_H // NOLINT(llvm-header-guard)
  #define MANDELBROT_TEXT_OUTPUT_2024_04_14_H

  #include <cstddef>
  #include <iostream>
  #include <string>

  #if (!defined(_MSC_VER) && defined(__cplusplus) && (__cplusplus >= 201703L))
  namespace ckormanyos::mandelbrot {
  #else
  namespace ckormanyos { namespace mandelbrot {
  #endif

  class mandelbrot_text_output_base // NOLINT(cppcoreguidelines-special-member-functions,hicpp-special-member-functions)
  {
  public:
    virtual ~mandelbrot_text_output_base() = default;

    virtual auto write(const std::string&) -> bool = 0;

  protected:
    using callback_function_type = auto(*)(const std::string&) -> bool;

    mandelbrot_text_output_base() = default;
  };

  class mandelbrot_text_output_cout : public mandelbrot_text_output_base // NOLINT(cppcoreguidelines-special-member-functions,hicpp-special-member-functions)
  {
  public:
    ~mandelbrot_text_output_cout() override = default;

    auto write(const std::string& str_to_write) -> bool override
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
