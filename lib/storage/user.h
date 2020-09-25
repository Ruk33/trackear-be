#ifndef STORAGE_USER_H
#define STORAGE_USER_H

#include <stdlib.h>
#include "../../data_structure/row.h"
#include "../dto/user.h"

typedef void (*storage_query_cb)
(char *query, struct row **results, size_t result_size);

void storage_user_list
(struct platform_api *api, struct user **users, size_t users_size);

#endif
