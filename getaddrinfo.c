#include <netinet/in.h>
#include <sys/socket.h>
#include <stdio.h>
#include <sys/types.h>
#include <netdb.h> // contains the addrinfo and all those structs
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>

int main(int argc, char** argv) {
    int status;                             // Status of the getaddrinfo

    struct addrinfo hints;                  // Contains the hints (configurations) to open the connection
    struct addrinfo *servinfo;              // the results pointer
    memset(&hints, 0, sizeof(hints));       // fills the memory at hints to zeros. Is this really necessary?

    // sets hints
    hints.ai_family   = AF_INET;             // IPV4
    hints.ai_socktype = SOCK_STREAM;         // TCP

    // Setting this to AI_PASSIVE is like telling it to "be a server", and listen on all interfaces
    // For IPv4 it will be 0.0.0.0
    // whereas disabling it will listen on the loopback address
    // The above statements are only true when the first argument into getaddrinfo is NULL.
    hints.ai_flags    = AI_PASSIVE;

    if ((status = getaddrinfo(NULL, "3490", &hints, &servinfo)) != 0) {
        fprintf(stderr, "getaddrinfo error %s\n", gai_strerror(status));
        exit(1);
    }


    // sockaddr* is returned, which is just raw bytes. Handling it directly would be tedius, but possible.
    // Instead, convert it to sockaddr_in* (for ipv4), or sockaddr_in6* (for ipv6) which make it more convenient to handle it
    // Casting is safe since they are using the exact same byte order under the hood.
    struct sockaddr_in* sin = (struct sockaddr_in*)(servinfo->ai_addr);
 
    char ip4[INET_ADDRSTRLEN];                                            // INET_ADDRESSLEN is defined in <netinet/in.h>
    inet_ntop(servinfo->ai_family, &sin->sin_addr, ip4, INET_ADDRSTRLEN); // From network byte order to presentation order

    printf("%s\n", ip4);

    // Be kind, free memory
    freeaddrinfo(servinfo);

    return 0;
}
