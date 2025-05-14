#include <netinet/in.h>
#include <sys/socket.h>
#include <stdio.h>
#include <sys/types.h>
#include <netdb.h> // contains the addrinfo and all those structs
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>

int main(int argc, char** argv) {
    int status;
    struct addrinfo hints, *res;
    char ipstr[INET_ADDRSTRLEN];
    int yes;                                    // used to turn on a option

    memset(&hints, 0, sizeof(hints));
    hints.ai_family   = AF_INET;
    hints.ai_socktype = SOCK_STREAM;

    // create an address on the loopback at port 3003
    if ((status = getaddrinfo(NULL, "3003", &hints, &res)) != 0) {
        fprintf(stderr, "getaddrinfo error %s\n", gai_strerror(status));
        exit(1);
    }

    struct sockaddr_in *ipv4 = (struct sockaddr_in *)(res->ai_addr);
    void *addr = &(ipv4->sin_addr);
    inet_ntop(res->ai_family, addr, ipstr, sizeof ipstr);

    // Got the address, now need to call socket to setup a namespace
    int fd = socket(res->ai_family, res->ai_socktype, res->ai_protocol);
    // allows the address to be reused if it is not "actively" listening
    // also not necessary but a good practice if you want to quickly restart the server
    if(setsockopt(fd, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof yes) == -1) {
        perror("setsockopt");
        exit(1);
    }

    // bind to that socket (on that ip:port) - assign the resources.
    // NOTE: This is not necessary when writing client side
    if (bind(fd, res->ai_addr, res->ai_addrlen) == -1) {
        perror("bind");
        exit(1);
    }

    printf("END");

    freeaddrinfo(res);
return 0; }
