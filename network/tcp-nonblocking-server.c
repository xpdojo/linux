/*
 * TCP non-blocking server
 *
 * This program listens for incoming connections and sends a "Hello, world!"
 * string to the client every time it receives data.
 *
 * gcc -o server.o tcp-nonblocking-server.c
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <fcntl.h> /* Added for the nonblocking socket */
#include <signal.h>
//#include <unistd.h> /* for sleep */

#define MYPORT 3456    /* the port users will be connecting to */
#define BACKLOG 10     /* how many pending connections queue will hold */

static volatile int keep_running = 1;

void sigint_handler(int signum) {
    keep_running = 0;
}

int main() {
    int sockfd, new_fd;             /* listen on sock_fd, new connection on new_fd */
    struct sockaddr_in my_addr;     /* my address information */
    struct sockaddr_in their_addr;  /* connector's address information */
    int sin_size;
    char string_read[255];
    int last_fd;    /* Thelast sockfd that is connected	*/

    /* Step 1: Create a socket and bind it to a port */
    if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
        perror("socket");
        exit(1);
    }

    last_fd = sockfd;

    my_addr.sin_family = AF_INET;         /* host byte order */
    my_addr.sin_port = htons(MYPORT);     /* short, network byte order */
    my_addr.sin_addr.s_addr = INADDR_ANY; /* auto-fill with my IP */
    bzero(&(my_addr.sin_zero), 8);        /* zero the rest of the struct */

    if (bind(sockfd, (struct sockaddr *) &my_addr, sizeof(struct sockaddr)) == -1) {
        perror("bind");
        exit(1);
    }

    /* Step 2: Listen for incoming connections */
    if (listen(sockfd, BACKLOG) == -1) {
        perror("listen");
        exit(1);
    }

    /* Step 3: Accept incoming connections and set them to non-blocking mode */
    if ((new_fd = accept(sockfd, (struct sockaddr *) &their_addr, &sin_size)) == -1) {
        perror("accept");
        exit(1);
    }
    fcntl(last_fd, F_SETFL, O_NONBLOCK); /* Change the socket into non-blocking state	*/
    fcntl(new_fd, F_SETFL, O_NONBLOCK); /* Change the socket into non-blocking state	*/

    signal(SIGINT, sigint_handler); /* register the SIGINT handler */

    const char *message = "Hello, world!\n";
    const size_t message_len = strlen(message);
    int i = 0;
    ssize_t n;
    while (keep_running) {
        /* Step 4: Receive data from the client */
        n = recv(new_fd, string_read, sizeof(string_read), 0);
        if (n < 1) {
            /* No data received */
            perror("recv - non blocking \n");
            printf("Round %d, and the data read size is: n=%zd \n", i, n);
        } else {
            /* Data received */
            string_read[n] = '\0';
            printf("The string is: %s \n", string_read);
            /* Step 5: Send data to the client */
            if (send(new_fd, message, message_len, 0) == -1) {
                perror("send");
            }
        }
        // sleep(1);
    }
}
