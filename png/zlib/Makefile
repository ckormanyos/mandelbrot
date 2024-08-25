###############################################################################
#  Copyright Sebastian Streubel 2024.
#  Distributed under the Boost Software License,
#  Version 1.0. (See accompanying file LICENSE_1_0.txt
#  or copy at http://www.boost.org/LICENSE_1_0.txt)
#

# Very simple makefile for building libz.a

# cd png/zlib
# make all

# The result should be png/zlib/zlib-1.3.1.1-2024/obj/libz.a
# Link this library to your project needing PNGcompression

SRC_DIR    = $(CURDIR)/zlib-1.3.1.1-2024
OBJ_DIR    = $(SRC_DIR)/obj

CC         = g++

CFLAGS     = -x c                              \
             -O2                               \
             -std=c11                          \
             -march=native                     \
             -DZ_SOLO                          \
             -Wall                             \
             -Wextra                           \
             -Wpedantic                        \
             -I.

all : clean $(OBJ_DIR)/libz.a

clean:
	rm -rf $(OBJ_DIR)/*.o
	rm -rf $(OBJ_DIR)/libz.a

$(OBJ_DIR)/libz.a :
	@echo 'make temporary obj directory'
	mkdir -p $(OBJ_DIR)
	@echo
	@echo 'compile libzlib-1.3.1.1-2024 source files'
	$(CC) $(CFLAGS) -c $(SRC_DIR)/adler32.c  -o $(OBJ_DIR)/adler32.o
	$(CC) $(CFLAGS) -c $(SRC_DIR)/compress.c -o $(OBJ_DIR)/compress.o
	$(CC) $(CFLAGS) -c $(SRC_DIR)/crc32.c    -o $(OBJ_DIR)/crc32.o
	$(CC) $(CFLAGS) -c $(SRC_DIR)/deflate.c  -o $(OBJ_DIR)/deflate.o
	$(CC) $(CFLAGS) -c $(SRC_DIR)/infback.c  -o $(OBJ_DIR)/infback.o
	$(CC) $(CFLAGS) -c $(SRC_DIR)/inffast.c  -o $(OBJ_DIR)/inffast.o
	$(CC) $(CFLAGS) -c $(SRC_DIR)/inflate.c  -o $(OBJ_DIR)/inflate.o
	$(CC) $(CFLAGS) -c $(SRC_DIR)/inftrees.c -o $(OBJ_DIR)/inftrees.o
	$(CC) $(CFLAGS) -c $(SRC_DIR)/trees.c    -o $(OBJ_DIR)/trees.o
	$(CC) $(CFLAGS) -c $(SRC_DIR)/uncompr.c  -o $(OBJ_DIR)/uncompr.o
	$(CC) $(CFLAGS) -c $(SRC_DIR)/zutil.c    -o $(OBJ_DIR)/zutil.o
	@echo
	@echo 'creating archive libz.a'
	ar rcs $(OBJ_DIR)/libz.a $(OBJ_DIR)/*.o
