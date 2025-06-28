///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2017 - 2025.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef CONCURRENCY_PARALLEL_FOR_H
  #define CONCURRENCY_PARALLEL_FOR_H

  #include <algorithm>
  #include <cmath>
  #include <thread>
  #include <vector>

  namespace my_concurrency
  {
    template<typename index_type,
             typename callable_function_type>
    auto parallel_for(index_type             first,
                      index_type             last,
                      callable_function_type parallel_function) -> void
    {
      // Estimate the number of threads available.
      const auto number_of_threads_hint =
        static_cast<signed>
        (
          std::thread::hardware_concurrency()
        );

      const auto number_of_threads = // NOLINT(altera-id-dependent-backward-branch)
        static_cast<unsigned>
        (
          (std::max)
          (
            static_cast<signed>(number_of_threads_hint - static_cast<signed>(UINT8_C(1))),
            static_cast<signed>(INT8_C(1))
          )
        );

      using thread_vector_type = std::vector<std::thread>;

      // Create the thread pool and launch the jobs.
      thread_vector_type pool { };

      pool.reserve(static_cast<typename thread_vector_type::size_type>(number_of_threads));

      {
        // Inner loop.
        const auto launch_nth =
          [&parallel_function](index_type offset, index_type nth, index_type total_lines) // NOLINT(bugprone-easily-swappable-parameters)
          {
            for(auto idx = static_cast<index_type>(0U); idx < total_lines; ++idx) // NOLINT(altera-id-dependent-backward-branch)
            {
              parallel_function(static_cast<index_type>(idx * nth) + offset );
            }
          };

        {
          // Set the size (distance) for the range functions.
          const auto n_distance =
            static_cast<index_type>
            (
              static_cast<index_type>(last - first)
            );

          using std::floor;

          const auto slice =
            (std::max)
            (
              static_cast<index_type>(floor(static_cast<float>(n_distance) / static_cast<float>(number_of_threads))),
              static_cast<index_type>(1)
            );

          for(auto   idx = static_cast<index_type>(0);
                     idx < static_cast<index_type>(number_of_threads); // NOLINT(altera-id-dependent-backward-branch)
                   ++idx)
          {
            index_type total_lines = slice;

            if(idx < static_cast<index_type>(last % static_cast<index_type>(number_of_threads)))
            {
              ++total_lines;
            }

            pool.emplace_back(launch_nth, idx, static_cast<index_type>(number_of_threads), total_lines);
          }
        }

      }

      // Wait for the jobs to finish.
      for(auto& thread_in_pool : pool)
      {
        if(thread_in_pool.joinable())
        {
          thread_in_pool.join();
        }
      }
    }

    // Provide a serial version for easy comparison.
    template<typename index_type,
             typename callable_function_type>
    auto sequential_for(index_type             first,
                        index_type             last,
                        callable_function_type sequential_function) -> void
    {
      // LCOV_EXCL_START
      for(auto idx = first; idx < last; ++idx)
      {
        sequential_function(idx);
      }
      // LCOV_EXCL_STOP
    }
  } // namespace my_concurrency

#endif // CONCURRENCY_PARALLEL_FOR_H
