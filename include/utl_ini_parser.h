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

#ifndef __UTL_INI_PARSER__
#define __UTL_INI_PARSER__

#include "utl.h"

typedef struct utl_ini_value
{
    char *group;
    char *key;
    char *value;
} UtlIniValue;

/** handler type definition
 */
typedef UBOOL8 (*UtlIniValueHandler)(UtlIniValue *);

UBOOL8 utl_ini_parser(char* buffer, char comment_char, char delim_char, UtlIniValueHandler func);
#endif /* __UTL_INI_PARSER__ */
