#ifndef LIB_H
#define LIB_H

#include <stdlib.h>

void lib_handle_request
(
        unsigned char *raw_request,
        size_t raw_request_size,
        unsigned char *response,
        size_t response_size
);

#endif
