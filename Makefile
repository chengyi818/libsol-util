#*************************************************
# *
# *  Copyright (c) 2015 sphantix 
# *  All Rights Reserved
# *
# * ***********************************************
# #
#
#set your own environment option  
CC = gcc

HDR_INC = -I. \
		  -I./include \
		  -I./include/os \

LDFLAGS = -L.
CFLAGS += -fPIC -Werror -Wfatal-errors $(HDR_INC)

LIB_DIR=/usr/lib
CURR_DIR := $(shell pwd)
OSDIR = $(CURR_DIR)/os

#make target lib and relevant obj, sol is short for sphantix's own lib
PRG = libsol-util.so
OBJS = utl_logging.o utl_prctl.o utl_time.o utl_strconv.o
INNER_LIBS = os/osl.a
OUTTER_LIBS = 

#all target  
all: $(PRG)
$(PRG): $(INNER_LIBS) $(OBJS)
	$(CC) $(CFLAGS) -shared -Wl,--whole-archive,-soname,$@ -o $@ \
	      $(OBJS) $(OSDIR)/osl.a \
	      -Wl,-lcrypt -Wl,--no-whole-archive

os/osl.a:
	$(MAKE) -C os 

.SUFFIXES: .c .o
.c.o:
	$(CC) $(CFLAGS) -c $*.c -o $*.o

.PRONY:clean install
clean:
	@$(MAKE) clean -C os
	rm -f $(OBJS) $(PRG)

install:$(PRG)
	install -m 755 $(PRG) $(LIB_DIR)

#
# Include the rule for making dependency files.
# The '-' in front of the second include suppresses
# error messages when make cannot find the .d files.
# It will just regenerate them.
# See Section 4.14 of Gnu Make.
#

-include $(OBJS:.o=.d)
