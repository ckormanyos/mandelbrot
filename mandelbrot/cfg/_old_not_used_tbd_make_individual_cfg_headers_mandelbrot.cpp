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

#include <mandelbrot.h>

// Provide instructions for simple build on WSL.
// cd /mnt/c/Users/User/Documents/Ks/PC_Software/NumericalPrograms/mandelbrot/jpeg-6b-2022

// cd ..
// cd /mnt/c/Users/User/Documents/Ks/PC_Software/NumericalPrograms/mandelbrot
// make all

// g++ -c -finline-functions -march=native -mtune=native -O3 -Wall -Wextra -std=c++11 -DMANDELBROT_IMAGE_INDEX=MANDELBROT_05_SEAHORSES -DMANDELBROT_USE_GMP_FLOAT -I. -I/mnt/c/boost/boost_1_78_0 -I./jpeg-6b-2022 -pthread mandelbrot.cpp -o mandelbrot.o
// g++ mandelbrot.o -lpthread -lgmp -ljpeg-6b -Ljpeg-6b-2022/obj -o mandelbrot.exe

#define MANDELBROT_01_FULL                  1
#define MANDELBROT_03_TOP                   3
#define MANDELBROT_04_SWIRL                 4
#define MANDELBROT_05_SEAHORSES             5
#define MANDELBROT_06_BRANCHES              6
#define MANDELBROT_07_SEAHORSE_VALLEY       7
#define MANDELBROT_08_DEEP_DIVE_01          8
#define MANDELBROT_09_DEEP_DIVE_02          9
#define MANDELBROT_10_ZOOM_WIKI_00         10
#define MANDELBROT_11_ZOOM_WIKI_01         11
#define MANDELBROT_12_ZOOM_WIKI_02         12
#define MANDELBROT_20_ZOOM_VERY_DEEP_00    20
#define MANDELBROT_21_ZOOM_VERY_DEEP_01    21
#define MANDELBROT_22_ZOOM_VERY_DEEP_02    22
#define MANDELBROT_30_ZOOM_ANOTHER_00      30
#define MANDELBROT_31_ZOOM_ANOTHER_01      31
#define MANDELBROT_32_ZOOM_ANOTHER_02      32

#if !defined(MANDELBROT_IMAGE_INDEX)
#define MANDELBROT_IMAGE_INDEX MANDELBROT_05_SEAHORSES
#endif

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
  #if (MANDELBROT_IMAGE_INDEX == MANDELBROT_01_FULL)

    const std::string str_filename = "images/mandelbrot_" + std::string("MANDELBROT_01_FULL") + ".jpg";

    // This is the classic full immage.
    using local_numeric_type      = MANDELBROT_NUMBER_TYPE_NAME(37);
    using mandelbrot_config_type  = ckormanyos::mandelbrot::mandelbrot_config<local_numeric_type, 2000U, 2048U>;
    using mandelbrot_numeric_type = typename mandelbrot_config_type::mandelbrot_config_numeric_type;


    const mandelbrot_numeric_type dx_half(+1.25L);
    const mandelbrot_numeric_type cx     (-0.75L);
    const mandelbrot_numeric_type cy     (+0.0L);

  #elif (MANDELBROT_IMAGE_INDEX == MANDELBROT_03_TOP)

    const std::string str_filename = "images/mandelbrot_" + std::string("MANDELBROT_03_TOP") + ".jpg";

    // This is a view of an upper part of the image (near the top of the classic full view).
    using local_numeric_type      = MANDELBROT_NUMBER_TYPE_NAME(31);
    using mandelbrot_config_type  = ckormanyos::mandelbrot::mandelbrot_config<local_numeric_type, 2000U, 2048U>;
    using mandelbrot_numeric_type = typename mandelbrot_config_type::mandelbrot_config_numeric_type;

    const mandelbrot_numeric_type dx_half("0.282");
    const mandelbrot_numeric_type cx     ("-0.130");
    const mandelbrot_numeric_type cy     ("0.856");

  #elif (MANDELBROT_IMAGE_INDEX == MANDELBROT_04_SWIRL)

    const std::string str_filename = "images/mandelbrot_" + std::string("MANDELBROT_04_SWIRL") + ".jpg";

    // This is a fanning swirl image.
    using local_numeric_type      = MANDELBROT_NUMBER_TYPE_NAME(31);
    using mandelbrot_config_type  = ckormanyos::mandelbrot::mandelbrot_config<local_numeric_type, 2000U, 2048U>;
    using mandelbrot_numeric_type = typename mandelbrot_config_type::mandelbrot_config_numeric_type;

    const mandelbrot_numeric_type dx_half("0.0002315");
    const mandelbrot_numeric_type cx     ("-0.749730");
    const mandelbrot_numeric_type cy     ("-0.046608");

  #elif (MANDELBROT_IMAGE_INDEX == MANDELBROT_05_SEAHORSES)

    const std::string str_filename = "images/mandelbrot_" + std::string("MANDELBROT_05_SEAHORSES") + ".jpg";

    // This is a swirly seahorse image.
    using local_numeric_type      = MANDELBROT_NUMBER_TYPE_NAME(37);
    using mandelbrot_config_type  = ckormanyos::mandelbrot::mandelbrot_config<local_numeric_type, 2000, 2048U>;
    using mandelbrot_numeric_type = typename mandelbrot_config_type::mandelbrot_config_numeric_type;

    const mandelbrot_numeric_type dx_half("1.76E-12");
    const mandelbrot_numeric_type cx     ("-0.7453983606667815");
    const mandelbrot_numeric_type cy     ("0.1125046349959942");

  #elif (MANDELBROT_IMAGE_INDEX == MANDELBROT_06_BRANCHES)

    const std::string str_filename = "images/mandelbrot_" + std::string("MANDELBROT_06_BRANCHES") + ".jpg";

    // This is a spiral image of branches.
    using local_numeric_type      = MANDELBROT_NUMBER_TYPE_NAME(31);
    using mandelbrot_config_type  = ckormanyos::mandelbrot::mandelbrot_config<local_numeric_type, 2000U, 2048U>;
    using mandelbrot_numeric_type = typename mandelbrot_config_type::mandelbrot_config_numeric_type;

    const mandelbrot_numeric_type dx_half("4.2E-12");
    const mandelbrot_numeric_type cx     ("0.3369844464873");
    const mandelbrot_numeric_type cy     ("0.0487782196791");

  #elif (MANDELBROT_IMAGE_INDEX == MANDELBROT_07_SEAHORSE_VALLEY)

    const std::string str_filename = "images/mandelbrot_" + std::string("MANDELBROT_07_SEAHORSE_VALLEY") + ".jpg";

    // This is an image from the seahorse valley.
    using local_numeric_type      = MANDELBROT_NUMBER_TYPE_NAME(31);
    using mandelbrot_config_type  = ckormanyos::mandelbrot::mandelbrot_config<local_numeric_type, 2000U, 2048U>;
    using mandelbrot_numeric_type = typename mandelbrot_config_type::mandelbrot_config_numeric_type;

    const mandelbrot_numeric_type dx_half("0.024");
    const mandelbrot_numeric_type cx     ("-0.748");
    const mandelbrot_numeric_type cy     ("0.222");

  #elif (MANDELBROT_IMAGE_INDEX == MANDELBROT_08_DEEP_DIVE_01)

    const std::string str_filename = "images/mandelbrot_" + std::string("MANDELBROT_08_DEEP_DIVE_01") + ".jpg";

    // This is a deep zoom image.
    // Note: Use 143 or more decimal digits for this iteration.

    using local_numeric_type      = MANDELBROT_NUMBER_TYPE_NAME(143);
    using mandelbrot_config_type  = ckormanyos::mandelbrot::mandelbrot_config<local_numeric_type, 2000U, 2048U>;
    using mandelbrot_numeric_type = typename mandelbrot_config_type::mandelbrot_config_numeric_type;

    const mandelbrot_numeric_type dx_half("1.25E-107");
    const mandelbrot_numeric_type cx     ("-1.99999999913827011875827476290869498831680913663682095950680227271547027727918984035447670553861909622481524124");
    const mandelbrot_numeric_type cy     ("0.00000000000001314895443507637575136247566806505002151700520912095709529449343530548994027524594471095886432006");

    static_assert(std::numeric_limits<mandelbrot_numeric_type>::digits10 >= 143,
                  "Error: Please use 143 or more decimal digits for MANDELBROT_08_DEEP_DIVE_01.");

  #elif (MANDELBROT_IMAGE_INDEX == MANDELBROT_09_DEEP_DIVE_02)

    const std::string str_filename = "images/mandelbrot_" + std::string("MANDELBROT_09_DEEP_DIVE_02") + ".jpg";

    // This is a deep zoom image.
    // Note: Use 79 or more decimal digits for this iteration.

    using local_numeric_type      = MANDELBROT_NUMBER_TYPE_NAME(95);
    using mandelbrot_config_type  = ckormanyos::mandelbrot::mandelbrot_config<local_numeric_type, 15000U, 2048U>;
    using mandelbrot_numeric_type = typename mandelbrot_config_type::mandelbrot_config_numeric_type;

    const mandelbrot_numeric_type dx_half("2.55E-55");
    const mandelbrot_numeric_type cx     ("-1.295189082147777457017064177185681926706566460884888469217456");
    const mandelbrot_numeric_type cy     ("0.440936982678320138880903678356262612113214627431396203682661");

    static_assert(std::numeric_limits<mandelbrot_numeric_type>::digits10 >= 95,
                  "Error: Please use 95 or more decimal digits for MANDELBROT_09_DEEP_DIVE_02.");

  #elif (MANDELBROT_IMAGE_INDEX ==  MANDELBROT_10_ZOOM_WIKI_00)

    const std::string str_filename = "images/mandelbrot_" + std::string("MANDELBROT_10_ZOOM_WIKI_00") + ".jpg";

    // This is a medium zoom image from the zoom coordinates of:
    // http://en.wikipedia.org/wiki/File:Mandelbrot_sequence_new.gif
    // Note: Use 55 or more decimal digits for this iteration.

    using local_numeric_type      = MANDELBROT_NUMBER_TYPE_NAME(55);
    using mandelbrot_config_type  = ckormanyos::mandelbrot::mandelbrot_config<local_numeric_type, 20000U, 2048U>;
    using mandelbrot_numeric_type = typename mandelbrot_config_type::mandelbrot_config_numeric_type;

    const mandelbrot_numeric_type dx_half("3.1E-25");
    const mandelbrot_numeric_type cx     ("-0.743643887037158704752191506114774");
    const mandelbrot_numeric_type cy     ("0.131825904205311970493132056385139");

    static_assert(std::numeric_limits<mandelbrot_numeric_type>::digits10 >= 55,
                  "Error: Please use 55 or more decimal digits for MANDELBROT_10_ZOOM_WIKI_00.");

  #elif (MANDELBROT_IMAGE_INDEX ==  MANDELBROT_11_ZOOM_WIKI_01)

    const std::string str_filename = "images/mandelbrot_" + std::string("MANDELBROT_11_ZOOM_WIKI_01") + ".jpg";

    // This is a medium zoom image from the zoom coordinates of:
    // http://en.wikipedia.org/wiki/File:Mandelbrot_sequence_new.gif
    // Note: Use 55 or more decimal digits for this iteration.

    using local_numeric_type      = MANDELBROT_NUMBER_TYPE_NAME(55);
    using mandelbrot_config_type  = ckormanyos::mandelbrot::mandelbrot_config<local_numeric_type, 30000U, 2048U>;
    using mandelbrot_numeric_type = typename mandelbrot_config_type::mandelbrot_config_numeric_type;

    const mandelbrot_numeric_type dx_half("3.3E-27");
    const mandelbrot_numeric_type cx     ("-0.743643887037158704752191506114774");
    const mandelbrot_numeric_type cy     ("0.131825904205311970493132056385139");

    static_assert(std::numeric_limits<mandelbrot_numeric_type>::digits10 >= 55,
                  "Error: Please use 55 or more decimal digits for MANDELBROT_11_ZOOM_WIKI_01.");

  #elif (MANDELBROT_IMAGE_INDEX ==  MANDELBROT_12_ZOOM_WIKI_02)

    const std::string str_filename = "images/mandelbrot_" + std::string("MANDELBROT_12_ZOOM_WIKI_02") + ".jpg";

    // This is a medium zoom image from the zoom coordinates of:
    // http://en.wikipedia.org/wiki/File:Mandelbrot_sequence_new.gif
    // Note: Use 55 or more decimal digits for this iteration.

    using local_numeric_type      = MANDELBROT_NUMBER_TYPE_NAME(55);
    using mandelbrot_config_type  = ckormanyos::mandelbrot::mandelbrot_config<local_numeric_type, 40000U, 2048U>;
    using mandelbrot_numeric_type = typename mandelbrot_config_type::mandelbrot_config_numeric_type;

    const mandelbrot_numeric_type dx_half("6.5E-28");
    const mandelbrot_numeric_type cx     ("-0.743643887037158704752191506114774");
    const mandelbrot_numeric_type cy     ("0.131825904205311970493132056385139");

    static_assert(std::numeric_limits<mandelbrot_numeric_type>::digits10 >= 55,
                  "Error: Please use 55 or more decimal digits for MANDELBROT_12_ZOOM_WIKI_02.");

  #elif (MANDELBROT_IMAGE_INDEX ==  MANDELBROT_20_ZOOM_VERY_DEEP_00)

    const std::string str_filename = "images/mandelbrot_" + std::string("MANDELBROT_20_ZOOM_VERY_DEEP_00") + ".jpg";

    using local_numeric_type      = MANDELBROT_NUMBER_TYPE_NAME(365);
    using mandelbrot_config_type  = ckormanyos::mandelbrot::mandelbrot_config<local_numeric_type, 60000U, 1536U>;
    using mandelbrot_numeric_type = typename mandelbrot_config_type::mandelbrot_config_numeric_type;

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

    const mandelbrot_numeric_type dx_half("4.4E-311");
    const mandelbrot_numeric_type cx     ("0.360240443437614363236125244449545308482607807958585750488375814740195346059218100311752936722773426396233731729724987737320035372683285317664532401218521579554288661726564324134702299962817029213329980895208036363104546639698106204384566555001322985619004717862781192694046362748742863016467354574422779443226982622356594130430232458472420816652623492974891730419252651127672782407292315574480207005828774566475024380960675386215814315654794021855269375824443853463117354448779647099224311848192893972572398662626725254769950976527431277402440752868498588785436705371093442460696090720654908973712759963732914849861213100695402602927267843779747314419332179148608587129105289166676461292845685734536033692577618496925170576714796693411776794742904333484665301628662532967079174729170714156810530598764525260869731233845987202037712637770582084286587072766838497865108477149114659838883818795374195150936369987302574377608649625020864292915913378927790344097552591919409137354459097560040374880346637533711271919419723135538377394364882968994646845930838049998854075817859391340445151448381853615103761584177161812057928");
    const mandelbrot_numeric_type cy     ("-0.6413130610648031748603750151793020665794949522823052595561775430644485741727536902556370230689681162370740565537072149790106973211105273740851993394803287437606238596262287731075999483940467161288840614581091294325709988992269165007394305732683208318834672366947550710920088501655704252385244481168836426277052232593412981472237968353661477793530336607247738951625817755401065045362273039788332245567345061665756708689359294516668271440525273653083717877701237756144214394870245598590883973716531691124286669552803640414068523325276808909040317617092683826521501539932397262012011082098721944643118695001226048977430038509470101715555439047884752058334804891389685530946112621573416582482926221804767466258346014417934356149837352092608891639072745930639364693513216719114523328990690069588676087923656657656023794484324797546024248328156586471662631008741349069961493817600100133439721557969263221185095951241491408756751582471307537382827924073746760884081704887902040036056611401378785952452105099242499241003208013460878442953408648178692353788153787229940221611731034405203519945313911627314900851851072122990492499999999999999999991");

  #elif (MANDELBROT_IMAGE_INDEX ==  MANDELBROT_21_ZOOM_VERY_DEEP_01)

    const std::string str_filename = "images/mandelbrot_" + std::string("MANDELBROT_21_ZOOM_VERY_DEEP_01") + ".jpg";

    using local_numeric_type      = MANDELBROT_NUMBER_TYPE_NAME(567);
    using mandelbrot_config_type  = ckormanyos::mandelbrot::mandelbrot_config<local_numeric_type, 160000U, 512U>;
    using mandelbrot_numeric_type = typename mandelbrot_config_type::mandelbrot_config_numeric_type;

    const mandelbrot_numeric_type dx_half("1.1E-501");
    const mandelbrot_numeric_type cx     ("0.360240443437614363236125244449545308482607807958585750488375814740195346059218100311752936722773426396233731729724987737320035372683285317664532401218521579554288661726564324134702299962817029213329980895208036363104546639698106204384566555001322985619004717862781192694046362748742863016467354574422779443226982622356594130430232458472420816652623492974891730419252651127672782407292315574480207005828774566475024380960675386215814315654794021855269375824443853463117354448779647099224311848192893972572398662626725254769950976527431277402440752868498588785436705371093442460696090720654908973712759963732914849861213100695402602927267843779747314419332179148608587129105289166676461292845685734536033692577618496925170576714796693411776794742904333484665301628662532967079174729170714156810530598764525260869731233845987202037712637770582084286587072766838497865108477149114659838883818795374195150936369987302574377608649625020864292915913378927790344097552591919409137354459097560040374880346637533711271919419723135538377394364882968994646845930838049998854075817859391340445151448381853615103761584177161812057928");
    const mandelbrot_numeric_type cy     ("-0.6413130610648031748603750151793020665794949522823052595561775430644485741727536902556370230689681162370740565537072149790106973211105273740851993394803287437606238596262287731075999483940467161288840614581091294325709988992269165007394305732683208318834672366947550710920088501655704252385244481168836426277052232593412981472237968353661477793530336607247738951625817755401065045362273039788332245567345061665756708689359294516668271440525273653083717877701237756144214394870245598590883973716531691124286669552803640414068523325276808909040317617092683826521501539932397262012011082098721944643118695001226048977430038509470101715555439047884752058334804891389685530946112621573416582482926221804767466258346014417934356149837352092608891639072745930639364693513216719114523328990690069588676087923656657656023794484324797546024248328156586471662631008741349069961493817600100133439721557969263221185095951241491408756751582471307537382827924073746760884081704887902040036056611401378785952452105099242499241003208013460878442953408648178692353788153787229940221611731034405203519945313911627314900851851072122990492499999999999999999991");

  #elif (MANDELBROT_IMAGE_INDEX ==  MANDELBROT_22_ZOOM_VERY_DEEP_02)

    const std::string str_filename = "images/mandelbrot_" + std::string("MANDELBROT_22_ZOOM_VERY_DEEP_02") + ".jpg";

    using local_numeric_type      = MANDELBROT_NUMBER_TYPE_NAME(1048);
    using mandelbrot_config_type  = ckormanyos::mandelbrot::mandelbrot_config<local_numeric_type, 700000U, 128U>;
    using mandelbrot_numeric_type = typename mandelbrot_config_type::mandelbrot_config_numeric_type;

    const mandelbrot_numeric_type dx_half("1.1E-990");
    const mandelbrot_numeric_type cx     ("0.360240443437614363236125244449545308482607807958585750488375814740195346059218100311752936722773426396233731729724987737320035372683285317664532401218521579554288661726564324134702299962817029213329980895208036363104546639698106204384566555001322985619004717862781192694046362748742863016467354574422779443226982622356594130430232458472420816652623492974891730419252651127672782407292315574480207005828774566475024380960675386215814315654794021855269375824443853463117354448779647099224311848192893972572398662626725254769950976527431277402440752868498588785436705371093442460696090720654908973712759963732914849861213100695402602927267843779747314419332179148608587129105289166676461292845685734536033692577618496925170576714796693411776794742904333484665301628662532967079174729170714156810530598764525260869731233845987202037712637770582084286587072766838497865108477149114659838883818795374195150936369987302574377608649625020864292915913378927790344097552591919409137354459097560040374880346637533711271919419723135538377394364882968994646845930838049998854075817859391340445151448381853615103761584177161812057928");
    const mandelbrot_numeric_type cy     ("-0.6413130610648031748603750151793020665794949522823052595561775430644485741727536902556370230689681162370740565537072149790106973211105273740851993394803287437606238596262287731075999483940467161288840614581091294325709988992269165007394305732683208318834672366947550710920088501655704252385244481168836426277052232593412981472237968353661477793530336607247738951625817755401065045362273039788332245567345061665756708689359294516668271440525273653083717877701237756144214394870245598590883973716531691124286669552803640414068523325276808909040317617092683826521501539932397262012011082098721944643118695001226048977430038509470101715555439047884752058334804891389685530946112621573416582482926221804767466258346014417934356149837352092608891639072745930639364693513216719114523328990690069588676087923656657656023794484324797546024248328156586471662631008741349069961493817600100133439721557969263221185095951241491408756751582471307537382827924073746760884081704887902040036056611401378785952452105099242499241003208013460878442953408648178692353788153787229940221611731034405203519945313911627314900851851072122990492499999999999999999991");

  #elif (MANDELBROT_IMAGE_INDEX ==  MANDELBROT_30_ZOOM_ANOTHER_00)

    const std::string str_filename = "images/mandelbrot_" + std::string("MANDELBROT_30_ZOOM_ANOTHER_00") + ".jpg";

    using local_numeric_type      = MANDELBROT_NUMBER_TYPE_NAME(287);
    using mandelbrot_config_type  = ckormanyos::mandelbrot::mandelbrot_config<local_numeric_type, 60000U, 2048U>;
    using mandelbrot_numeric_type = typename mandelbrot_config_type::mandelbrot_config_numeric_type;

    const mandelbrot_numeric_type dx_half("9.5E-191");
    const mandelbrot_numeric_type cx     ("-1.740062382579339905220844167065825638296641720436171866879862418461182919644153056054840718339483225743450008259172138785492983677893366503417299549623738838303346465461290768441055486136870719850559269507357211790243666940134793753068611574745943820712885258222629105433648695946003865");
    const mandelbrot_numeric_type cy     ("0.0281753397792110489924115211443195096875390767429906085704013095958801743240920186385400814658560553615695084486774077000669037710191665338060418999324320867147028768983704831316527873719459264592084600433150333362859318102017032958074799966721030307082150171994798478089798638258639934");

  #elif (MANDELBROT_IMAGE_INDEX ==  MANDELBROT_31_ZOOM_ANOTHER_01)

    const std::string str_filename = "images/mandelbrot_" + std::string("MANDELBROT_31_ZOOM_ANOTHER_01") + ".jpg";

    using local_numeric_type      = MANDELBROT_NUMBER_TYPE_NAME(287);
    using mandelbrot_config_type  = ckormanyos::mandelbrot::mandelbrot_config<local_numeric_type, 60000U, 2048U>;
    using mandelbrot_numeric_type = typename mandelbrot_config_type::mandelbrot_config_numeric_type;

    const mandelbrot_numeric_type dx_half("6.4E-201");
    const mandelbrot_numeric_type cx     ("-1.740062382579339905220844167065825638296641720436171866879862418461182919644153056054840718339483225743450008259172138785492983677893366503417299549623738838303346465461290768441055486136870719850559269507357211790243666940134793753068611574745943820712885258222629105433648695946003865");
    const mandelbrot_numeric_type cy     ("0.0281753397792110489924115211443195096875390767429906085704013095958801743240920186385400814658560553615695084486774077000669037710191665338060418999324320867147028768983704831316527873719459264592084600433150333362859318102017032958074799966721030307082150171994798478089798638258639934");

  #elif (MANDELBROT_IMAGE_INDEX ==  MANDELBROT_32_ZOOM_ANOTHER_02)

    const std::string str_filename = "images/mandelbrot_" + std::string("MANDELBROT_32_ZOOM_ANOTHER_02") + ".jpg";

    using local_numeric_type      = MANDELBROT_NUMBER_TYPE_NAME(287);
    using mandelbrot_config_type  = ckormanyos::mandelbrot::mandelbrot_config<local_numeric_type, 60000U, 2048U>;
    using mandelbrot_numeric_type = typename mandelbrot_config_type::mandelbrot_config_numeric_type;

    const mandelbrot_numeric_type dx_half("4.9E-211");
    const mandelbrot_numeric_type cx     ("-1.740062382579339905220844167065825638296641720436171866879862418461182919644153056054840718339483225743450008259172138785492983677893366503417299549623738838303346465461290768441055486136870719850559269507357211790243666940134793753068611574745943820712885258222629105433648695946003865");
    const mandelbrot_numeric_type cy     ("0.0281753397792110489924115211443195096875390767429906085704013095958801743240920186385400814658560553615695084486774077000669037710191665338060418999324320867147028768983704831316527873719459264592084600433150333362859318102017032958074799966721030307082150171994798478089798638258639934");

  #else

    #error: Mandelbrot image type is not defined!

  #endif

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
