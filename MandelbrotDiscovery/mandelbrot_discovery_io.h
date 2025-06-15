///////////////////////////////////////////////////////////////////////////////
// Copyright Christopher Kormanyos 2025.
// Distributed under the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt
// or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef MANDELBROT_DISCOVERY_IO_2025_06_15_H
  #define MANDELBROT_DISCOVERY_IO_2025_06_15_H

  #include <string>

  struct mandelbrot_discovery_io_object
  {
    explicit mandelbrot_discovery_io_object(const std::string& str_fname,
                                            const unsigned     zoom_val,
                                            const unsigned     iter_val,
                                            const std::string& str_x,
                                            const std::string& str_y,
                                            const std::string& str_dx)
      : str_filename { str_fname },
        zoom         { zoom_val },
        iter         { iter_val },
        str_x_val    { str_x },
        str_y_val    { str_y },
        str_dx_half  { str_dx } { }

    std::string str_filename { };
    unsigned    zoom         { };
    unsigned    iter         { };
    std::string str_x_val    { };
    std::string str_y_val    { };
    std::string str_dx_half  { };

    static auto mandelbrot_discovery_io_load(mandelbrot_discovery_io_object& io_object_to_load) -> bool;
    static auto mandelbrot_discovery_io_save(const mandelbrot_discovery_io_object& io_object_to_save) -> bool;
  };

#endif // MANDELBROT_DISCOVERY_IO_2025_06_15_H
