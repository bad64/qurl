#include "includes.h"
#include <cerrno>
#include <cstring>

std::string curlRequest(std::string method, std::string target, std::string content)
{
    // Do we have a HTTP prefix ?
    int offset = 0;
    if (target.find("http://") != std::string::npos)
        offset = 7;

    // Get resource first
    std::string resource = "/";
    if (target.find('/', 8) != std::string::npos)
        resource = target.substr(target.find('/', offset));

    // Get port second
    uint16_t port = 80;
    if (target.find(':', 8) != std::string::npos)
    {
        if (resource == "/")
            port = std::stoul(target.substr(target.find(':', offset)+1));
        else
            port = std::stoul(target.substr(target.find(':', offset)+1, target.find('/', offset)));
    }

    //Get domain last
    std::string domain;
    if (port == 80)
        domain = target.substr(offset, target.find('/', offset));
    else
        domain = target.substr(offset, target.find(':', offset));

    // Special cases
    if (domain == "localhost")
    {
        target.replace(target.find(domain), domain.size(), "127.0.0.1");
        domain = "127.0.0.1";
    }

    // Set up connection socket
    QTcpSocket* sock = new QTcpSocket();
    sock->connectToHost(QString::fromStdString(domain), port);
    if (!sock->waitForConnected(30000))
    {
        std::stringstream err;
        err << "Connection timed out";
        return err.str();
    }

    // Build the HTTP request
    std::stringstream req;
    req << method << " " << resource << " HTTP/1.1\r\n";
    req << "Host: " << domain << "\r\n";
    if (method == "POST")
    {
        req << "Content-type: application/json\r\n";
        req << "Content-length: " << content.length() << "\r\n";
    }
    req << "Connection: close\r\n\r\n";

    if (method == "POST")
        req << content;

    // Send it
    std::stringstream resp;
    sock->write(req.str().c_str());
    sock->waitForReadyRead();
    resp << sock->readAll().toStdString();

    sock->close();
    return resp.str();
}
