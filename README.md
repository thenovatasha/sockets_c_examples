# sockets_c_examples
Learning socket programming in C by examples. Most of these examples are my notes while reading the highly instructive, and well written article from Beej. The article can be found at: https://beej.us/guide/bgnet/html/#audience.

This particular readme describes the different files that I have used and what they provide examples for. The examples cover IPv4, but also IPv6 (mostly in comments). For the terminology, a Client is simply a process that inititates the connection actively, whereas a server is the passive listener responding to the client.

#### Getsockaddr.c

The first step in creating any sort of connection - whether it is a Server side connection or a Client side connection is to get the address of the connection.
The address is made up of a 5-tuple with
(Protocol, Source IP address, Source port, Target IP address, Target port). 

Now, computers do not store domain names (e.g "google.com"), but instead will store IP addresses. While we can provide the domain name most of the time, we cannot always provide the IP address (because we don't know it or remember it). 
A DNS protocol is therefore required to resolve these domain names to IP addresses which the Internet Protocol (IP) uses to route all our requests made to those addresses. 

Since DNS resolution can be thought of as the prerequesite to an internet connection - I start off by trying to understand the getsockaddr.c

Initially, we pack `struct addrinfo hints` to indicate what the configuration preferences are. We set all of it's bytes to 0 (or NULL) as this is required by the getaddrinfo. For more information on the hints, checkout the [manual](https://www.man7.org/linux/man-pages/man3/getaddrinfo.3.html)

Then, we extract the address information we received and convert it to a presentable format for printing.

#### showip.c

You see, getaddrinfo may not only return a single IP. It may also return multiple IP addresses, and return both IPv4, and IPv6 addresses. 
The reason may be simple - a single domain may be distributed across many IP addresses for geographical reasons, or load balancing reasons. Therefore, the DNS 
may resolve it and get back mutiple responses. 

To accomodate this, the structure for addrinfo is actually a linked list - of different IP addresses. If you are a client, typically you will connect to the 
first one available, or may employ load balacing on your app to distribute the load randomly. 

#### bind.c

After the address is configured, (or for a client - found), we are ready to start requesting resources from the operating system. 
The first of which is a socket(....) call that creates a namespace - a description of the connection we are about to make. It returns a file descriptor
which is a fancy way of saying "a handle to a file". The file descriptor can be used to interact with the socket by sending and receiving information from it.

However, at this point, the system has not allocated any way of associating that file descriptor with any particular network resources. In other words,
the address, port etc are not yet "mapped" to it. This process is called "binding". And a bind() call is made. 

This bind call is necessary only if the code is for a server side application where the server needs to allocate resources and sit in a loop listening for incoming messages on that
descriptor associated with that file. If a proram is already interacting ("listening") on that port and address, then the binding fails with an error.

#### listen.c

#### accept.c

#### connect.c
