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
CFLAGS = -fPIC -Werror -Wfatal-errors

#set your inc and lib
INC = -I. \
	  -I./include \
	  -I./include/os \

CURR_DIR := $(shell pwd)
OSDIR = $(CURR_DIR)/os
#make target lib and relevant obj
PRG = libutil.so
OBJS = utl_logging.o utl_prctl.o utl_time.o utl_strconv.o
INNER_LIBS = os/osl.a
OUTTER_LIBS = 

#all target  
all: $(PRG)
$(PRG): $(INNER_LIBS) $(OBJS)
	$(CC) $(CFLAGS) $(INC) -shared -Wl,--whole-archive,-soname,$@ -o $@ \
	      $(OBJS) $(OSDIR)/osl.a \
	      -Wl,-lcrypt -Wl,--no-whole-archive

os/osl.a:
	$(MAKE) -C os 

.SUFFIXES: .c .o
.c.o:
	$(CC) $(CFLAGS) $(INC) -c $*.c -o $*.o

.PRONY:clean
clean:
	@$(MAKE) clean -C os
	rm -f $(OBJS) $(PRG)

#
# Include the rule for making dependency files.
# The '-' in front of the second include suppresses
# error messages when make cannot find the .d files.
# It will just regenerate them.
# See Section 4.14 of Gnu Make.
#

-include $(OBJS:.o=.d)
