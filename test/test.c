#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "utl_logging.h"

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

int main(int argc, const char *argv[])
{
    utl_logging_test();
    return 0;
}
