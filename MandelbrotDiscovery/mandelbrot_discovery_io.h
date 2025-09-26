///////////////////////////////////////////////////////////////////////////////
// Copyright Christopher Kormanyos 2025.
// Distributed under the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt
// or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef MANDELBROT_DISCOVERY_IO_2025_06_15_H
  #define MANDELBROT_DISCOVERY_IO_2025_06_15_H

  #include <string>

  struct mandelbrot_discovery_io
  {
    explicit mandelbrot_discovery_io(const std::string& str_x,
                                     const std::string& str_y,
                                     const std::string& str_dx,
                                     const std::string& str_fname = "mandelbrot_zooming.txt",
                                     const unsigned     zoom_val  = 1U,
                                     const unsigned     iter_val  = 400U,
                                     const std::string& str_res   = "1")
      : str_x_val    { str_x },
        str_y_val    { str_y },
        str_dx_half  { str_dx },
        str_filename { str_fname },
        zoom         { zoom_val },
        iter         { iter_val },
        str_resol    { str_res } { }

    mandelbrot_discovery_io() = default;

    mandelbrot_discovery_io(const mandelbrot_discovery_io&) = default;
    mandelbrot_discovery_io(mandelbrot_discovery_io&&) noexcept = default;

    auto operator=(const mandelbrot_discovery_io&) -> mandelbrot_discovery_io& = default;
    auto operator=(mandelbrot_discovery_io&&) noexcept -> mandelbrot_discovery_io& = default;

    static auto load(mandelbrot_discovery_io& io_object_to_load) -> bool;
    static auto save(const mandelbrot_discovery_io& io_object_to_save) -> bool;

    std::string str_x_val    { "-0.75" };
    std::string str_y_val    { "+0.00" };
    std::string str_dx_half  { "+1.35" };
    std::string str_filename { "mandelbrot_zooming.txt" };
    unsigned    zoom         { 1U };
    unsigned    iter         { 400U };
    std::string str_resol    { "1" };
  };

#endif // MANDELBROT_DISCOVERY_IO_2025_06_15_H
