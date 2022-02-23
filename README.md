ckormanyos/mandelbrot
==================

ckormanyos/mandelbrot implements a header-only C++ template library for
extended precision Mandelbrot fractal iterations.

This C++ template header-only library implements Mandelbrot fractal iterations.
It is intended to be used for so-called _deep_ _dives_ involving multiple-precision
floating-point or fixed-point types.

ckormanyos/mandelbrot implements the fractal iteration scheme using multiple
CPU cores. Visualization of the result uses color-stretching techniques with the
histogram method. Graphical representation uses Boost.Gil in combination with the
JPEG-6b library.

ckormanyos/mandelbrot is written in header-only C++11, and compatible through C++11, 14, 17, 20.

## Sample Image

A beautiful deep dive showing a swirly seahorse image in blach-and-white color representation
is shown below. The square image has
<img src="https://render.githubusercontent.com/render/math?math=2048\,\times\,2048">
pixels. It been taken at the point
<img src="https://render.githubusercontent.com/render/math?math=(-0.7453983606667815,\,0.1125046349959942)">
with a half-width of
<img src="https://render.githubusercontent.com/render/math?math=1.76E-12">.
A multiple-precision type (Boost's `cpp_dec_float`) has been used with 37 decimal digits of precision.

![](./images/mandelbrot_MANDELBROT_05_SEAHORSES.jpg)

## Using ckormanyos/mandelbrot

TBD.

## Adaptions of and Notes on JPEG-6b

We use a modified version of jpeg-6b located [here](./jpeg-6b-2022).

See the original _README_ located [here](./jpeg-6b-2022)
for more information, with explicit jpeg-software licensing terms
[here](https://github.com/ckormanyos/mandelbrot/blob/78114ab4bc2ba14e9abe8f113f2e0cf4d422cb9f/jpeg-6b-2022/README#L111).
