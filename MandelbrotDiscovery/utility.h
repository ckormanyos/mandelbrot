#ifndef UTILITY_2024_04_14_H
  #define UTILITY_2024_04_14_H

  namespace utility
  {
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
  } // namespace utility

#endif // UTILITY_2024_04_14_H
