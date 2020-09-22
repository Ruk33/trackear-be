#ifndef REQUEST_H
#define REQUEST_H

#include <stdlib.h>
#include "static_config.h"
#include "header.h"

struct request {
        char type[MAX_REQUEST_TYPE_SIZE];
        char path[MAX_REQUEST_PATH_SIZE];
        struct header headers[MAX_REQUEST_HEADERS];
};

#endif
