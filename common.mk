################################################################################
# Commands

AR              := ar
CC              := gcc
CXX             := g++
MKDIR           := mkdir -p
MV              := mv -f
RM              := rm -f
SED             := sed
TEST            := test

################################################################################
# Flags

OPTIMIZER       := -O2
INCLUDES        :=
LIBS            :=
CFLAGS          :=
CPPFLAGS        := -Wall $(OPTIMIZER) $(INCLUDES)
CXXFLAGS        :=
LDFLAGS         := $(OPTIMIZER)
OS              := $(shell uname -s)
SHELL           := sh
TARGET_ARCH     :=

ifdef DEBUG
    CPPFLAGS += -g -DDEBUG
    LDFLAGS  += -g -DDEBUG
endif

# gprof
ifdef PROF
    CPPFLAGS += -pg
    LDFLAGS  += -pg
endif

ifeq ($(OS), AIX)
    CPPFLAGS += -maix64
    LDFLAGS  += -maix64
endif

ifeq ($(OS), HP-UX)
    CC       := /opt/hp-gcc/bin/gcc
    CXX      := /opt/hp-gcc/bin/g++
    CPPFLAGS += -mlp64
    LDFLAGS  += -mlp64
endif

ifeq ($(OS), Linux)
    CPPFLAGS += -m64
    LDFLAGS  += -m64
endif

ifeq ($(OS), Solaris)
    CPPFLAGS += -m64
    LDFLAGS  += -m64
endif

LIB_BOOST_THREAD            := -lboost_thread
ifeq ($(OS), Linux)
    ifneq ($(wildcard /usr/lib64/libboost_thread-mt.so),)
        LIB_BOOST_THREAD    := -lboost_thread-mt
    endif
endif

################################################################################
# Functions

# $(call generated-source, source-file-list)
generated-source = $(subst .y,.c,$(filter %.y,$1)) \
                   $(subst .y,.h,$(filter %.y,$1)) \
                   $(subst .l,.c,$(filter %.l,$1))

# $(call source-to-object, source-file-list)
source-to-object = $(subst .c,.o,$(filter %.c,$1)) \
                   $(subst .cpp,.o,$(filter %.cpp,$1)) \
                   $(subst .y,.o,$(filter %.y,$1)) \
                   $(subst .l,.o,$(filter %.l,$1))

# $(call make-library, library-name, source-file-list)
define make-library
  libraries += $(BINARY_DIR)/$1
  sources   += $2

  $1: $(call source-dir-to-binary-dir, \
             $(subst .c,.o,$(filter %.c,$2)) \
             $(subst .y,.o,$(filter %.y,$2)) \
             $(subst .l,.o,$(filter %.l,$2)))
	$(AR) $(ARFLAGS) $$@ $$^
endef

################################################################################
# Targets

objects         = $(call source-to-object,$(sources))
dependencies    = $(subst .o,.d,$(objects))

vpath %.h $(TOP)/include
vpath %.y $(TOP)
vpath %.l $(TOP)
vpath %.c $(TOP)

.PHONY: all
all: $(programs) $(libraries)

.PHONY: clean
clean:
	$(RM) $(programs) $(libraries) $(objects) $(dependencies) $(extra_clean)

ifneq "$(MAKECMDGOALS)" "clean"
    include $(dependencies)
endif

%.c %.h: %.y
	$(YACC.y) --defines $<
	$(MV) y.tab.c $*.c
	$(MV) y.tab.h $*.h

%.d: %.c
	$(CC) $(CFLAGS) $(CPPFLAGS) $(TARGET_ARCH) -M $< | $(SED) 's,\($(notdir $*)\.o\) *:,$(dir $@)\1 $@: ,' > $@.tmp
	$(MV) $@.tmp $@

%.d: %.cpp
	$(CXX) $(CXXFLAGS) $(CPPFLAGS) $(TARGET_ARCH) -M $< | $(SED) 's,\($(notdir $*)\.o\) *:,$(dir $@)\1 $@: ,' > $@.tmp
	$(MV) $@.tmp $@

