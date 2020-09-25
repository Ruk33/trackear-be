#ifndef ROUTE_AUTH_H
#define ROUTE_AUTH_H

#include "../platform_api.h"
#include "../request.h"
#include "../response.h"

void route_auth
(struct platform_api *api, struct request *req, struct response *res);

#endif
