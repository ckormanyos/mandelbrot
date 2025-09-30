///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2013 - 2025.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef CONCURRENCY_STOPWATCH_H
  #define CONCURRENCY_STOPWATCH_H

  #include <chrono>
  #include <cstdint>

  #if (defined(_MSC_VER) && defined(_MSVC_LANG))
  #define STOPWATCH_CXX_VERSION _MSVC_LANG
  #elif defined(__cplusplus)
  #define STOPWATCH_CXX_VERSION __cplusplus // NOLINT(cppcoreguidelines-macro-usage)
  #endif

  #if !defined(STOPWATCH_CXX_VERSION)
  #error Error: can't determine C++ version STOPWATCH_CXX_VERSION
  #endif

  #if defined(_MSC_VER) && !defined(__GNUC__)
  #define STOPWATCH_NODISCARD
  #else
  #if (defined(STOPWATCH_CXX_VERSION) && (STOPWATCH_CXX_VERSION >= 201703L))
  #define STOPWATCH_NODISCARD  [[nodiscard]] // NOLINT(cppcoreguidelines-macro-usage)
  #else
  #define STOPWATCH_NODISCARD
  #endif
  #endif

  namespace concurrency {

  template<typename ClockType>
  struct stopwatch
  {
  private:
    using local_clock_type = ClockType;

  public:
    stopwatch()
    {
      reset();
    }

    auto reset() -> void
    {
      m_start = local_clock_type::now();
    }

    template<typename RepresentationRequestedTimeType>
    STOPWATCH_NODISCARD static auto elapsed_time(const stopwatch& my_stopwatch) noexcept -> RepresentationRequestedTimeType
    {
      using local_time_type = RepresentationRequestedTimeType;

      const auto my_now = local_clock_type::now();

      const local_time_type ns_duration { static_cast<local_time_type>(std::chrono::duration_cast<std::chrono::nanoseconds>(my_now - my_stopwatch.m_start).count()) };

      return ns_duration / local_time_type { UINTMAX_C(1000000000) };
    }

  private:
    using time_point_type = typename local_clock_type::time_point;

    time_point_type m_start { }; // NOLINT(readability-identifier-naming)
  };

  } // namespace concurrency

#endif // CONCURRENCY_STOPWATCH_H
