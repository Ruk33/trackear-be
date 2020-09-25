#include <assert.h>
#include <stdlib.h>
#include <string.h>
#include "../platform_api.h"
#include "../../data_structure/row.h"
#include "../dto/user.h"
#include "user.h"

void storage_user_list
(struct platform_api *api, struct user *users[], size_t user_size)
{
        assert(api);
        assert(users);
        assert(user_size);

        char query[] = "SELECT name FROM users LIMIT 1";
        struct row **results = NULL;

        results = api->malloc(sizeof(*results) * user_size);

        for (size_t i = 0; i < user_size; i++) {
                results[i] = api->malloc(sizeof(*results[i]));
        }

        api->storage_query(query, results, user_size);

        memset(users[0]->name, 0, sizeof(users[0]->name));
        strncat(users[0]->name, results[0]->columns[0].value, sizeof(users[0]->name));

        for (size_t i = 0; i < user_size; i++) {
                api->free(results[i]);
        }
        api->free(results);
}
