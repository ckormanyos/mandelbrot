///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2013 - 2024.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef STOPWATCH_2024_03_28_H
  #define STOPWATCH_2024_03_28_H

  #include <chrono>

  template <class clock_type>
  struct stopwatch
  {
  public:
    using duration_type = typename clock_type::duration;

    stopwatch() : m_start(clock_type::now()) { }

    stopwatch(const stopwatch& other) : m_start(other.m_start) { }
    stopwatch(stopwatch&& other) noexcept : m_start(other.m_start) { }

    auto operator=(const stopwatch& other) -> stopwatch&
    {
      if(this != &other)
      {
        m_start = other.m_start;
      }

      return *this;
    }

    auto operator=(stopwatch&& other) noexcept -> stopwatch&
    {
      m_start = other.m_start;

      return *this;
    }

    ~stopwatch() { }

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
    typename clock_type::time_point m_start;

    auto elapsed() const -> duration_type
    {
      return (clock_type::now() - m_start);
    }
  };

#endif // STOPWATCH_2024_03_28_H
