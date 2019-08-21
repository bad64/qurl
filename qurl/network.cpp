#include "includes.h"

std::string request(std::string method, std::string target, std::string content)
{
    // Get resource first
    std::string resource = "/";
    if (target.find('/') != std::string::npos)
        resource += target.substr('/');

    // Get port second
    unsigned int port = 80;
    if (target.find(':') != std::string::npos)
    {
        if (resource == "/")
            port = std::stoul(target.substr(target.find(':')));
        else
            port = std::stoul(target.substr(target.find(':'), target.find('/')));
    }

    int sock;
    struct sockaddr_in serv_addr;

    sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock < 0)
        return "ERROR: Could not open socket";

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(port);

    if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0)
        return "Unable to connect to target " + target;

    // Build the HTTP request
    std::stringstream req;
    req << method << " " << resource << " HTTP/1.1\r\n";
    req << "Host: ";
    if (port == 80)
        req << target.substr(0, target.find('/'));
    else
        req << target.substr(0, target.find(':'));
    req << "\r\nConnection: close\r\n\r\n";

    if (method == "POST")
        req << content;

    // Send it
    char buf[1024] = { '\0' };
    std::stringstream resp;

    send(sock, req.str().c_str(), req.str().size(), 0);

    int bytesread;
    do
    {
        bytesread = read(sock, buf, 1024);
        resp << buf;
        buf[0] = '\0';
    } while (bytesread == 1024);

    return resp.str();
}
