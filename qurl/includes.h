#ifndef INCLUDES_H
#define INCLUDES_H

/* INCLUDES */

// Standard lib
#include <iostream>
#include <sstream>

// Sockets
#if (defined (_WIN32) || defined (_WIN64))
    #include <winsock2.h>
    #include <windows.h>
#else
    #include <sys/ioctl.h>
    #include <sys/stat.h>
    #include <sys/types.h>
    #include <sys/socket.h>
    #include <arpa/inet.h>
    #include <netinet/in.h>

    #define closesocket(s) close(s)

    typedef int SOCKET;
    typedef struct sockaddr_in SOCKADDR_IN;
    typedef struct sockaddr SOCKADDR;
    typedef struct in_addr IN_ADDR;
#endif

// Qt
#include <QtWidgets>

/* PROTOTYPES */

// Network
std::string request(std::string method, std::string target, std::string content);

#endif // INCLUDES_H
