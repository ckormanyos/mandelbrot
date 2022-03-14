///////////////////////////////////////////////////////////////////////////////
//      Copyright Christopher Kormanyos 2022.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef MANDELBROT_CFG_MANDELBROT_31_ZOOM_ANOTHER_01_2022_02_24_H
  #define MANDELBROT_CFG_MANDELBROT_31_ZOOM_ANOTHER_01_2022_02_24_H

  // At the moment, this is my personal best deep dive with relatively
  // high precision. This deep dive features magnification of
  // approximately 1e310, which is 1 and 310 zeros. Generating this
  // image took about 15 hours on my machine.

  // TBD: Try to zoom even deeper with higher precision and more iterations.
  // The remarkable video here: https://www.youtube.com/watch?v=pCpLWbHVNhk
  // makes use of the same high-precision coordinate (shown below).
  // The author of that video, for instance, reports and beautifully
  // depicts achieving a deep zoom of approximately 1e1091 at this
  // staggeringly high-precision coordinate.

  #define MANDELBROT_FILENAME_STRING            "MANDELBROT_31_ZOOM_ANOTHER_01"

  #define MANDELBROT_CALCULATION_DIGITS10       287
  #define MANDELBROT_CALCULATION_PIXELS_1D      2048UL
  #define MANDELBROT_CALCULATION_ITERATIONS     60000UL

  #define MANDELBROT_POINT_DX_HALF              "6.4E-201"
  #define MANDELBROT_POINT_CENTER_X             "-1.740062382579339905220844167065825638296641720436171866879862418461182919644153056054840718339483225743450008259172138785492983677893366503417299549623738838303346465461290768441055486136870719850559269507357211790243666940134793753068611574745943820712885258222629105433648695946003865"
  #define MANDELBROT_POINT_CENTER_Y             "0.0281753397792110489924115211443195096875390767429906085704013095958801743240920186385400814658560553615695084486774077000669037710191665338060418999324320867147028768983704831316527873719459264592084600433150333362859318102017032958074799966721030307082150171994798478089798638258639934"

  #include <mandelbrot/cfg/mandelbrot_cfg.h>

#endif // MANDELBROT_CFG_MANDELBROT_31_ZOOM_ANOTHER_01_2022_02_24_H
