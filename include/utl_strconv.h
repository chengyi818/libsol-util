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

void utlStr_strToLower(char *string);
void utlStr_strToUpper(char *string);
SINT32 utlStr_strcmp(const char *s1, const char *s2);
SINT32 utlStr_strcasecmp(const char *s1, const char *s2);
SINT32 utlStr_strncmp(const char *s1, const char *s2, SINT32 n);
SINT32 utlStr_strncasecmp(const char *s1, const char *s2, SINT32 n);
char *utlStr_strstr(const char *s1, const char *s2);
char *utlStr_strncpy(char *dest, const char *src, SINT32 dlen);
char *utlStr_strcpy(char *dest, const char *src);
char *utlStr_strcat(char *dest, const char *src);
SINT32 utlStr_strlen(const char *src);
char *utlStr_strdup(const char *src);
char *utlStr_getBaseName(char *path);
#endif /* __UTL_STRCONV_H__ */
