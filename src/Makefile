PWD := $(shell pwd)

sources = $(wildcard *.c) $(wildcard *.cpp)
programs = sudoku

include $(PWD)/../common.mk

$(programs): $(LIB_BOOST_THREAD) -lboost_program_options
