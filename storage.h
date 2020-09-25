#ifndef STORAGE_H
#define STORAGE_H

#include <stdlib.h>
#include "data_structure/row.h"

void storage_query
(char *query, struct row **results, size_t result_size);

#endif
