#ifndef MEMORY_H
#define MEMORY_H

#include <stdlib.h>

void *memory_alloc
(size_t how_much);

void memory_free
(void *memory);

#endif
