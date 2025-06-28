///////////////////////////////////////////////////////////////////////////////
// Copyright Christopher Kormanyos 2025.
// Distributed under the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt
// or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#include <mandelbrot_discovery_io.h>

#include <fstream>

auto mandelbrot_discovery_io::load(mandelbrot_discovery_io& io_object_to_load) -> bool
{
  static_cast<void>(!io_object_to_load.str_filename.empty());

  return false;
}

auto mandelbrot_discovery_io::save(const mandelbrot_discovery_io& io_object_to_save) -> bool
{
  const std::string
    str_filename_save
    {
      ((!io_object_to_save.str_filename.empty()) ? io_object_to_save.str_filename : "mandelbrot_zooming.txt")
    };

  static_cast<void>(!str_filename_save.empty());

  return false;
}
