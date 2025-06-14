///////////////////////////////////////////////////////////////////////////////
// Copyright Christopher Kormanyos 2024 - 2025.
// Distributed under the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt
// or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef UTILITY_2024_04_14_H
  #define UTILITY_2024_04_14_H

  #include <mandelbrot/mandelbrot_text_output.h>

  #include <cstddef>
  #include <functional>
  #include <tuple>
  #include <utility>

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
    class text_output_alloc_console final : public ckormanyos::mandelbrot::mandelbrot_text_output_base
    {
    public:
      explicit text_output_alloc_console(callback_function_type cbk) : my_callback { cbk } { }

      text_output_alloc_console() = delete;

      text_output_alloc_console(const text_output_alloc_console&) = delete;
      text_output_alloc_console(text_output_alloc_console&&) noexcept = delete;

      auto operator=(const text_output_alloc_console&) -> text_output_alloc_console& = delete;
      auto operator=(text_output_alloc_console&&) noexcept -> text_output_alloc_console& = delete;

      ~text_output_alloc_console() override = default;

      MANDELBROT_NODISCARD auto write(const std::string& str_to_write) const -> bool override
      {
        my_callback(str_to_write);

        return true;
      }

    private:
      const callback_function_type my_callback { nullptr };
    };
  } // namespace util::text

  namespace util::caller
  {
    // Helper function to call a function on each element of a tuple.
    // See also: https://godbolt.org/z/bxYdsc7W6

    template <std::size_t tuple_elem_index = 0, typename Func, typename... Ts>
    void for_each_in_tuple(std::tuple<Ts...>& tuple_pack, Func&& func)
    {
      if constexpr (tuple_elem_index < sizeof...(Ts))
      {
        // Call the function with the current tuple element.
        func(std::get<tuple_elem_index>(tuple_pack));

        // Use a recursive call for the next element.
        for_each_in_tuple<tuple_elem_index + 1>(tuple_pack, std::forward<Func>(func));
      }
    }
  } // namespace util::caller

#endif // UTILITY_2024_04_14_H
