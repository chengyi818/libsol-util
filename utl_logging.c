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

#include <fcntl.h>      /* open */
#include "utl_logging.h"
#include "utl_prctl.h"

static UtlLogLevel                  logLevel;
static UtlLogDestination            logDestination;
static UINT32 logHeaderMask;

void utlLog_debug(UtlLogLevel level, const char *func, UINT32 lineNum, const char *pFmt, ... )
{
    va_list		ap;
    char buf[MAX_LOG_LINE_LENGTH] = {0};
    int len=0, maxLen;
    char *logLevelStr=NULL;
    int logTelnetFd = -1;

    maxLen = sizeof(buf);

    if (level <= logLevel)
    {
        va_start(ap, pFmt);

        if (logHeaderMask & UTLLOG_HDRMASK_APPNAME)
        {
            char processName[256] = {'\0'};
            utlPrctl_getProcessName(processName);
            if (utlStr_strlen(processName) != 0) 
                len = snprintf(buf, maxLen, "%s:", processName);
            else
                len = snprintf(buf, maxLen, "unkown:");
        }


        if ((logHeaderMask & UTLLOG_HDRMASK_LEVEL) && (len < maxLen))
        {
            /*
             * Only log the severity level when going to stderr
             * because syslog already logs the severity level for us.
             */
            if (logDestination == LOG_DEST_STDERR)
            {
                switch(level)
                {
                    case LOG_LEVEL_ERR:
                        logLevelStr = "error";
                        break;
                    case LOG_LEVEL_NOTICE:
                        logLevelStr = "notice";
                        break;
                    case LOG_LEVEL_DEBUG:
                        logLevelStr = "debug";
                        break;
                    default:
                        logLevelStr = "invalid";
                        break;
                }
                len += snprintf(&(buf[len]), maxLen - len, "%s:", logLevelStr);
            }
        }


        /*
         * Log timestamp for both stderr and syslog because syslog's
         * timestamp is when the syslogd gets the log, not when it was
         * generated.
         */
        if ((logHeaderMask & UTLLOG_HDRMASK_TIMESTAMP) && (len < maxLen))
        {
            UtlTimestamp ts;

            utlTm_get(&ts);
            len += snprintf(&(buf[len]), maxLen - len, "%u.%03u:",
                    ts.sec%1000, ts.nsec/NSECS_IN_MSEC);
        }


        if ((logHeaderMask & UTLLOG_HDRMASK_LOCATION) && (len < maxLen))
        {
            len += snprintf(&(buf[len]), maxLen - len, "%s:%u:", func, lineNum);
        }


        if (len < maxLen)
        {
            maxLen -= len;
            vsnprintf(&buf[len], maxLen, pFmt, ap);
        }

        if (logDestination == LOG_DEST_STDERR)
        {
            int logStdErrFd = -1;
            logStdErrFd = open("/dev/ttyS0", O_RDWR);
            if(logStdErrFd != -1)
            {
                write(logStdErrFd, buf, strlen(buf));
                write(logStdErrFd, "\n", strlen("\n"));
                close(logStdErrFd);
            }
        }
        else if (logDestination == LOG_DEST_TELNET )
        {
#ifdef DESKTOP_LINUX
            /* Fedora Desktop Linux */
            logTelnetFd = open("/dev/pts/1", O_RDWR);
#else
            /* CPE use ptyp0 as the first pesudo terminal */
            logTelnetFd = open("/dev/ttyp0", O_RDWR);
#endif
            if(logTelnetFd != -1)
            {
                write(logTelnetFd, buf, strlen(buf));
                write(logTelnetFd, "\n", strlen("\n"));
                close(logTelnetFd);
            }
        }
        else
        {
            oslLog_syslog(level, buf);
        }

        va_end(ap);
    }
}
