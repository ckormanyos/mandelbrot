///////////////////////////////////////////////////////////////////////////////
//      Copyright Christopher Kormanyos 2024.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef TEXT_2024_04_16_H // NOLINT(llvm-header-guard)
  #define TEXT_2024_04_16_H

  #include <mandelbrot/mandelbrot_text_output.h>

  #include <windows.h>

  #include <cstddef>
  #include <string>

  namespace util::text {

  class text_output_alloc_console : public ckormanyos::mandelbrot::mandelbrot_text_output_base // NOLINT(cppcoreguidelines-special-member-functions,hicpp-special-member-functions)
  {
  public:
    using callback_function_type = bool(*)(const std::string&);

    text_output_alloc_console(callback_function_type cbk) : my_callback(cbk) { }

    ~text_output_alloc_console() override = default;

    auto write(const std::string& str_to_write) -> bool override
    {
      my_callback(str_to_write);

      return true;
    }

  private:
    callback_function_type my_callback { nullptr };
  };

  } // namespace util::text

#endif // TEXT_2024_04_16_H
