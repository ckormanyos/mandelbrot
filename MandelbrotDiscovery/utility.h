///////////////////////////////////////////////////////////////////////////////
// Copyright Christopher Kormanyos 2024.
// Distributed under the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt
// or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef UTILITY_2024_04_14_H
  #define UTILITY_2024_04_14_H

  #include <mandelbrot/text_output.h>

  #if(__cplusplus >= 201703L)
  namespace util::utility {
  #else
  namespace util { namespace utility { // NOLINT(modernize-concat-nested-namespaces)
  #endif

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

  #if(__cplusplus >= 201703L)
  } // namespace util::utility
  #else
  } // namespace utility
  } // namespace util
  #endif

  #if(__cplusplus >= 201703L)
  namespace util::text {
  #else
  namespace util { namespace text { // NOLINT(modernize-concat-nested-namespaces)
  #endif

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

  #if(__cplusplus >= 201703L)
  } // namespace util::text
  #else
  } // namespace text
  } // namespace util
  #endif

#endif // UTILITY_2024_04_14_H
