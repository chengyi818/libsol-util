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

#include "utl_timer.h"
#include "utl_time.h"
#include "rbtree.h"

/** Internal event timer structure
 */
typedef struct utl_timer_event
{
    struct rb_node           node;      /**< node for rbtree. */
    UtlTimestamp             expireTms; /**< Timestamp (in the future) of when this timer event will expire. */
    UtlEventHandler          func;      /**< handler func to call when event expires. */
    void *                   ctxData;   /**< context data to pass to func */
    char name[UTL_EVENT_TIMER_NAME_LENGTH]; /**< name of this timer */
} UtlTimerEvent;

/** Internal timer handle. */
typedef struct
{
   struct rb_root  root;       /**< timer tree root node */
   UINT32          numEvents;  /**< Number of events in this handle. */
} UtlTimerHandle;


UtlRet utlTmr_init(void **tmrHandle)
{

   (*tmrHandle) = utlMem_alloc(sizeof(UtlTimerHandle), ALLOC_ZEROIZE);
   if ((*tmrHandle) == NULL)
   {
      utlLog_error("could not malloc mem for tmrHandle");
      return UTLRET_RESOURCE_EXCEEDED;
   }

   return UTLRET_SUCCESS;
}

UBOOL8 utlTmr_isEventPresent(const void *handle, UtlEventHandler func, void *ctxData)
{
   const UtlTimerHandle *tmrHandle = (const UtlTimerHandle *) handle;
   const struct rb_root *tmr_tree = &tmrHandle->root;
   UtlTimerEvent *tmrEvent, *next;
   UBOOL8 found = FALSE;

   rbtree_postorder_for_each_entry_safe(tmrEvent, next, tmr_tree, node)
   {
       if (tmrEvent->func == func && tmrEvent->ctxData == ctxData)
       {
           found = TRUE;
       }
   }

   return found;
}

/**
 * timerqueue_add - Adds timer to rbtree.
 *
 * Adds the timer node to the rbtree, sorted by the
 * node's expires value.
 */
bool utlTmr_add(void *handle, UtlTimerEvent *event)
{
    UtlTimerHandle *tmrHandle = (UtlTimerHandle *) handle;
    struct rb_node **p = &head->head.rb_node;
    struct rb_node *parent = NULL;
    struct timerqueue_node  *ptr;

    if(!RB_EMPTY_NODE(&node->node))
    {
        while (*p) {
            parent = *p;
            ptr = rb_entry(parent, struct timerqueue_node, node);
            if (node->expires.tv64 < ptr->expires.tv64)
                p = &(*p)->rb_left;
            else
                p = &(*p)->rb_right;
        }
        rb_link_node(&node->node, parent, p);
        rb_insert_color(&node->node, &head->head);

        if (!head->next || node->expires.tv64 < head->next->expires.tv64) {
            head->next = node;
            return true;
        }
    }
    return false;
}
