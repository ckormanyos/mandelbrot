///////////////////////////////////////////////////////////////////////////////
// Copyright Christopher Kormanyos 2025.
// Distributed under the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt
// or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#include <mandelbrot_discovery_io.h>

#include <fstream>

auto mandelbrot_discovery_io_object::mandelbrot_discovery_io_load(mandelbrot_discovery_io_object& io_object_to_load) -> bool
{
  static_cast<void>(io_object_to_load.str_filename.empty());

  return false;
}

auto mandelbrot_discovery_io_object::mandelbrot_discovery_io_save(const mandelbrot_discovery_io_object& io_object_to_save) -> bool
{
  static_cast<void>(io_object_to_save.str_filename.empty());

  return false;
}

