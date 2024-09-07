///////////////////////////////////////////////////////////////////////////////
// Copyright Christopher Kormanyos 2024.
// Distributed under the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt
// or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef UTILITY_2024_04_14_H
  #define UTILITY_2024_04_14_H

  #include <mandelbrot/text_output.h>

  #include <cstddef>

  namespace util::utility
  {
    constexpr std::size_t strlen(const char* start)
    {
      const char* end = start;

      while (*end != '\0')
      {
        ++end;
      }

      return end - start;
    }

    template<typename input_iterator1,
              typename input_iterator2>
    constexpr auto equal(input_iterator1 first1, input_iterator1 last1, input_iterator2 first2) -> bool
    {
      while((first1 != last1) && (*first1 == *first2))
      {
        ++first1;
        ++first2;
      }

      return { first1 == last1 };
    }
  } // namespace util::utility

  namespace util::text
  {
    class text_output_alloc_console : public ckormanyos::mandelbrot::text_output_base // NOLINT(cppcoreguidelines-special-member-functions,hicpp-special-member-functions)
    {
    public:
      explicit text_output_alloc_console(callback_function_type cbk) : my_callback { cbk } { }

      text_output_alloc_console() = delete;

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

#endif // UTILITY_2024_04_14_H
