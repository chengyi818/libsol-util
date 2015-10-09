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

#ifndef __UTL_TIMER_H__
#define __UTL_TIMER_H__

#include "utl.h"

/** Event handler type definition
 */
typedef void (*UtlEventHandler)(void*);


/** Max length (including NULL character) of an event timer name.
 *
 * When an event timer is created, the caller can give it a name
 * to help with debugging and lookup.  Name is optional.
 */
#define UTL_EVENT_TIMER_NAME_LENGTH  32

#endif /* __UTL_TIMER_H__ */
