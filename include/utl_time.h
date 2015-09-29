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

#ifndef __UTL_TIME_H__
#define __UTL_TIME_H__

#include "utl.h"

#define NSECS_IN_SEC        1000000000
#define NSECS_IN_MSEC       1000000
#define NSECS_IN_USEC       1000
#define USECS_IN_SEC        1000000
#define USECS_IN_MSEC       1000
#define MSECS_IN_SEC        1000
#define SECS_IN_MINUTE      60
#define SECS_IN_HOUR        (SECS_IN_MINUTE * 60)
#define SECS_IN_DAY         (SECS_IN_HOUR * 24)

#define UNKNOWN_DATETIME_STRING "0001-01-01T00:00:00Z"


/** OS independent timestamp structure.
 */
typedef struct
{
   UINT32 sec;   /**< Number of seconds since some arbitrary point. */
   UINT32 nsec;  /**< Number of nanoseconds since some arbitrary point. */
} UtlTimestamp;

void utlTm_get(UtlTimestamp *tms);

#endif /* __UTL_TIME_H__ */
