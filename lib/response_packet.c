#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "response.h"
#include "response_packet.h"

static void write_buffer
(unsigned char *dest, size_t max, char *content)
{
        assert(dest);
        assert(content);

        size_t dest_length = 0;
        size_t content_length = 0;
        size_t safe_length = 0;

        dest_length = strlen((const char *) dest);
        content_length = strlen((const char *) content);
        safe_length = dest_length + content_length > max ? max : content_length;

        memcpy(dest + dest_length, content, safe_length);
        dest[max] = 0;
}

void response_packet
(unsigned char *dest, size_t dest_size, struct response *r)
{
        assert(dest);
        assert(dest_size);
        assert(r);

        char status_code[8];
        char content_length[32];

        memset(dest, 0, dest_size);
        memset(status_code, 0, sizeof(status_code));
        memset(content_length, 0, sizeof(content_length));

        write_buffer(dest, dest_size, "HTTP/1.1");
        snprintf(status_code, sizeof(status_code), " %d ", r->status);
        write_buffer(dest, dest_size, status_code);
        write_buffer(dest, dest_size, r->status_message);
        write_buffer(dest, dest_size, "\n");
        // write_buffer(dest, dest_size, "Date: Sat, 09 Oct 2010 14:28:02 GMT\n");
        // write_buffer(dest, dest_size, "Last-Modified: Tue, 01 Dec 2009 20:18:22 GMT\n");
        // write_buffer(dest, dest_size, "ETag: \"51142bc1-7449-479b075b2891b\"\n");
        write_buffer(dest, dest_size, "Accept-Ranges: bytes\n");
        write_buffer(dest, dest_size, "Content-Length: ");
        snprintf(content_length, sizeof(content_length), "%ld\n", strlen(r->body));
        write_buffer(dest, dest_size, content_length);
        write_buffer(dest, dest_size, "Content-Type: text/json\n");
        write_buffer(dest, dest_size, "\n");
        write_buffer(dest, dest_size, r->body);
}
