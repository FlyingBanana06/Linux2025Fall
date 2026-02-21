#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define PORT 8080

int main() {
    int server_fd, client_fd;
    struct sockaddr_in addr;
    socklen_t addrlen = sizeof(addr);
    char buffer[1024];

    /* Create a TCP socket */
    server_fd = socket(AF_INET, SOCK_STREAM, 0);

    /* Configure server address */
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = INADDR_ANY;
    addr.sin_port = htons(PORT);

    /* Bind socket to the given port */
    bind(server_fd, (struct sockaddr*)&addr, sizeof(addr));

    /* Listen for incoming connections */
    listen(server_fd, 1);

    /* Accept a client connection */
    client_fd = accept(server_fd, (struct sockaddr*)&addr, &addrlen);

    /* Process client commands until "kill" is received */
    while (1) {
        memset(buffer, 0, sizeof(buffer));

        /* Read data sent from client */
        int n = read(client_fd, buffer, sizeof(buffer) - 1);
        if (n <= 0) break;

        int a, b;
        char cmd[32];

        /* Check for kill command */
        if (sscanf(buffer, "%s", cmd) == 1 && strcmp(cmd, "kill") == 0) {
            break;
        }

        /* add / mul (no line number) */
        if (sscanf(buffer, "%s %d %d", cmd, &a, &b) == 3) {
            if (strcmp(cmd, "add") == 0) {
                sprintf(buffer, "%d\n", a + b);
            } else if (strcmp(cmd, "mul") == 0) {
                sprintf(buffer, "%d\n", a * b);
            } else {
                sprintf(buffer, "Hello\n");
            }
        }
        /* abs (no line number) */
        else if (sscanf(buffer, "%s %d", cmd, &a) == 2) {
            if (strcmp(cmd, "abs") == 0) {
                if (a < 0) a = -a;
                sprintf(buffer, "%d\n", a);
            } else {
                sprintf(buffer, "Hello\n");
            }
        }
        /* unsupported */
        else {
            sprintf(buffer, "Hello\n");
        }

        /* Send result back to client */
        write(client_fd, buffer, strlen(buffer));
    }

    /* Close sockets */
    close(client_fd);
    close(server_fd);
    return 0;
}

