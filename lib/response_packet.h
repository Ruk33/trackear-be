#ifndef RESPONSE_PACKET_H
#define RESPONSE_PACKET_H

#include <stdlib.h>
#include "response.h"

void response_packet
(unsigned char *dest, size_t dest_size, struct response *r);

#endif
