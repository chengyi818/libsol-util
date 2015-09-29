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

#include "utl_strconv.h"

void utlPrctl_getProcessName(char *name)
{
    char path[BUFLEN_256] = {'\0'};

    oslPrctl_getPathName(path);
    utlStr_strcpy(name, utlStr_getBaseName(path));

    return;
}
