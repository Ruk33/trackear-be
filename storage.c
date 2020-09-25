#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "storage.h"

void storage_query
(char *query, struct row **results, size_t result_size)
{
        assert(query);
        assert(results);
        assert(result_size > 0);

        printf("Query: %s\n", query);

        memset(results[0]->columns[0].key, 0, sizeof(results[0]->columns[0].key));
        memset(results[0]->columns[0].value, 0, sizeof(results[0]->columns[0].value));

        strncat(results[0]->columns[0].key, "name", sizeof(results[0]->columns[0].key));
        strncat(results[0]->columns[0].value, "Foo", sizeof(results[0]->columns[0].value));
}
