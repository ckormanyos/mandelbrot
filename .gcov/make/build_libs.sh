#!/usr/bin/env bash
#
#  Copyright Christopher Kormanyos 2022 - 2025.
#  Distributed under the Boost Software License,
#  Version 1.0. (See accompanying file LICENSE_1_0.txt
#  or copy at http://www.boost.org/LICENSE_1_0.txt)
#

if [[ "$1" != "" ]]; then
    GCC="$1"
else
    GCC=g++
fi

cd ../..

echo "query GCC version"
g++ -v
echo

echo "build libjpeg"
echo
cd jpeg
make all
echo

cd ..
echo "build libpng"
echo
cd png/libpng
make all
echo

cd ../..
echo "build libz"
echo
cd png/zlib
make all
echo

cd ../..
echo "verify archive existences"
echo
ls -la ./jpeg/jpeg-6b-2022/obj/libjpeg-6b.a ./png/libpng/libpng-1.6.44.git-2024/obj/libpng16.a ./png/zlib/zlib-1.3.1.1-2024/obj/libz.a
result=$?

echo
echo "result: $result"
echo

exit $result
