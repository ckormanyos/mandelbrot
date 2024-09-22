###############################################################################
#  Copyright Christopher Kormanyos 2022 - 2024.
#  Distributed under the Boost Software License,
#  Version 1.0. (See accompanying file LICENSE_1_0.txt
#  or copy at http://www.boost.org/LICENSE_1_0.txt)
#

# Very simple makefile for building libjpeg-6b.a

# cd jpeg
# make all

# The result should be jpeg/jpeg-6b-2022/obj/libjpeg-6b.a
# Link this library to your project needing JPEG.

SRC_DIR    = $(CURDIR)/jpeg-6b-2022
OBJ_DIR    = $(SRC_DIR)/obj

CC         = g++

CFLAGS     = -x c                              \
             -O2                               \
             -std=c11                          \
             -march=native                     \
             -Wall                             \
             -Wextra                           \
             -Wpedantic                        \
             -Wconversion                      \
             -Wsign-conversion                 \
             -Werror                           \
             -I.

all : clean $(OBJ_DIR)/libjpeg-6b.a

clean:
	rm -rf $(OBJ_DIR)/*.o
	rm -rf $(OBJ_DIR)/libjpeg-6b.a

$(OBJ_DIR)/libjpeg-6b.a :
	@-echo 'make temporary obj directory'
	@-mkdir -p $(OBJ_DIR)
	@-echo
	@-echo 'compile libjpeg-6b source files'
	$(CC) $(CFLAGS) -c $(SRC_DIR)/jcapimin.c -o $(OBJ_DIR)/jcapimin.o
	$(CC) $(CFLAGS) -c $(SRC_DIR)/jcapistd.c -o $(OBJ_DIR)/jcapistd.o
	$(CC) $(CFLAGS) -c $(SRC_DIR)/jccoefct.c -o $(OBJ_DIR)/jccoefct.o
	$(CC) $(CFLAGS) -c $(SRC_DIR)/jccolor.c  -o $(OBJ_DIR)/jccolor.o
	$(CC) $(CFLAGS) -c $(SRC_DIR)/jcdctmgr.c -o $(OBJ_DIR)/jcdctmgr.o
	$(CC) $(CFLAGS) -c $(SRC_DIR)/jchuff.c   -o $(OBJ_DIR)/jchuff.o
	$(CC) $(CFLAGS) -c $(SRC_DIR)/jcinit.c   -o $(OBJ_DIR)/jcinit.o
	$(CC) $(CFLAGS) -c $(SRC_DIR)/jcmainct.c -o $(OBJ_DIR)/jcmainct.o
	$(CC) $(CFLAGS) -c $(SRC_DIR)/jcmarker.c -o $(OBJ_DIR)/jcmarker.o
	$(CC) $(CFLAGS) -c $(SRC_DIR)/jcmaster.c -o $(OBJ_DIR)/jcmaster.o
	$(CC) $(CFLAGS) -c $(SRC_DIR)/jcomapi.c  -o $(OBJ_DIR)/jcomapi.o
	$(CC) $(CFLAGS) -c $(SRC_DIR)/jcparam.c  -o $(OBJ_DIR)/jcparam.o
	$(CC) $(CFLAGS) -c $(SRC_DIR)/jcphuff.c  -o $(OBJ_DIR)/jcphuff.o
	$(CC) $(CFLAGS) -c $(SRC_DIR)/jcprepct.c -o $(OBJ_DIR)/jcprepct.o
	$(CC) $(CFLAGS) -c $(SRC_DIR)/jcsample.c -o $(OBJ_DIR)/jcsample.o
	$(CC) $(CFLAGS) -c $(SRC_DIR)/jctrans.c  -o $(OBJ_DIR)/jctrans.o
	$(CC) $(CFLAGS) -c $(SRC_DIR)/jdapimin.c -o $(OBJ_DIR)/jdapimin.o
	$(CC) $(CFLAGS) -c $(SRC_DIR)/jdapistd.c -o $(OBJ_DIR)/jdapistd.o
	$(CC) $(CFLAGS) -c $(SRC_DIR)/jdatadst.c -o $(OBJ_DIR)/jdatadst.o
	$(CC) $(CFLAGS) -c $(SRC_DIR)/jdcoefct.c -o $(OBJ_DIR)/jdcoefct.o
	$(CC) $(CFLAGS) -c $(SRC_DIR)/jdcolor.c  -o $(OBJ_DIR)/jdcolor.o
	$(CC) $(CFLAGS) -c $(SRC_DIR)/jddctmgr.c -o $(OBJ_DIR)/jddctmgr.o
	$(CC) $(CFLAGS) -c $(SRC_DIR)/jdinput.c  -o $(OBJ_DIR)/jdinput.o
	$(CC) $(CFLAGS) -c $(SRC_DIR)/jdmainct.c -o $(OBJ_DIR)/jdmainct.o
	$(CC) $(CFLAGS) -c $(SRC_DIR)/jdmarker.c -o $(OBJ_DIR)/jdmarker.o
	$(CC) $(CFLAGS) -c $(SRC_DIR)/jdmaster.c -o $(OBJ_DIR)/jdmaster.o
	$(CC) $(CFLAGS) -c $(SRC_DIR)/jdmerge.c  -o $(OBJ_DIR)/jdmerge.o
	$(CC) $(CFLAGS) -c $(SRC_DIR)/jdphuff.c  -o $(OBJ_DIR)/jdphuff.o
	$(CC) $(CFLAGS) -c $(SRC_DIR)/jdpostct.c -o $(OBJ_DIR)/jdpostct.o
	$(CC) $(CFLAGS) -c $(SRC_DIR)/jdsample.c -o $(OBJ_DIR)/jdsample.o
	$(CC) $(CFLAGS) -c $(SRC_DIR)/jerror.c   -o $(OBJ_DIR)/jerror.o
	$(CC) $(CFLAGS) -c $(SRC_DIR)/jfdctflt.c -o $(OBJ_DIR)/jfdctflt.o
	$(CC) $(CFLAGS) -c $(SRC_DIR)/jfdctfst.c -o $(OBJ_DIR)/jfdctfst.o
	$(CC) $(CFLAGS) -c $(SRC_DIR)/jfdctint.c -o $(OBJ_DIR)/jfdctint.o
	$(CC) $(CFLAGS) -c $(SRC_DIR)/jidctflt.c -o $(OBJ_DIR)/jidctflt.o
	$(CC) $(CFLAGS) -c $(SRC_DIR)/jidctfst.c -o $(OBJ_DIR)/jidctfst.o
	$(CC) $(CFLAGS) -c $(SRC_DIR)/jidctint.c -o $(OBJ_DIR)/jidctint.o
	$(CC) $(CFLAGS) -c $(SRC_DIR)/jidctred.c -o $(OBJ_DIR)/jidctred.o
	$(CC) $(CFLAGS) -c $(SRC_DIR)/jmemansi.c -o $(OBJ_DIR)/jmemansi.o
	$(CC) $(CFLAGS) -c $(SRC_DIR)/jmemmgr.c  -o $(OBJ_DIR)/jmemmgr.o
	$(CC) $(CFLAGS) -c $(SRC_DIR)/jquant1.c  -o $(OBJ_DIR)/jquant1.o
	$(CC) $(CFLAGS) -c $(SRC_DIR)/jquant2.c  -o $(OBJ_DIR)/jquant2.o
	$(CC) $(CFLAGS) -c $(SRC_DIR)/jutils.c   -o $(OBJ_DIR)/jutils.o
	@-echo
	@-echo 'creating archive libjpeg-6b.a'
	@-ar rcs $(OBJ_DIR)/libjpeg-6b.a $(OBJ_DIR)/*.o
