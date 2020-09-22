#include <assert.h>
#include <stdlib.h>
#include <string.h>
#include "header.h"
#include "static_config.h"
#include "request_parser.h"

static int request_is_get
(unsigned char *raw_request, size_t request_size)
{
        assert(raw_request);

        char get[] = "GET";

        if (request_size < sizeof(get)) {
                return 0;
        }

        return memcmp(get, raw_request, strlen(get)) == 0;
}

static int request_is_post
(unsigned char *raw_request, size_t request_size)
{
        assert(raw_request);

        char post[] = "POST";

        if (request_size < sizeof(post)) {
                return 0;
        }

        return memcmp(post, raw_request, strlen(post)) == 0;
}

static void request_parse_type
(struct request *dest, unsigned char *raw_request, size_t request_size)
{
        assert(dest);
        assert(raw_request);
        assert(request_size);

        char get[] = "GET";
        char post[] = "POST";

        int is_get = 0;
        int is_post = 0;

        is_get = request_is_get(raw_request, request_size);
        is_post = request_is_post(raw_request, request_size);

        memset(dest->type, 0, sizeof(dest->type));

        assert(sizeof(dest->type) > sizeof(get));
        assert(sizeof(dest->type) > sizeof(post));

        if (is_get) {
                memcpy(dest->type, get, sizeof(get));
        }

        if (is_post) {
                memcpy(dest->type, post, sizeof(post));
        }
}

static unsigned char *request_find_char
(unsigned char *raw_request, char c)
{
        if (!raw_request) {
                return NULL;
        }

        while (*raw_request) {
                if (*raw_request == c) {
                        return raw_request;
                }
                raw_request++;
        }

        return NULL;
}

static void request_parse_path
(struct request *dest, unsigned char *raw_request, size_t request_size)
{
        assert(dest);
        assert(raw_request);
        assert(request_size);

        unsigned char *tmp = NULL;
        size_t type_length = 0;
        size_t path_length = 0;
        size_t max_length = 0;
        size_t safe_length = 0;

        type_length = strlen(dest->type);

        memset(dest->path, 0, sizeof(dest->path));

        if (type_length == 0) {
                return;
        }

        raw_request = raw_request + type_length + 1;
        tmp = request_find_char(raw_request, ' ');

        if (!tmp) {
                return;
        }

        path_length = tmp - raw_request;
        max_length = sizeof(dest->path);
        safe_length = max_length > path_length ? path_length : max_length;

        memcpy(dest->path, raw_request, safe_length);
        dest->path[max_length - 1] = 0;
}

static void request_reset_headers
(struct request *dest)
{
        assert(dest);

        for (int i = 0; i < MAX_REQUEST_HEADERS; i++) {
                memset(dest->headers[i].key, 0, sizeof(dest->headers[i].key));
                memset(dest->headers[i].value, 0, sizeof(dest->headers[i].value));
        }
}

static void request_parse_headers
(struct request *dest, unsigned char *raw_request, size_t request_size)
{
        assert(dest);
        assert(raw_request);
        assert(request_size);

        struct header *new_header = NULL;
        size_t headers_count = 0;
        unsigned char *tmp = NULL;
        size_t key_len = 0;
        size_t max_key_len = 0;
        size_t safe_key_len = 0;
        size_t value_len = 0;
        size_t max_value_len = 0;
        size_t safe_value_len = 0;

        raw_request = request_find_char(raw_request, '\n');

        request_reset_headers(dest);

        if (raw_request) {
                // Advance to the new line
                raw_request++;
        }

        while (raw_request && headers_count < MAX_REQUEST_HEADERS) {
                tmp = request_find_char(raw_request, ':');

                if (!tmp) {
                        return;
                }

                new_header = &dest->headers[headers_count];
                headers_count++;

                memset(new_header->key, 0, sizeof(new_header->key));
                memset(new_header->value, 0, sizeof(new_header->value));

                key_len = tmp - raw_request;
                max_key_len = sizeof(new_header->key);
                safe_key_len = max_key_len > key_len ? key_len : max_key_len;
                memcpy(new_header->key, raw_request, safe_key_len);
                new_header->key[max_key_len - 1] = 0;

                raw_request = request_find_char(tmp, ' ');

                if (!raw_request) {
                        return;
                }

                // Advance the space
                raw_request++;
                tmp = request_find_char(raw_request, '\n');

                if (!tmp) {
                        return;
                }

                value_len = tmp - raw_request - 1;
                max_value_len = sizeof(new_header->value);
                safe_value_len = max_value_len > value_len ? value_len : max_value_len;
                memcpy(new_header->value, raw_request, safe_value_len);
                new_header->value[max_value_len - 1] = 0;

                // Advance new line
                raw_request = tmp + 1;
        }
}

void request_parser_parse
(struct request *dest, unsigned char *raw_request, size_t request_size)
{
        assert(dest);
        assert(raw_request);
        assert(request_size);

        request_parse_type(dest, raw_request, request_size);
        request_parse_path(dest, raw_request, request_size);
        request_parse_headers(dest, raw_request, request_size);
}
