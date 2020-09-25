#ifndef PLATFORM_API_H
#define PLATFORM_API_H

#include <stdlib.h>
#include "../data_structure/row.h"

/**
 * Allocate memory. The memory is guaranteed to be allocated or
 * the program will exit
 */
typedef void* (* platform_malloc_cb)
(size_t how_much_memory);

/**
 * Free memory allocated with platform_malloc_cb
 */
typedef void (* platform_mfree_cb)
(void *memory);

/**
 * Query storage with query and store a maximum
 * of result_size in results
 */
typedef void (* platform_storage_query_cb)
(char *query, struct row *results[], size_t result_size);

struct platform_api {
        platform_malloc_cb malloc;
        platform_mfree_cb free;
        platform_storage_query_cb storage_query;
};

#endif
