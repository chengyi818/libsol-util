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
AR = ar

HDR_INC = -I. \
		  -I.. \
		  -I../include \
		  -I../include/os \

LDFLAGS += -L.
LIBS = -lsol-util
CFLAGS += -fPIC -Werror -Wfatal-errors $(HDR_INC) $(LIBS)

#make target lib and relevant obj
PRG = test
OBJS = test.o

#all target  
all: $(PRG)
$(PRG): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $(OBJS)

.SUFFIXES: .c .o
.c.o:
	$(CC) $(CFLAGS) -c $*.c -o $*.o

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