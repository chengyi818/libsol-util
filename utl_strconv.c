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
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>     /* for isDigit, really should be in oal_strconv.c */
#include <sys/stat.h>  /* this really should be in oal_strconv.c */
#include <arpa/inet.h> /* for inet_aton */
#include <sys/time.h> /* for inet_aton */

#include "utl_strconv.h"

char *utlStr_strcpy(char *dest, const char *src)
{
   char emptyStr = '\0';
   char *str1 = (char *)dest;
   char *str2 = (char *)src;

   if (str1 == NULL)
   {
      str1 = &emptyStr;
   }
   if (str2 == NULL)
   {
      str2 = &emptyStr;
   }

   return strcpy(str1, str2);   
}

SINT32 utlStr_strlen(const char *src)
{
   char emptyStr = '\0';
   char *str = (char *)src;
   
   if(src == NULL)
   {
      str = &emptyStr;
   }	

   return strlen(str);
} 

char *utlStr_strdup(const char *src)
{
   char *str = (char *)src;

   if (str == NULL)
   {
       return NULL;
   }

   return strdup(str);   
}

char *utlStr_getBaseName(char *path)
{
    char *ptr = NULL;
    if((ptr = strchr(path,'/')) != NULL)
        return utlStr_getBaseName(ptr+1);
    else
        return path;
}
