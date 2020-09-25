#ifndef ENTRY_H
#define ENTRY_H

#include <stdlib.h>
#include "platform_api.h"

void entry_handle_request
(
        platform_malloc_cb alloc_memory,
        platform_mfree_cb free_memory,
        platform_storage_query_cb query_storage,
        unsigned char *raw_request,
        size_t raw_request_size,
        unsigned char *response,
        size_t response_size
);

#endif
