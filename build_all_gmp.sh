#!/bin/bash
#
#  Copyright Christopher Kormanyos 2024 - 2025.
#  Distributed under the Boost Software License,
#  Version 1.0. (See accompanying file LICENSE_1_0.txt
#  or copy at http://www.boost.org/LICENSE_1_0.txt)
#

# cd /mnt/c/Users/ckorm/Documents/Ks/PC_Software/NumericalPrograms/mandelbrot
# ./build_all.sh --boost=/mnt/c/boost/boost_1_85_0 --my_cc=g++ --stdcc=c++20

boost=
my_cc=g++

for arg in "$@"; do
  case $arg in
    --boost=*)
      boost="${arg#*=}"
      shift
      ;;
    --my_cc=*)
      my_cc="${arg#*=}"
      shift
      ;;
    --stdcc=*)
      stdcc="${arg#*=}"
      shift
      ;;
    *)
      ;;
  esac
done

echo "boost: $boost"
echo "my_cc: $my_cc"
echo "stdcc: $stdcc"

MY_BOOST_INC=-I$boost

MY_GCC=$my_cc

MY_STD=$stdcc

echo 'make the jpeg-6b library'
cd jpeg
make all
cd ..
echo

echo 'make the libpng-1.6.44.git-2024 library'
cd png/libpng
make all
cd ../..
echo

echo 'make the libzlib-1.3.1.1-2024 library'
cd png/zlib
make all
cd ../..
echo

echo 'verify existence of libs'
ls -la ./png/libpng/libpng-1.6.44.git-2024/obj/libpng16.a ./png/zlib/zlib-1.3.1.1-2024/obj/libz.a ./jpeg/jpeg-6b-2022/obj/libjpeg-6b.a
res_makelibs=$?
echo

echo 'compiler version'
echo
$MY_GCC -v
echo

echo 'compile test/test_mandelbrot.cpp to test_mandelbrot.o'
$MY_GCC -x c++ -c -finline-functions -march=native -mtune=native -O3 -Wall -Wextra -Wmissing-include-dirs -std=$MY_STD -DMANDELBROT_USE_GMP_FLOAT -I. -Ipng/zlib/zlib-1.3.1.1-2024 -Ipng/libpng/libpng-1.6.44.git-2024 -Ijpeg/jpeg-6b-2022 $MY_BOOST_INC -pthread test/test_mandelbrot.cpp -o test_mandelbrot.o
echo

echo 'link test_mandelbrot.o with libraries to create test_mandelbrot.exe'
$MY_GCC -x none -march=native -mtune=native test_mandelbrot.o ./png/libpng/libpng-1.6.44.git-2024/obj/libpng16.a ./png/zlib/zlib-1.3.1.1-2024/obj/libz.a ./jpeg/jpeg-6b-2022/obj/libjpeg-6b.a -lpthread -lgmp -o test_mandelbrot.exe
echo

echo 'verify existence of test_mandelbrot.exe'
ls -la ./test_mandelbrot.exe
res_maketest=$?
echo

result_total=$((res_makelibs+res_maketest))


echo "res_makelibs : "  "$res_makelibs"
echo "res_maketest : "  "$res_maketest"
echo "result_total : "  "$result_total"
echo

exit $result_total
