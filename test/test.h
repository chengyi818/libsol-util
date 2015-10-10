#ifndef __TEST_H__
#define __TEST_H__

#include "utl.h"
#include "utl_ini_parser.h"

typedef UBOOL8 (*INI_SET_FUNC)(const char *name, const char *value);

typedef struct IniNodeDesc {
    char         *tagName;
    INI_SET_FUNC setIniFunc;
    struct IniNodeDesc *leafNode;
} IniNodeDesc;

#endif /* __TEST_H__ */
