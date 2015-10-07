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

#include <string.h>
#include "utl_list.h"
#include "utl_memory.h"
#include "bget.h"

extern int backtrace(void **buffer, int size);


/** Macro to round up to nearest 4 byte length */
#define ROUNDUP4(s)  (((s) + 3) & 0xfffffffc)


/** Macro to calculate how much we need to allocate for a given user size request.
 *
 * We need the header even when not doing MEM_DEBUG to keep
 * track of the size and allocFlags that was passed in during cmsMem_alloc.
 * This info is needed during cmsMem_realloc.
 */
#ifdef UTL_MEM_DEBUG
#define REAL_ALLOC_SIZE(s) (UTL_MEM_HEADER_LENGTH + ROUNDUP4(s) + UTL_MEM_FOOTER_LENGTH)
#else
#define REAL_ALLOC_SIZE(s) (UTL_MEM_HEADER_LENGTH + (s))
#endif

static UtlMemStats mStats;

#ifdef UTL_MEM_LEAK_TRACING

#define NUM_STACK_ENTRIES   15

typedef struct alloc_record {
   DlistNode dlist;
   unsigned char *bufAddr;
   UINT32 userSize;
   UBOOL8 isClone;
   UBOOL8 dumpThisClone;
   UINT32 seq;
   void *stackAddr[NUM_STACK_ENTRIES];
} AllocRecord;

static UINT32 allocSeq=0;
DLIST_HEAD(glbAllocRec);

static void initAllocSeq(void)
{
   UtlTimestamp tms;

   if (allocSeq > 0)
   {
      return;
   }

   utlTm_get(&tms);

   srand(tms.nsec);
   allocSeq = rand() << 16;
   utlLog_debug("allocSeq=%lu\n", allocSeq);

   return;
}

static void garbageCollectAllocRec(void);
#endif /* UTL_MEM_LEAK_TRACING */

