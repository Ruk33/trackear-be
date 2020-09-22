#ifndef ENTRY_H
#define ENTRY_H

#include <stdlib.h>

void entry_handle_request
(
        unsigned char *raw_request,
        size_t raw_request_size,
        unsigned char *response,
        size_t response_size
);

#endif
