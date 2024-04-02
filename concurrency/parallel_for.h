///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2017 - 2023.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef PARALLEL_FOR_2017_12_18_H // NOLINT(llvm-header-guard)
  #define PARALLEL_FOR_2017_12_18_H

  #include <algorithm>
  #include <thread>
  #include <vector>

  namespace my_concurrency
  {
    template<typename index_type,
             typename callable_function_type>
    auto parallel_for(index_type             start,
                      index_type             end,
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
          [&parallel_function](index_type offset, index_type n, index_type total_lines)
          {
            for (auto i = static_cast<index_type>(0U); i < total_lines; ++i) // NOLINT(altera-id-dependent-backward-branch)
            {
              parallel_function(i*n + offset);
            }
          };

        {
          // Set the size of a slice for the range functions.
          const auto n =
            static_cast<index_type>
            (
              static_cast<index_type>(end - start)
            );

          const auto slice =
            (std::max)
            (
              static_cast<index_type>(std::floorf(static_cast<float>(n) / static_cast<float>(number_of_threads))),
              static_cast<index_type>(1)
            );

          for(auto   i = static_cast<index_type>(0U);
                     i < static_cast<index_type>(number_of_threads); // NOLINT(altera-id-dependent-backward-branch)
                   ++i)
          {
            index_type total_lines = slice;
            if (i < end % static_cast<index_type>(number_of_threads))
            {
              ++total_lines;
            }

            pool.emplace_back(launch_nth, i, static_cast<index_type>(number_of_threads), total_lines);
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
    auto sequential_for(index_type             start,
                        index_type             end,
                        callable_function_type sequential_function) -> void
    {
      for(auto i = start; i < end; ++i)
      {
        sequential_function(i);
      }
    }
  } // namespace my_concurrency

#endif // PARALLEL_FOR_2017_12_18_H
