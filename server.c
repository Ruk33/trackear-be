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
#include "conn.h"
#include "server.h"

#define SOCKET_EXPR_OR_DIE(expr)                                \
        do {                                                    \
                if ((expr) == -1) {                             \
                        printf(                                 \
                                "%s:%d - Socket error: %d\n",   \
                                __FILE__,                       \
                                __LINE__,                       \
                                errno                           \
                        );                                      \
                        exit(EXIT_FAILURE);                     \
                }                                               \
        } while (0);

static void server_accept_connections
(int server)
{
        assert(server);

        int client_socket = 0;
        struct sockaddr_in client_addr;
        socklen_t client_addr_size = 0;

        client_addr_size = (socklen_t) sizeof(client_socket);

        client_socket = accept(
                server,
                (struct sockaddr *) &client_addr,
                &client_addr_size
        );

        if (client_socket == -1) {
                printf("Error while trying to accept new connection.\n");
                printf("Error: %d\n", errno);
                return;
        }

        conn_handle_in_new_thread(client_socket);
}

void server_start
(unsigned short port, size_t max_conn)
{
        assert(port > 0);
        assert(max_conn > 0);

        int server = 0;
        struct sockaddr_in addr;

        addr.sin_family = AF_INET;
        addr.sin_addr.s_addr = INADDR_ANY;
        addr.sin_port = htons(port);

        SOCKET_EXPR_OR_DIE(server = socket(AF_INET, SOCK_STREAM, 0));
        SOCKET_EXPR_OR_DIE(bind(server, (struct sockaddr *) &addr, sizeof(addr)));
        SOCKET_EXPR_OR_DIE(listen(server, max_conn));

        printf("Starting to accept connections on port %d\n", port);
        while (1) server_accept_connections(server);
}
