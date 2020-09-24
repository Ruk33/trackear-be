#ifndef REQUEST_PARSER_H
#define REQUEST_PARSER_H

#include <stdlib.h>
#include "request.h"

/**
 * Parse a connection request and store it in dest
 */
void request_parser_parse
(struct request *dest, unsigned char *raw_request, size_t request_size);

#endif
