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
