#ifndef LIB_H
#define LIB_H

#include <stdlib.h>

/**
 * Dynamically load the code from lib folder and handle the request
 * This allows to have changes in the code live without having to
 * stop the server
 */
void lib_handle_request
(
        unsigned char *raw_request,
        size_t raw_request_size,
        unsigned char *response,
        size_t response_size
);

#endif
