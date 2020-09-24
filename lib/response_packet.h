#ifndef RESPONSE_PACKET_H
#define RESPONSE_PACKET_H

#include <stdlib.h>
#include "response.h"

/**
 * Store a sendable HTTP packet from response and store it in dest
 */
void response_packet
(unsigned char *dest, size_t dest_size, struct response *r);

#endif
