#ifndef INCLUDES_H
#define INCLUDES_H

/* INCLUDES */

// Standard lib
#include <iostream>
#include <sstream>
#include <unistd.h>

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

// Widgets
class TargetBoxWidget : public QWidget
{
    Q_OBJECT

public:
    TargetBoxWidget();
    ~TargetBoxWidget();

private:
    QLabel *label;
    QLineEdit *box;
    QHBoxLayout *layout;
};

class MethodBoxWidget : public QWidget
{
    Q_OBJECT

public:
    MethodBoxWidget();
    ~MethodBoxWidget();

private:
    QLabel *label;
    QComboBox *box;
    QHBoxLayout *layout;
};

class HeadersBoxWidget : public QWidget
{
    Q_OBJECT

public:
    HeadersBoxWidget();
    ~HeadersBoxWidget();

private:
    QLabel *label;
    QCheckBox *box;
    QHBoxLayout *layout;
};

class RequestBoxWidget : public QWidget
{
    Q_OBJECT

public:
    RequestBoxWidget();
    ~RequestBoxWidget();

private:
    QGroupBox *group;
    QPlainTextEdit *text;
    QVBoxLayout *layout;
};

class ResponseBoxWidget : public QWidget
{
    Q_OBJECT

public:
    ResponseBoxWidget();
    ~ResponseBoxWidget();

private:
    QGroupBox *group;
    QPlainTextEdit *text;
    QVBoxLayout *layout;
};

class MainWindow : public QWidget
{
    Q_OBJECT

public:
    MainWindow();
    ~MainWindow();

private:
    QGridLayout *layout;
    QPushButton *buttonSend;
    QPushButton *buttonClear;

    TargetBoxWidget *target;
    MethodBoxWidget *method;
    HeadersBoxWidget *headers;

    RequestBoxWidget *request;
    ResponseBoxWidget *response;
};

// Network
std::string request(std::string method, std::string target, std::string content);

#endif // INCLUDES_H
