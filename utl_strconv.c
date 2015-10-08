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
#include "utl_logging.h"

void utlStr_strToLower(char *string)
{
   char *ptr = string;
   for (ptr = string; *ptr; ptr++)
   {
       *ptr = tolower(*ptr);
   }
}

void utlStr_strToUpper(char *string)
{
   char *ptr = string;
   for (ptr = string; *ptr; ptr++)
   {
       *ptr = toupper(*ptr);
   }
}

SINT32 utlStr_strcmp(const char *s1, const char *s2)
{
   char emptyStr = '\0';
   char *str1 = (char *) s1;
   char *str2 = (char *) s2;

   if (str1 == NULL)
   {
      str1 = &emptyStr;
   }
   if (str2 == NULL)
   {
      str2 = &emptyStr;
   }

   return strcmp(str1, str2);
}

SINT32 utlStr_strcasecmp(const char *s1, const char *s2)
{
   char emptyStr = '\0';
   char *str1 = (char *) s1;
   char *str2 = (char *) s2;

   if (str1 == NULL)
   {
      str1 = &emptyStr;
   }
   if (str2 == NULL)
   {
      str2 = &emptyStr;
   }

   return strcasecmp(str1, str2);
}

SINT32 utlStr_strncmp(const char *s1, const char *s2, SINT32 n)
{
   char emptyStr = '\0';
   char *str1 = (char *) s1;
   char *str2 = (char *) s2;

   if (str1 == NULL)
   {
      str1 = &emptyStr;
   }
   if (str2 == NULL)
   {
      str2 = &emptyStr;
   }

   return strncmp(str1, str2, n);
}

SINT32 utlStr_strncasecmp(const char *s1, const char *s2, SINT32 n) 
{
   char emptyStr = '\0';
   char *str1 = (char *) s1;
   char *str2 = (char *) s2;

   if (str1 == NULL)
   {
      str1 = &emptyStr;
   }
   if (str2 == NULL)
   {
      str2 = &emptyStr;
   }

   return strncasecmp(str1, str2, n);
}

char *utlStr_strstr(const char *s1, const char *s2) 
{
   char emptyStr = '\0';
   char *str1 = (char *)s1;
   char *str2 = (char *)s2;

   if (str1 == NULL)
   {
      str1 = &emptyStr;
   }
   if (str2 == NULL)
   {
      str2 = &emptyStr;
   }

   return strstr(str1, str2);
}

char *utlStr_strncpy(char *dest, const char *src, SINT32 dlen)
{

   if((src == NULL) || (dest == NULL))
   {
      utlLog_error("null pointer reference src =%u ,dest =%u", src, dest);
   }	

   if( strlen(src)+1 > dlen )
   {
      utlLog_notice("truncating:src string length > dest buffer");
      strncpy(dest,src,dlen-1);
      dest[dlen-1] ='\0';
   }
   else
   {
      strcpy(dest,src);
   }
   return dest;
}

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

char *utlStr_strcat(char *dest, const char *src)
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

   return strcat(str1, str2);      
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

char *utlStr_getBaseName(char *path)
{
    char *ptr = NULL;
    if((ptr = strchr(path,'/')) != NULL)
        return utlStr_getBaseName(ptr+1);
    else
        return path;
}
