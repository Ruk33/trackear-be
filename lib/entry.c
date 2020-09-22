#include <assert.h>
#include <stdlib.h>
#include <string.h>
#include "request_parser.h"
#include "router.h"
#include "response_packet.h"
#include "entry.h"

void entry_handle_request
(
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

        memset(response, 0, response_size);
        request_parser_parse(&req, raw_request, raw_request_size);
        router_handle_request(&req, &res);
        response_packet(response, response_size, &res);
}
