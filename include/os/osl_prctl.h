/***********************************************************************
 *
 *  Copyright (c) 2015 sphantix
 *  All Rights Reserved
 *
# 
# 
# 
#
 * 
 ************************************************************************/

#ifndef __OSL_PRCTL_H__
#define __OSL_PRCTL_H__

#include <sys/types.h>
#include <unistd.h>
#include "utl.h"

void oslPrctl_getProcessName(pid_t pid, char *name);
#endif /* __OSL_PRCTL_H__ */
