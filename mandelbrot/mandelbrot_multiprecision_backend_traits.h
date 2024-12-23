///////////////////////////////////////////////////////////////////////////////
// Copyright Christopher Kormanyos 2024.
// Distributed under the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt
// or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef MANDELBROT_MULTIPRECISION_BACKEND_TRAITS_2024_09_07_H // NOLINT(llvm-header-guard)
  #define MANDELBROT_MULTIPRECISION_BACKEND_TRAITS_2024_09_07_H

  #include <boost/multiprecision/cpp_dec_float.hpp>
  #if defined(MANDELBROT_USE_GMP_FLOAT)
  #include <boost/multiprecision/gmp.hpp>
  #endif

  #include <type_traits>

  // Helper template to check if the type is instantiated with cpp_dec_float
  template <typename T>
  struct is_cpp_dec_float_backend : std::false_type { };

  // Specialization for cpp_dec_float backend
  template <unsigned Digits10>
  struct is_cpp_dec_float_backend<boost::multiprecision::cpp_dec_float<Digits10>> : std::true_type { };

  // Template to check if the given boost::multiprecision::number uses cpp_dec_float as its backend
  template <typename T>
  struct is_cpp_dec_float_number : is_cpp_dec_float_backend<typename T::backend_type> { };

  // Define a trial number type with cpp_dec_float backend having 100 digits.
  // This type is sued for static-assertion only.
  namespace static_assertion_only {

  using cpp_dec_test_100_backend_type = boost::multiprecision::cpp_dec_float<unsigned { UINT8_C(100) }>;

  using cpp_dec_test_100_type = ::boost::multiprecision::number<cpp_dec_test_100_backend_type, boost::multiprecision::et_off>;

  static_assert(is_cpp_dec_float_number<cpp_dec_test_100_type>::value, "Error: Wrong instantiation of backend type");

  } // namespace static_assertion_only

  #if defined(MANDELBROT_USE_GMP_FLOAT)

  // Helper template to check if the type is instantiated with gmp_float
  template <typename T>
  struct is_gmp_float_backend : std::false_type { };

  // Specialization for gmp_float backend
  template <unsigned Digits10>
  struct is_gmp_float_backend<boost::multiprecision::gmp_float<Digits10>> : std::true_type { };

  // Template to check if the given boost::multiprecision::number uses gmp_float as its backend
  template <typename T>
  struct is_gmp_float_number : is_gmp_float_backend<typename T::backend_type> { };

  #endif

#endif // MANDELBROT_MULTIPRECISION_BACKEND_TRAITS_2024_09_07_H
