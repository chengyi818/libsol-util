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

#ifndef __UTL_MEMORY_H__
#define __UTL_MEMORY_H__

#include "utl.h"
#include "osl_memory.h"

/** zeroize the buffer before returning it to the caller. */
#define ALLOC_ZEROIZE          0x01

/** allocate memory in the shared memory region. */
#define ALLOC_SHARED_MEM       0x02

#ifdef __cplusplus
extern "C" {
#endif

/* Memory Statistics structure.
 */
typedef struct
{
   UINT32 shmAllocStart; /**< Start of shared memory alloc pool */
   UINT32 shmAllocEnd;   /**< End of shared memory alloc pool */
   UINT32 shmTotalBytes; /**< Total size of shm pool, in bytes */
   UINT32 shmBytesAllocd;/**< Number of bytes allocated/in-use from shm pool */
   UINT32 shmNumAllocs;  /**< Number of shared memory allocs */
   UINT32 shmNumFrees;   /**< Number of shared memory frees */
   UINT32 bytesAllocd;   /**< Number of private heap bytes alloc'ed */
   UINT32 numAllocs;     /**< Number of private heap allocs */
   UINT32 numFrees;      /**< Number of private heap frees */
} UtlMemStats;


#ifdef __cplusplus
} /* end of extern "C" */
#endif

/** How much debug information to put at the beginning of a malloc'd block,
 *  to keep track of original length and allocation flags (and also to
 *  detect buffer under-write).
 *
 * We allocate a header regardless of UTL_MEM_DEBUG.
 *
 * The memory code assumes this value is 12, so you'll need to modify
 * utl_memory.c if you change this constant.
 */
#define UTL_MEM_HEADER_LENGTH   12


/** How much debug information to put at the end of a malloc'd block,
 *  (to detect buffer over-write) used only if UTL_MEM_DEBUG is defined.
 *
 * The memory code assumes this value is 8, so you'll need to modify
 * utl_memory.c if you change this constant.
 */
#define UTL_MEM_FOOTER_LENGTH   8


/** Pattern put at the memory block footer (to detect buffer over-write).
 *
 * Used only if UTL_MEM_DEBUG is defined.
 * If allocation is not on 4 byte boundary, the bytes between the user
 * requested bytes and the 4 byte boundary are filled with the 
 * last byte of the UTL_MEM_FOOTER_PATTERN.
 */
#define UTL_MEM_FOOTER_PATTERN   0xfdfdfdfd


/** Pattern put in freshly allocated memory blocks, which do not have
 *  ALLOC_ZEROIZE flag set (to detect use before initialization.)
 *
 * Used only if UTL_MEM_DEBUG is defined.
 */
#define UTL_MEM_ALLOC_PATTERN    ((UINT8) 0x95)


/** Pattern put in freed memory blocks (to detect use after free.)
 *
 * Used only if UTL_MEM_DEBUG is defined.
 */
#define UTL_MEM_FREE_PATTERN     ((UINT8) 0x97)

#endif /* __UTL_MEMORY_H__ */
