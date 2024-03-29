///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2013 - 2024.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef STOPWATCH_2024_03_28_H // NOLINT(llvm-header-guard)
  #define STOPWATCH_2024_03_28_H

  #if defined(_MSC_VER) && !defined(__GNUC__)
  #define STOPWATCH_NODISCARD
  #else
  #if (defined(__cplusplus) && (__cplusplus >= 201703L))
  #define STOPWATCH_NODISCARD  [[nodiscard]] // NOLINT(cppcoreguidelines-macro-usage)
  #else
  #define STOPWATCH_NODISCARD
  #endif
  #endif

  #include <chrono>

  template <class clock_type>
  struct stopwatch
  {
  public:
    using duration_type = typename clock_type::duration;

    auto reset() -> void
    {
      m_start = clock_type::now();
    }

    template<typename RepresentationRequestedType>
    static auto elapsed_time(const stopwatch& my_stopwatch) noexcept -> RepresentationRequestedType
    {
      return std::chrono::duration_cast<std::chrono::duration<float>>(my_stopwatch.elapsed()).count();
    }

  private:
    typename clock_type::time_point m_start { clock_type::now() }; // NOLINT(readability-identifier-naming)

    STOPWATCH_NODISCARD auto elapsed() const -> duration_type
    {
      return (clock_type::now() - m_start);
    }
  };

#endif // STOPWATCH_2024_03_28_H
