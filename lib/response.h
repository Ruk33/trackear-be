#ifndef RESPONSE_H
#define RESPONSE_H

#include <stdlib.h>
#include "static_config.h"
#include "header.h"

struct response {
        unsigned short status;
        char status_message[MAX_RESPONSE_STATUS_MESSAGE_SIZE];
        struct header headers[MAX_RESPONSE_HEADERS];
        char body[MAX_RESPONSE_BODY_SIZE];
};

#endif
