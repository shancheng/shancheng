PWD := $(shell pwd)

sources = $(wildcard *.c) $(wildcard *.cpp)
programs = sqlite_busyhandler_test sqlite_concurrency_test

include $(PWD)/../common.mk

$(programs): $(LIB_BOOST_THREAD) -lboost_program_options -lsqlite3
