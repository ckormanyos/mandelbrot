ckormanyos/mandelbrot
==================

ckormanyos/mandelbrot implements a header-only C++ template library for
extended precision Mandelbrot fractal iterations.

It is intended to be used for so-called _deep_ _dives_ involving multiple-precision
floating-point or fixed-point types.

## Design Goals

The following design goals have been incorporated.
  - ckormanyos/mandelbrot is written in header-only C++11, and compatible through C++11, 14, 17, 20.
  - ckormanyos/mandelbrot implements the inner loop of the fractal iteration scheme using multiple, parallel CPU cores.
  - C++ template design allows flexible use of any appropriate kind of big-number type.
  - Visualization of the result uses color-stretching techniques with the histogram method.
  - Graphical representation uses Boost.Gil in combination with the JPEG-6b library.
  - Color scheming can be easily adapted via straightforward creation/adaption of a skinny derived class.

## Sample Images

A beautiful deep dive showing a swirly seahorse image in black-and-white color representation
is shown below. The square image has features following features/parameters.

  - Has <img src="https://render.githubusercontent.com/render/math?math=2048\,\times\,2048"> pixels.
  - Centered at the point <img src="https://render.githubusercontent.com/render/math?math=(-0.7453983606667815,\,0.1125046349959942)">.
  - Uses a half-width of <img src="https://render.githubusercontent.com/render/math?math=1.76E-12">.
  - Iterated with <img src="https://render.githubusercontent.com/render/math?math=2,000"> iteratons using Boost's `cpp_dec_float` multiple-precision type instantiated with <img src="https://render.githubusercontent.com/render/math?math=37"> decimal digits of precision.

![](./images/mandelbrot_MANDELBROT_05_SEAHORSES.jpg)

My personal best deep dive has a scale of approximately
<img src="https://render.githubusercontent.com/render/math?math=10E-301">,
i.e., having a magnification of approximately
<img src="https://render.githubusercontent.com/render/math?math=10^{301}">,
which is a
<img src="https://render.githubusercontent.com/render/math?math=1">
with
<img src="https://render.githubusercontent.com/render/math?math=301">
zeros.

The image has the following features/parameters and is shown below.

  - Has <img src="https://render.githubusercontent.com/render/math?math=1536\,\times\,1536"> pixels.
  - Centered at the point <img src="https://render.githubusercontent.com/render/math?math=(0.360240443437614363236125244449545308482607807958585750488375814740195346059218100311752936722773426396233731729724987737320035372683285317664532401218521579554288661726564324134702299962817029213329980895208036363104546639698106204384566555001322985619004717862781192694046362748742863016467354574422779443226982622356594130430232458472420816652623492974891730419252651127672782407292315574480207005828774566475024380960675386215814315654794021855269375824443853463117354448779647099224311848192893972572398662626725254769950976527431277402440752868498588785436705371093442460696090720654908973712759963732914849861213100695402602927267843779747314419332179148608587129105289166676461292845685734536033692577618496925170576714796693411776794742904333484665301628662532967079174729170714156810530598764525260869731233845987202037712637770582084286587072766838497865108477149114659838883818795374195150936369987302574377608649625020864292915913378927790344097552591919409137354459097560040374880346637533711271919419723135538377394364882968994646845930838049998854075817859391340445151448381853615103761584177161812057928,\,-0.6413130610648031748603750151793020665794949522823052595561775430644485741727536902556370230689681162370740565537072149790106973211105273740851993394803287437606238596262287731075999483940467161288840614581091294325709988992269165007394305732683208318834672366947550710920088501655704252385244481168836426277052232593412981472237968353661477793530336607247738951625817755401065045362273039788332245567345061665756708689359294516668271440525273653083717877701237756144214394870245598590883973716531691124286669552803640414068523325276808909040317617092683826521501539932397262012011082098721944643118695001226048977430038509470101715555439047884752058334804891389685530946112621573416582482926221804767466258346014417934356149837352092608891639072745930639364693513216719114523328990690069588676087923656657656023794484324797546024248328156586471662631008741349069961493817600100133439721557969263221185095951241491408756751582471307537382827924073746760884081704887902040036056611401378785952452105099242499241003208013460878442953408648178692353788153787229940221611731034405203519945313911627314900851851072122990492499999999999999999991)">.
  - Uses a half-width of <img src="https://render.githubusercontent.com/render/math?math=4.4^{-311}">.
  - Iterated with <img src="https://render.githubusercontent.com/render/math?math=60,000"> iteratons using Boost's `gmp_float` multiple-precision type instantiated with <img src="https://render.githubusercontent.com/render/math?math=365"> decimal digits of precision.

![](./images/mandelbrot_MANDELBROT_20_ZOOM_VERY_DEEP_00.jpg)


## Using ckormanyos/mandelbrot

TBD.

## Adaptions of and Notes on JPEG-6b

We use a modified version of jpeg-6b located [here](./jpeg-6b-2022).
According to license agreement, it is referred to as
_the_ _Independent_ _JPEG_ _Group's_ _software_.

See the original _README_ located [here](./jpeg-6b-2022)
for more information, with explicit licensing terms
of _the_ _Independent_ _JPEG_ _Group's_ _software_ located
[here](https://github.com/ckormanyos/mandelbrot/blob/78114ab4bc2ba14e9abe8f113f2e0cf4d422cb9f/jpeg-6b-2022/README#L111).
