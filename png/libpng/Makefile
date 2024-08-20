###############################################################################
#  Copyright Sebastian Streubel 2024.
#  Distributed under the Boost Software License,
#  Version 1.0. (See accompanying file LICENSE_1_0.txt
#  or copy at http://www.boost.org/LICENSE_1_0.txt)
#

# Very simple makefile for building libpng16.a

# cd png/libpng
# make all

# The result should be png/tmpPng/obj/libpng16.a
# Link this library to your project needing PNG.

SRC_DIR    = $(CURDIR)
OBJ_DIR    = $(SRC_DIR)/../tmpPng/obj

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
             -I.

all : clean $(OBJ_DIR)/libpng16.a

clean:
	rm -rf $(OBJ_DIR)/*.o
	rm -rf $(OBJ_DIR)/libpng16.a

$(OBJ_DIR)/libpng16.a :
	@echo make temporary obj directory
	mkdir -p $(OBJ_DIR)
	@echo compile libpng16 source files
	$(CC) $(CFLAGS) -c $(SRC_DIR)/png.c       -o $(OBJ_DIR)/png.o
	$(CC) $(CFLAGS) -c $(SRC_DIR)/pngerror.c  -o $(OBJ_DIR)/pngerror.o
	$(CC) $(CFLAGS) -c $(SRC_DIR)/pngget.c    -o $(OBJ_DIR)/pngget.o
	$(CC) $(CFLAGS) -c $(SRC_DIR)/pngmem.c    -o $(OBJ_DIR)/pngmem.o
	$(CC) $(CFLAGS) -c $(SRC_DIR)/pngpread.c  -o $(OBJ_DIR)/pngpread.o
	$(CC) $(CFLAGS) -c $(SRC_DIR)/pngread.c   -o $(OBJ_DIR)/pngread.o
	$(CC) $(CFLAGS) -c $(SRC_DIR)/pngrio.c    -o $(OBJ_DIR)/pngrio.o
	$(CC) $(CFLAGS) -c $(SRC_DIR)/pngrtran.c  -o $(OBJ_DIR)/pngrtran.o
	$(CC) $(CFLAGS) -c $(SRC_DIR)/pngrutil.c  -o $(OBJ_DIR)/pngrutil.o
	$(CC) $(CFLAGS) -c $(SRC_DIR)/pngset.c    -o $(OBJ_DIR)/pngset.o
	$(CC) $(CFLAGS) -c $(SRC_DIR)/pngtrans.c  -o $(OBJ_DIR)/pngtrans.o
	$(CC) $(CFLAGS) -c $(SRC_DIR)/pngwio.c    -o $(OBJ_DIR)/pngwio.o
	$(CC) $(CFLAGS) -c $(SRC_DIR)/pngwrite.c  -o $(OBJ_DIR)/pngwrite.o
	$(CC) $(CFLAGS) -c $(SRC_DIR)/pngwtran.c  -o $(OBJ_DIR)/pngwtran.o
	$(CC) $(CFLAGS) -c $(SRC_DIR)/pngwutil.c  -o $(OBJ_DIR)/pngwutil.o


	@echo creating archive libpng16.a
	ar rcs $(OBJ_DIR)/libpng16.a $(OBJ_DIR)/*.o
