///////////////////////////////////////////////////////////////////////////////
//      Copyright Christopher Kormanyos 2015 - 2022.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)
//

// A well-known example of fractal is the Mandelbrot set,
// which is based upon the function z_{n+1} = z_{n}^2 + c.
// A common way of coloring Mandelbrot images is by taking
// the number of iterations required to reach non-bounded
// divergence from c and then assigning that value a color.

// This example uses Boost.Multiprecision to implement
// a high-precision Mandelbrot iteration and visualization.
// Graphic file creation uses Boost.Gil (old) to wrap JPEG.
// Color-strething in combination with the histogram method
// is used for creating vivid images. The default color
// scheme uses stretched, amplified and modulated black
// and white coloring. The Mandelbrot iteration is carried
// out with hardware concurrency with multiple threads.
// The multithreading dispatcher used 3/4 of the available
// CPU cores that can be found using hardware concurrency.

// The Mandelbrot set consists of those points c in the
// complex plane for which the iteration
//   z_{n+1} = z_{n}^2 + c,
// with z_{0} = 0 stays bounded.

// Interesting iteration points could be points having an orbit.
// An orbit of length n is a sequence of z_{n} with
//   z_{1} = c, z_{2}, ..., z{n},
// such that z_{n} = z_{1} and z_{n} != z_{k} with (1 < k < n).
// In order to find these, numerical methods are needed.
// The equation z_{n} = z_{1} can only be solved in closed form
// by hand for small n. A point c of order n will also show up
// as a point of order n_{m}, for some m > 1. Mark these points
// in your set.

// Any point that is inside the Mandelbrot set and close to the
// boundary between the set and its complement as well as any point
// outside the Mandelbrot set that is close to this boundary is an
// interesting point. The closer you are to the boundary, the more
// you need to zoom in to see the interesting parts. In particular,
// all points on the x-axis between -2 and 1/4 are in the Mandelbrot set.
// Especially close to x = -2 (from the right), the point (x, 0)
// is arbitrarily close to the boundary. So try the point (eps - 2, 0)
// for a small (eps > 0). Some Mandelbrot softwares use a strategy that
// zooms in, continually trying to find a point close to the boundary
// while zooming, and uses that as the zoom point.

// Points on the boundary of the Mandelbrot set can potentially
// have the most interesting orbits.  The easiest boundary points
// to compute are:
//   * The spike along the negative real axis
//   * The boundary of the main cardioid:
//       r = (1 - cos(theta))/2,
//       x = r*cos(theta)+0.25,
//       y = r*sin(theta)
//   * The boundary of the period 2 disk:
//       r = 0.25,
//       x = r*cos(theta)-1,
//       y = r*sin(theta)

#include <chrono>
#include <iostream>

#include <mandelbrot/mandelbrot.h>

// Provide instructions for simple build on WSL.
// cd /mnt/c/Users/User/Documents/Ks/PC_Software/NumericalPrograms/mandelbrot/jpeg-6b-2022
// make all

// cd ..

// g++ -c -finline-functions -march=native -mtune=native -O3 -Wall -Wextra -std=c++11 -DMANDELBROT_USE_GMP_FLOAT -I. -I/mnt/c/boost/boost_1_78_0 -I./jpeg-6b-2022 -pthread test/test_mandelbrot.cpp -o test_mandelbrot.o
// g++ test_mandelbrot.o -lpthread -lgmp -ljpeg-6b -Ljpeg-6b-2022/obj -o test_mandelbrot.exe

#if defined(MANDELBROT_USE_GMP_FLOAT)

#include <boost/multiprecision/gmp.hpp>

#define MANDELBROT_NUMBER_TYPE_NAME(mandelbrot_digits10) \
boost::multiprecision::number<boost::multiprecision::gmp_float<(mandelbrot_digits10)>,\
                              boost::multiprecision::et_off>

#else

#include <boost/multiprecision/cpp_dec_float.hpp>

#define MANDELBROT_NUMBER_TYPE_NAME(mandelbrot_digits10) \
boost::multiprecision::number<boost::multiprecision::cpp_dec_float<(mandelbrot_digits10)>,\
                              boost::multiprecision::et_off>

#endif

int main()
{
  const std::string str_filename = "images/tmp/mandelbrot_" + std::string("MANDELBROT_05_SEAHORSES") + ".jpg";

  // This is a swirly seahorse image.
  using local_numeric_type      = MANDELBROT_NUMBER_TYPE_NAME(37);
  using mandelbrot_config_type  = ckormanyos::mandelbrot::mandelbrot_config<local_numeric_type, 2000, 2048U>;
  using mandelbrot_numeric_type = typename mandelbrot_config_type::mandelbrot_config_numeric_type;

  const mandelbrot_numeric_type dx_half("1.76E-12");
  const mandelbrot_numeric_type cx     ("-0.7453983606667815");
  const mandelbrot_numeric_type cy     ("0.1125046349959942");

  const mandelbrot_numeric_type x_lo = cx - dx_half;
  const mandelbrot_numeric_type x_hi = cx + dx_half;
  const mandelbrot_numeric_type y_lo = cy - dx_half;
  const mandelbrot_numeric_type y_hi = cy + dx_half;

  const mandelbrot_config_type mandelbrot_config_object(x_lo, x_hi, y_lo, y_hi);

  using mandelbrot_generator_type =
    ckormanyos::mandelbrot::mandelbrot_generator<mandelbrot_numeric_type,
                                                 mandelbrot_config_type::max_iterations>;

        ckormanyos::mandelbrot::color::color_stretch_histogram_method local_color_stretches;
  const ckormanyos::mandelbrot::color::color_functions_bw             local_color_functions;
  //const ckormanyos::mandelbrot::color::color_functions_pretty  local_color_functions;

  mandelbrot_generator_type mandelbrot_generator(mandelbrot_config_object);

  const auto start = std::chrono::high_resolution_clock::now();

  mandelbrot_generator.generate_mandelbrot_image(str_filename,
                                                 local_color_functions,
                                                 local_color_stretches);

  const auto stop = std::chrono::high_resolution_clock::now();

  auto elapsed = std::chrono::duration_cast<std::chrono::seconds>(stop - start).count();

  std::cout << "Time for calculation: "
            << elapsed
            << "s"
            << std::endl;
}
