#include <stdlib.h>
#include "server.h"

int main
(int argc, char **argv)
{
        unsigned short port = 0;
        size_t max_connections = 0;

        // We may want to get this from argv
        port = 8080;
        max_connections = 10;

        server_start(port, max_connections);

        return EXIT_SUCCESS;
}
