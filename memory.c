#include <assert.h>
#include <stdlib.h>
#include "memory.h"

void *memory_alloc
(size_t how_much)
{
        assert(how_much > 0);

        void *memory = NULL;

        memory = calloc(1, how_much);

        if (!memory) {
                exit(EXIT_FAILURE);
        }

        return memory;
}

void memory_free
(void *memory)
{
        assert(memory);
        free(memory);
}
