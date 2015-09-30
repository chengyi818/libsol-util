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

#ifndef __UTL_STRCONV_H__
#define __UTL_STRCONV_H__

#include "utl.h"

char *utlStr_strcpy(char *dest, const char *src);
SINT32 utlStr_strlen(const char *src);
char *utlStr_strdup(const char *src);
char *utlStr_getBaseName(char *path);
#endif /* __UTL_STRCONV_H__ */
