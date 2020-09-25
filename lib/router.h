#ifndef ROUTER_H
#define ROUTER_H

#include "platform_api.h"
#include "request.h"
#include "response.h"

/**
 * Handle request from connection and store it in res
 */
void router_handle_request
(struct platform_api *api, struct request *req, struct response *res);

#endif
