#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "utl_logging.h"
#include "utl_memory.h"

void utl_logging_test(void)
{
    utlLog_init();

    /* test loglevel */
    utlLog_error("debug level = %d",(int)utlLog_getLevel());
    utlLog_error("log error test!");
    utlLog_notice("log notice test!");
    utlLog_debug("log debug test!");

    utlLog_setLevel(LOG_LEVEL_NOTICE);
    utlLog_error("debug level = %d",(int)utlLog_getLevel());
    utlLog_error("log error test!");
    utlLog_notice("log notice test!");
    utlLog_debug("log debug test!");

    utlLog_setLevel(LOG_LEVEL_DEBUG);
    utlLog_error("debug level = %d",(int)utlLog_getLevel());
    utlLog_error("log error test!");
    utlLog_notice("log notice test!");
    utlLog_debug("log debug test!");

    utlLog_error("********************************\n");

    /* test head mask */
    utlLog_error("head mask = %d", utlLog_getHeaderMask());
    utlLog_error("log head mask test!");

    utlLog_setHeaderMask(0x0001);
    utlLog_error("head mask = %d", utlLog_getHeaderMask());
    utlLog_error("log head mask test!");

    utlLog_setHeaderMask(0x0002);
    utlLog_error("head mask = %d", utlLog_getHeaderMask());
    utlLog_error("log head mask test!");

    utlLog_setHeaderMask(0x0004);
    utlLog_error("head mask = %d", utlLog_getHeaderMask());
    utlLog_error("log head mask test!");

    utlLog_setHeaderMask(0x0008);
    utlLog_error("head mask = %d", utlLog_getHeaderMask());
    utlLog_error("log head mask test!");

    utlLog_setHeaderMask(0x0003);
    utlLog_error("head mask = %d", utlLog_getHeaderMask());
    utlLog_error("log head mask test!");

    utlLog_setHeaderMask(0x0007);
    utlLog_error("head mask = %d", utlLog_getHeaderMask());
    utlLog_error("log head mask test!");

    utlLog_setHeaderMask(0x000f);
    utlLog_error("head mask = %d", utlLog_getHeaderMask());
    utlLog_error("log head mask test!");

    utlLog_error("********************************\n");

    /* log destination test */
    utlLog_error("log destination = %d", utlLog_getDestination());

    utlLog_setDestination(4);

    utlLog_error("log destination = %d", utlLog_getDestination());

    utlLog_setLogFile("/home/hyman/work/process/libutil/test/test.log");

    utlLog_error("log file = %s", utlLog_getLogFile());

    utlLog_cleanup();
}

void utl_memory_test(void)
{
    char *ptr1 = NULL;
    char *ptr2 = NULL;
    char *ptr3 = NULL;
    char *ptr4 = NULL;
    char *str  = "I'm sphantix, who are you?";

    utlLog_init();
    utlLog_setLevel(LOG_LEVEL_DEBUG);

    ptr1 = utlMem_alloc(256,ALLOC_ZEROIZE);
    strcpy(ptr1, "hello, world!");
    utlMem_dumpTraceAll();
    utlLog_debug("ptr1 = %s",ptr1);

    ptr2 = utlMem_strdup("I love the world");
    utlMem_dumpTraceAll();
    utlLog_debug("ptr2 = %s",ptr2);

    UTLMEM_REPLACE_STRING(ptr3, "I'm the king of the world");
    utlMem_dumpTraceAll();
    utlLog_debug("ptr3 = %s",ptr3);

    REPLACE_STRING_IF_NOT_EQUAL(ptr4, str);
    utlMem_dumpTraceAll();
    utlLog_debug("ptr4 = %s",ptr4);

    utlMem_free(ptr1);
    UTLMEM_FREE_BUF_AND_NULL_PTR(ptr2);
    UTLMEM_FREE_BUF_AND_NULL_PTR(ptr3);
    UTLMEM_FREE_BUF_AND_NULL_PTR(ptr4);

    utlLog_cleanup();
    return; 
}

int main(int argc, const char *argv[])
{
    utl_logging_test();
    utl_memory_test();
    return 0;
}
