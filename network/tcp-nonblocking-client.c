/*
 * TCP non-blocking client
 *
 * This program connects to a TCP server and sends a "Hello, world!" string
 * every second.
 *
 * gcc -o client.o tcp-nonblocking-client.c
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <netdb.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <unistd.h>
#include <signal.h>

#define PORT 3456 /* the port client will be connecting to */

static volatile int keep_running = 1;

void sigint_handler(int signum) {
    keep_running = 0;
}

int main(int argc, char *argv[]) {
    int sockfd;
    struct hostent *he;
    struct sockaddr_in their_addr; /* connector's address information */

    /* Step 1: Get the host information */
    if ((he = gethostbyname("127.0.0.1")) == NULL) {
        herror("gethostbyname");
        exit(1);
    }

    /* Step 2: Create a socket */
    if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
        perror("socket");
        exit(1);
    }

    /* Step 3: Connect to the server */
    their_addr.sin_family = AF_INET;   /* host byte order */
    their_addr.sin_port = htons(PORT); /* short, network byte order */
    their_addr.sin_addr = *((struct in_addr *) he->h_addr);
    bzero(&(their_addr.sin_zero), 8); /* zero the rest of the struct */

    if (connect(sockfd, (struct sockaddr *) &their_addr, sizeof(struct sockaddr)) == -1) {
        perror("connect");
        exit(1);
    }

    /* Step 4: Send data to the server */
    signal(SIGINT, sigint_handler); /* register the SIGINT handler */

    const char *message = "Hello, world!\n";
    const size_t message_len = strlen(message);
    while (keep_running) {
        if (send(sockfd, message, message_len, 0) == -1) {
            perror("send");
        }
        printf("In loop \n");
    }
    /* Step 5: Close the socket */
    close(sockfd);
    return 0;
}
