///////////////////////////////////////////////////////////////////////////////
// Copyright Christopher Kormanyos 2024.
// Distributed under the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt
// or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#include <geometry.h>

#include <boost/gil/image.hpp>
#include <boost/gil/typedefs.hpp>
#include <boost/gil/extension/io/jpeg/old.hpp>
#include <boost/gil/extension/io/png/old.hpp>
#include <boost/gil/extension/numeric/resample.hpp>
#include <boost/gil/extension/numeric/sampler.hpp>
#include <boost/gil/io/read_image.hpp>
#include <boost/gil/io/write_view.hpp>

auto mandelbrot_discovery_rescale() -> void
{
  // Rescale the JPEG/PNG files.

  // Load the input image(s).
  boost::gil::rgb8_image_t input_image_jpg;
  boost::gil::rgb8_image_t input_image_png;

  boost::gil::read_image("mandelbrot_zooming.jpg", input_image_jpg, boost::gil::jpeg_tag());
  boost::gil::read_image("mandelbrot_zooming.png", input_image_png, boost::gil::png_tag ());

  // Get the dimensions of the input image(s).
  const auto input_dimensions_jpg = input_image_jpg.dimensions();
  const auto input_dimensions_png = input_image_png.dimensions();

  // Define the new desired size by scaling from potentially fewer pixels
  // to the default of 768 * 768 pixels.

  boost::gil::point_t
    new_dimensions
    {
      geometry::rectangle_base::default_pixels(),
      geometry::rectangle_base::default_pixels()
    };

  // Create the output image(s) with the new dimensions
  boost::gil::rgb8_image_t output_image_jpg(new_dimensions.x, new_dimensions.y);
  boost::gil::rgb8_image_t output_image_png(new_dimensions.x, new_dimensions.y);

  // Resize the output image(s).
  boost::gil::resize_view
  (
    boost::gil::view(input_image_jpg),
    boost::gil::view(output_image_jpg),
    boost::gil::bilinear_sampler()
  );

  boost::gil::resize_view
  (
    boost::gil::view(input_image_png),
    boost::gil::view(output_image_png),
    boost::gil::bilinear_sampler()
  );

  // Save the resized output image(s).
  boost::gil::write_view("mandelbrot_zooming.jpg", boost::gil::view(output_image_jpg), boost::gil::jpeg_tag());
  boost::gil::write_view("mandelbrot_zooming.png", boost::gil::view(output_image_png), boost::gil::png_tag ());
}
