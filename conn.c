#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/ip.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <pthread.h>
#include "lib.h"
#include "conn.h"

#define MAX_REQUEST_SIZE 4096
#define MAX_RESPONSE_SIZE 4096

static void conn_close
(int conn_socket)
{
        assert(conn_socket);

        printf("Closing connection.\n");
        close(conn_socket);
        shutdown(conn_socket, SHUT_RDWR);
}

static void conn_request_handle
(int conn_socket, unsigned char *raw_request, size_t request_size)
{
        assert(conn_socket);
        assert(raw_request);

        unsigned char raw_response[MAX_RESPONSE_SIZE];
        int send_status = 0;

        if (request_size == 0) {
                return;
        }

        lib_handle_request(
                raw_request,
                request_size,
                raw_response,
                MAX_RESPONSE_SIZE
        );

        send_status = send(
                conn_socket,
                raw_response,
                strlen((const char *) raw_response),
                0
        );

        if (send_status == -1) {
                printf("Error while sending response to connection.\n");
                printf("Error: %d.\n", errno);
                return;
        }

        printf("Response sent.");
}

static void *conn_handle_requests
(void *conn_socket_p)
{
        assert(conn_socket_p);

        int conn_socket = 0;
        unsigned char buffer[MAX_REQUEST_SIZE];
        size_t request_size = 0;

        conn_socket = *((int *) conn_socket_p);

        memset(buffer, 0, MAX_REQUEST_SIZE);

        printf("Listening for request.\n");
        request_size = recv(conn_socket, buffer, MAX_REQUEST_SIZE, 0);

        if (request_size > MAX_REQUEST_SIZE) {
                printf("Request bigger than supported. Ignoring request.\n");
                printf("Requested = %ld.\n", request_size);
                printf("Maximum supported = %d.\n", MAX_REQUEST_SIZE);
        } else {
                conn_request_handle(conn_socket, buffer, request_size);
        }

        conn_close(conn_socket);

        free(conn_socket_p);

        return NULL;
}

void conn_handle_in_new_thread
(int conn_socket)
{
        assert(conn_socket);

        pthread_t thread = 0;
        int *conn_socket_p = NULL;

        conn_socket_p = calloc(1, sizeof(*conn_socket_p));
        *conn_socket_p = conn_socket;

        printf("New connection accepted.\n");
        pthread_create(&thread, NULL, &conn_handle_requests, conn_socket_p);
}
