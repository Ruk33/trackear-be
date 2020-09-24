#ifndef ROUTER_H
#define ROUTER_H

#include "request.h"
#include "response.h"

/**
 * Handle request from connection and store it in res
 */
void router_handle_request
(struct request *req, struct response *res);

#endif
