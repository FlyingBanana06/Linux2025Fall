#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define PORT 8080

int main() {
    int sockfd;
    struct sockaddr_in serv_addr;
    char buffer[1024];

    /* Create a TCP socket */
    sockfd = socket(AF_INET, SOCK_STREAM, 0);

    /* Configure server address (IPv4, localhost, specified port) */
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(PORT);
    inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr);

    /* Delay the client execution to avoid race condition */
    usleep(100000);

    /* Connect to the server */
    connect(sockfd, (struct sockaddr*)&serv_addr, sizeof(serv_addr));

    /* Read commands from standard input line by line */
    while (fgets(buffer, sizeof(buffer), stdin)) {

        /* Send one line of input to the server */
        write(sockfd, buffer, strlen(buffer));

        /* If the command is "kill", do not expect a response */
        if (strstr(buffer, "kill") != NULL)
            break;

        /* Clear buffer before receiving data */
        memset(buffer, 0, sizeof(buffer));

        /* Receive response from the server */
        read(sockfd, buffer, sizeof(buffer) - 1);

        /* Print server response to standard output */
        printf("%s", buffer);
    }
    
    /* Print final newline to match ans format */
    printf("\n");

    /* Close the socket and release resources */
    close(sockfd);
    return 0;
}

