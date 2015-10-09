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
#include "utl_memory.h"
#include "utl_logging.h"
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

   if (func != NULL) 
   {
       rbtree_postorder_for_each_entry_safe(tmrEvent, next, tmr_tree, node)
       {
           if (tmrEvent->func == func && tmrEvent->ctxData == ctxData)
           {
               found = TRUE;
               break;
           }
       }
   }

   return found;
}

/** This macro will evaluate TRUE if a is earlier than b */
#define IS_EARLIER_THAN(a, b) (((a)->sec < (b)->sec) || \
                               (((a)->sec == (b)->sec) && ((a)->nsec < (b)->nsec)))

/**
 * Adds timer to rbtree.
 *
 * Adds the timer node to the rbtree, sorted by the
 * node's expires value.
 */
void utlTmr_add(void *handle, UtlTimerEvent *event)
{
    UtlTimerHandle *tmrHandle = (UtlTimerHandle *) handle;
    struct rb_node **p = &tmrHandle->root.rb_node;
    struct rb_node *parent = NULL;
    UtlTimerEvent *ptr;

    if(!RB_EMPTY_NODE(&event->node))
    {
        while (*p) {
            parent = *p;
            ptr = rb_entry(parent, UtlTimerEvent, node);
            if (IS_EARLIER_THAN(&(event->expireTms), &(ptr->expireTms)))
                p = &(*p)->rb_left;
            else
                p = &(*p)->rb_right;
        }
        rb_link_node(&event->node, parent, p);
        rb_insert_color(&event->node, &tmrHandle->root);
    }

    return;
}

/**
 * Removes a timer from the timerqueue.
 *
 * Removes the timer node from the timerqueue.
 */
void utlTmr_del(void *handle, UtlTimerEvent *event)
{
    UtlTimerHandle *tmrHandle = (UtlTimerHandle *) handle;
    struct rb_root *tmr_tree = &tmrHandle->root;

    rb_erase(&event->node, tmr_tree);
    RB_CLEAR_NODE(&event->node);
    UTLMEM_FREE_BUF_AND_NULL_PTR(event);

    return;
}

UtlTimerEvent *utlTmr_find(const void *handle, UtlEventHandler func, void *ctxData)
{
    const UtlTimerHandle *tmrHandle = (const UtlTimerHandle *) handle;
    const struct rb_root *tmr_tree = &tmrHandle->root;
    UtlTimerEvent *tmrEvent, *next;

    rbtree_postorder_for_each_entry_safe(tmrEvent, next, tmr_tree, node)
    {
        if (tmrEvent->func == func && tmrEvent->ctxData == ctxData)
            return tmrEvent;
    }
    
    return NULL;
}

UtlRet utlTmr_set(void *handle, UtlEventHandler func, void *ctxData, UINT32 ms, const char *name)
{
    UtlTimerHandle *tmrHandle = (UtlTimerHandle *) handle;
    UtlTimerEvent *newEvent;

    /*
     * First verify there is not a duplicate event.
     * (The original code first deleted any existing timer,
     * which is a "side-effect", bad style, but maybe tr69c requires
     * that functionality?)
     */
    if (utlTmr_isEventPresent(handle, func, ctxData))
    {
        utlLog_error("There is already an event func 0x%x ctxData 0x%x", func, ctxData);
        return UTLRET_INVALID_ARGUMENTS;
    }

    /* make sure name is not too long */
    if ((name != NULL) && (strlen(name) >= UTL_EVENT_TIMER_NAME_LENGTH))
    {
        utlLog_error("name of timer event is too long, max %d", UTL_EVENT_TIMER_NAME_LENGTH);
        return UTLRET_INVALID_ARGUMENTS;
    }

    /*
     * Allocate a structure for the timer event.
     */
    newEvent = utlMem_alloc(sizeof(UtlTimerEvent), ALLOC_ZEROIZE);
    if (newEvent == NULL)
    {
        utlLog_error("malloc of new timer event failed");
        return UTLRET_RESOURCE_EXCEEDED;
    }

    /* fill in fields of new event timer structure. */
    newEvent->func = func;
    newEvent->ctxData = ctxData;

    utlTm_get(&(newEvent->expireTms));
    utlTm_addMilliSeconds(&(newEvent->expireTms), ms);

    if (name != NULL)
    {
        sprintf(newEvent->name, "%s", name);
    }

    utlTmr_add(handle, newEvent);

    tmrHandle->numEvents++;

    utlLog_debug("added event %s, expires in %ums (at %u.%03u), func=0x%x data=%p count=%d",
            newEvent->name,
            ms,
            newEvent->expireTms.sec,
            newEvent->expireTms.nsec/NSECS_IN_MSEC,
            func,
            ctxData,
            tmrHandle->numEvents);

    return UTLRET_SUCCESS;
}

void utlTmr_cancel(void *handle, UtlEventHandler func, void *ctxData)
{
    UtlTimerHandle *tmrHandle = (UtlTimerHandle *) handle;
    UtlTimerEvent *tmrEvent;

    if (RB_EMPTY_ROOT(&tmrHandle->root))
    {
        utlLog_debug("no events to delete (func=0x%x data=%p)", func, ctxData);
        return;
    }

    if ((tmrEvent = utlTmr_find(handle, func, ctxData)) != NULL)
    {
        tmrHandle->numEvents--;
        utlLog_debug("canceled event %s, count=%d", tmrEvent->name, tmrHandle->numEvents);
        utlTmr_del(handle, tmrEvent);
    }
    else
    {
        utlLog_debug("could not find requested event to delete, func=0x%x data=%p count=%d", func, ctxData, tmrHandle->numEvents);
    }

    return;
}
