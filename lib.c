#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <dlfcn.h>
#include "data_structure/row.h"
#include "memory.h"
#include "storage.h"
#include "lib.h"

#define LIB_PATH "./lib/libtrackear.so"

#define DLEXPR_OR_ERR(expr)                             \
        do {                                            \
                if (!(expr)) {                          \
                        printf("%s\n", dlerror());      \
                }                                       \
        } while (0);

typedef void* (* malloc_cb)
(size_t how_much_memory);

typedef void (* free_cb)
(void *memory);

typedef void (* storage_query_cb)
(char *query, struct row **results, size_t result_size);

typedef void (*handle_request_cb)
(
        malloc_cb m,
        free_cb f,
        storage_query_cb s,
        unsigned char *raw_request,
        size_t raw_request_size,
        unsigned char *response,
        size_t response_size
);

static time_t lib_loaded_version = 0;
static void *lib = NULL;
static handle_request_cb handle_request = NULL;

static time_t lib_last_time_modified
(void)
{
        struct stat file_stat;
        int err = stat(LIB_PATH, &file_stat);

        if (err != 0) {
                printf("Error while checking if lib changed.\n");
                return 0;
        }

        return file_stat.st_mtime;
}

static void load_lib_if_required
(void)
{
        time_t llm = 0;
        int did_not_changed = 0;

        llm = lib_last_time_modified();
        did_not_changed = llm <= lib_loaded_version;

        if (did_not_changed) {
                return;
        }

        if (lib) {
                dlclose(lib);
        }

        printf("Change detected in lib, loading latest version...\n");

        DLEXPR_OR_ERR(lib = dlopen(LIB_PATH, RTLD_LAZY));
        handle_request = NULL;

        if (!lib) {
                printf("Dynamic library could not be loaded.\n");
                return;
        }

        lib_loaded_version = llm;
        DLEXPR_OR_ERR(handle_request = dlsym(lib, "entry_handle_request"));
}

void lib_handle_request
(
        unsigned char *raw_request,
        size_t raw_request_size,
        unsigned char *response,
        size_t response_size
)
{
        assert(raw_request);
        assert(raw_request_size);
        assert(response);
        assert(response_size);

        load_lib_if_required();

        if (!handle_request) {
                return;
        }

        handle_request(
                &memory_alloc,
                &memory_free,
                &storage_query,
                raw_request,
                raw_request_size,
                response,
                response_size
        );
}
