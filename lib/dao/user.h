#ifndef DAO_USER_H
#define DAO_USER_H

#include <stdlib.h>
#include "../../data_structure/row.h"
#include "../dto/user.h"

void dao_user_list
(struct platform_api *api, struct user **users, size_t users_size);

#endif
