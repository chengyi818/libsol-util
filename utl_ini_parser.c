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

#include <ctype.h>
#include "utl_ini_parser.h"
#include "utl_memory.h"
#include "utl_strconv.h"
#include "utl_logging.h"

static inline UBOOL8 utl_ini_check(UtlIniValue *pair)
{
    return((pair->group != NULL) && (pair->key != NULL) && (pair->value != NULL));
}

static void utl_ini_clean_key_value(UtlIniValue *pair)
{
    if (pair->key) 
        UTLMEM_FREE_BUF_AND_NULL_PTR(pair->key);
    if (pair->value) 
        UTLMEM_FREE_BUF_AND_NULL_PTR(pair->value);
}

static void utl_ini_clean_group(UtlIniValue *pair)
{
    if (pair->group) 
        UTLMEM_FREE_BUF_AND_NULL_PTR(pair->group);
}

static void utl_ini_cleanup(UtlIniValue *pair)
{
    if (pair->group) 
        UTLMEM_FREE_BUF_AND_NULL_PTR(pair->group);
    if (pair->key) 
        UTLMEM_FREE_BUF_AND_NULL_PTR(pair->key);
    if (pair->value) 
        UTLMEM_FREE_BUF_AND_NULL_PTR(pair->value);
}

UBOOL8 utl_ini_parser(char* buffer, char comment_char, char delim_char, UtlIniValueHandler func)
{
    char* p = buffer;
    char* group_start = NULL;
    char* key_start   = NULL;
    char* value_start = NULL;
    UtlIniValue pair = {NULL, NULL, NULL};

    enum _State
    {
        STAT_NONE = 0,
        STAT_GROUP,
        STAT_KEY,
        STAT_VALUE,
        STAT_COMMENT
    }state = STAT_NONE;

    for(p = buffer; *p != '\0'; p++)
    {
        switch(state)
        {
            case STAT_NONE:
                {
                    if(*p == '[')
                    {
                        state = STAT_GROUP;
                        group_start = p + 1;
                    }
                    else if(*p == comment_char)
                    {
                        state = STAT_COMMENT;
                    }
                    else if(!isspace(*p))
                    {
                        state = STAT_KEY;
                        key_start = p;
                    }
                    break;
                }
            case STAT_GROUP:
                {
                    if(*p == ']')
                    {
                        *p = '\0';
                        state = STAT_NONE;
                        utlStr_strTrim(group_start);
                        utl_ini_clean_group(&pair);
                        pair.group = utlMem_strdup(group_start);
                        utlLog_debug("[%s]", group_start);
                    }
                    break;
                }
            case STAT_COMMENT:
                {
                    if(*p == '\n')
                    {
                        state = STAT_NONE;
                        break;
                    }
                    break;
                }
            case STAT_KEY:
                {
                    if(*p == delim_char || (delim_char == ' ' && *p == '\t'))
                    {
                        *p = '\0';
                        state = STAT_VALUE;
                        value_start = p + 1;
                    }
                    break;
                }
            case STAT_VALUE:
                {
                    if(*p == '\n' || *p == '\r')
                    {
                        *p = '\0';
                        state = STAT_NONE;
                        utlStr_strTrim(key_start);
                        utlStr_strTrim(value_start);
                        pair.key = utlMem_strdup(key_start);
                        pair.value = utlMem_strdup(value_start);
                        utlLog_debug("%s%c%s", key_start, delim_char, value_start);
                        if (utl_ini_check(&pair)) 
                        {
                            if (func(&pair)) 
                                utl_ini_clean_key_value(&pair);
                            else
                                goto error;
                        }
                        else
                            goto error;
                    }
                    break;
                }
            default:break;
        }
    }

    if(state == STAT_VALUE)
    {
        utlStr_strTrim(key_start);
        utlStr_strTrim(value_start);
        pair.key = utlMem_strdup(key_start);
        pair.value = utlMem_strdup(value_start);
        utlLog_debug("%s%c%s", key_start, delim_char, value_start);
        if (utl_ini_check(&pair)) 
        {
            if (func(&pair)) 
                utl_ini_clean_key_value(&pair);
            else
                goto error;
        }
        else
            goto error;
    }

    utl_ini_cleanup(&pair);
    return TRUE;

error:
    utlLog_error("ini config file parse error!");
    utl_ini_cleanup(&pair);
    return FALSE;
}
