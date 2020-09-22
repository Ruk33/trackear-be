#ifndef ROUTER_H
#define ROUTER_H

#include "request.h"
#include "response.h"

void router_handle_request
(struct request *req, struct response *res);

#endif
