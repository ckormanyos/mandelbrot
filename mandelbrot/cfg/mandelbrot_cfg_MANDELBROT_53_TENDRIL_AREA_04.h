///////////////////////////////////////////////////////////////////////////////
//      Copyright Christopher Kormanyos 2025.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef MANDELBROT_CFG_MANDELBROT_53_TENDRIL_AREA_04_2025_04_25_H
  #define MANDELBROT_CFG_MANDELBROT_53_TENDRIL_AREA_04_2025_04_25_H

  #if (!defined(_MSC_VER) && defined(__cplusplus) && (__cplusplus >= 201703L))
  namespace ckormanyos::mandelbrot::config {
  #else
  namespace ckormanyos { namespace mandelbrot { namespace config { // NOLINT(modernize-concat-nested-namespaces)
  #endif

  constexpr char MANDELBROT_FILENAME_STRING[]       = "MANDELBROT_53_TENDRIL_AREA_04";

  constexpr int  MANDELBROT_COORD_PNT_DIGITS10      =     162;
  constexpr int  MANDELBROT_ITERATION_DIGITS10      =      28;
  constexpr int  MANDELBROT_CALCULATION_PIXELS_X    =    2048;
  constexpr int  MANDELBROT_CALCULATION_PIXELS_Y    =    2048;
  constexpr int  MANDELBROT_CALCULATION_ITERATIONS  =   20000;

  // This was a thrilling point. It ends up hitting a Mandelbrot
  // figure at around order 152. But prior to doing so, the image
  // goes through a variety of geometric transformations. In between
  // the transformations it looks like a whirlpool spinning around.

  // For the image, I walked this point back to Magnification
  // order 10^138 where a gentle whirlpool is bounded by
  // four dipole-like structures enclosed in boundaries
  // that look like little pods.

  constexpr char MANDELBROT_POINT_DX_HALF[]         = "1.25E-138";
  constexpr char MANDELBROT_POINT_DY_HALF[]         = "1.25E-138";
  constexpr char MANDELBROT_POINT_CENTER_X[]        = "-1.255589529041767443075662810348547194884297879542589303691898674036089101375975104522809828007307219142487417548757615919000565258227843578239062626613046740234375";
  constexpr char MANDELBROT_POINT_CENTER_Y[]        = "+0.107633740437100457285639701906416244578284629482228824352877844872572501467076151353270968293106724415020871823412258993906808033341933187855986309482205205078125";

  template<typename CoordPntNumericType, typename IterateNumericType>
  using my_mandelbrot_generator_type = ::ckormanyos::mandelbrot::mandelbrot_generator_perturbative<CoordPntNumericType, IterateNumericType>;

  #if (!defined(_MSC_VER) && defined(__cplusplus) && (__cplusplus >= 201703L))
  } // namespace ckormanyos::mandelbrot::config
  #else
  } // namespace config
  } // namespace mandelbrot
  } // namespace ckormanyos
  #endif

#endif // MANDELBROT_CFG_MANDELBROT_53_TENDRIL_AREA_04_2025_04_25_H
