#include <assert.h>
#include <stdio.h>
#include <string.h>
#include "../platform_api.h"
#include "../request.h"
#include "../response.h"
#include "../dto/user.h"
#include "../storage/user.h"
#include "auth.h"

void route_auth
(struct platform_api *api, struct request *req, struct response *res)
{
        assert(api);
        assert(req);
        assert(res);

        struct user **users = NULL;
        size_t user_count = 0;

        user_count = 1;
        users = api->malloc(sizeof(*users) * user_count);

        for (size_t i = 0; i < user_count; i++) {
                users[i] = api->malloc(sizeof(*users[i]));
        }

        storage_user_list(api, users, user_count);

        memset(res->body, 0, sizeof(res->body));
        snprintf(
                res->body,
                sizeof(res->body),
                "{ \"%s\": \"%s\" }", "name",
                users[0]->name
        );

        for (size_t i = 0; i < user_count; i++) {
                api->free(users[i]);
        }
        api->free(users);
}
