#include <assert.h>
#include <stdlib.h>
#include <string.h>
#include "request_parser.h"
#include "router.h"
#include "response_packet.h"
#include "platform_api.h"
#include "entry.h"

void entry_handle_request
(
        platform_malloc_cb alloc_memory,
        platform_mfree_cb free_memory,
        platform_storage_query_cb storage_query,
        unsigned char *raw_request,
        size_t raw_request_size,
        unsigned char *response,
        size_t response_size
)
{
        assert(raw_request);
        assert(raw_request_size);
        assert(response);
        assert(response_size);

        struct request req;
        struct response res;
        struct platform_api api;

        api.malloc = alloc_memory;
        api.free = free_memory;
        api.storage_query = storage_query;

        memset(response, 0, response_size);
        request_parser_parse(&req, raw_request, raw_request_size);
        router_handle_request(&api, &req, &res);
        response_packet(response, response_size, &res);
}
