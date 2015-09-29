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
CFLAGS += -fPIC -Werror -Wfatal-errors

#static library use 'ar' command
AR = ar

#set your inc and lib
INC = -I. \
	  -I../include \
	  -I../include/os \

#make target lib and relevant obj
PRG = osl.a
OBJS = osl_logging.o osl_prctl.o osl_time.o

#all target  
all: $(PRG)
$(PRG): $(OBJS)
	$(AR) -rcs $@ $(OBJS)

.SUFFIXES: .c .o
.c.o:
	$(CC) $(CFLAGS) $(INC) -c $*.c -o $*.o

.PRONY:clean
clean:
	@echo "Removing linked and compiled files......"
	rm -f $(OBJS) $(PRG)

#
# Include the rule for making dependency files.
# The '-' in front of the second include suppresses
# error messages when make cannot find the .d files.
# It will just regenerate them.
# See Section 4.14 of Gnu Make.
#

-include $(OBJS:.o=.d)
