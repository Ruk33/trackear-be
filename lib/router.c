#include <assert.h>
#include <stdlib.h>
#include <string.h>
#include "platform_api.h"
#include "request.h"
#include "response.h"
#include "route/auth.h"
#include "router.h"

static int request_is_for_route
(struct request *req, char *verb, char *path)
{
        assert(req);
        assert(verb);
        assert(path);

        return (
                strcmp(req->type, verb) == 0 &&
                strcmp(req->path, path) == 0
        );
}

void router_handle_request
(struct platform_api *api, struct request *req, struct response *res)
{
        assert(req);
        assert(res);

        if (request_is_for_route(req, "GET", "/")) {
                return;
        }

        if (request_is_for_route(req, "GET", "/auth")) {
                route_auth(api, req, res);
                return;
        }
}
