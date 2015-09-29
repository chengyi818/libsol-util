#*************************************************
# *
# *  Copyright (c) 2015  PHICOMM Corporation
# *  All Rights Reserved
# *
# * ***********************************************
#
# In most cases, you only need to modify this first section.

EXE = hsc

DIRS = main util sysIntf jsonParser
DIR_LIBS = main/main.a sysIntf/sysIntf.a jsonParser/jsonParser.a util/util.a

LIBS = -lcms_msg $(CMS_COMMON_LIBS) -ldl $(CMS_CORE_LIBS) 

all dynamic install: $(EXE) generic_exe_install

clean: generic_clean hsc_dir_clean
	rm -f $(INSTALL_DIR)/bin/$(EXE)


hsc_dir_clean:
	for dir in $(DIRS); do \
		$(MAKE) -C $$dir clean; \
	done

.FORCE:

#
# Set our CommEngine directory (by splitting the pwd into two words
# at /userspace and taking the first word only).
# Then include the common defines under CommEngine.
#
CURR_DIR := $(shell pwd)
BUILD_DIR:=$(subst /userspace, /userspace,$(CURR_DIR))
BUILD_DIR:=$(word 1, $(BUILD_DIR))

include $(BUILD_DIR)/make.common

#
# Private apps and libs are allowed to include header files from the
# private and public directories.
#
# WARNING: Do not modify this section unless you understand the
# license implications of what you are doing.
#
ALLOWED_INCLUDE_PATHS := -I.\
                         -I$(BUILD_DIR)/userspace/public/include  \
                         -I$(BUILD_DIR)/userspace/public/include/$(OALDIR) \
                         -I$(BUILD_DIR)/userspace/private/include  \
                         -I$(BUILD_DIR)/userspace/private/include/$(OALDIR) \
                         -I$(BUILD_DIR)/userspace/private/libs/cms_core/linux

#
# Private apps and libs are allowed to link with libraries from the
# private and public directories.
#
# WARNING: Do not modify this section unless you understand the
# license implications of what you are doing.
#
ALLOWED_LIB_DIRS := /lib:/lib/private:/lib/public

#
# Implicit rule will make the .c into a .o
# Implicit rule is $(CC) -c $(CPPFLAGS) $(CFLAGS)
# See Section 10.2 of Gnu Make manual
# Assemble the libraries.  Need to specify main.o one more time to resolve dependencies.
#
$(EXE): $(DIR_LIBS)
	$(CC) -o $@ $(DIR_LIBS) -Wl,-rpath,$(CMS_LIB_RPATH) $(CMS_LIB_PATH) $(LIBS)


util/util.a: .FORCE
	$(MAKE) -C util

sysIntf/sysIntf.a: .FORCE
	$(MAKE) -C sysIntf

jsonParser/jsonParser.a: .FORCE
	$(MAKE) -C jsonParser

main/main.a: .FORCE
	$(MAKE) -C main

#
# Include the rule for making dependency files.
# The '-' in front of the second include suppresses
# error messages when make cannot find the .d files.
# It will just regenerate them.
# See Section 4.14 of Gnu Make.
#

include $(BUILD_DIR)/make.deprules

-include $(OBJS:.o=.d)
