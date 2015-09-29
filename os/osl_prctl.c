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
#include "osl_prctl.h"

void oslPrctl_getPathName(pid_t pid, char *name)
{
    FILE *fp;
    char cmd[BUFLEN_256] = {'\0'};

    sprintf(cmd,"readlink /proc/%d/exe",pid);
    if((fp = popen(cmd,"r")) != NULL)
        if(fscanf(fp,"%s\n",name) != -1)
            ;

    pclose(fp);
    return;
}
