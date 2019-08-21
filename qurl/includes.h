#ifndef INCLUDES_H
#define INCLUDES_H

/* INCLUDES */

// Standard lib
#include <iostream>
#include <sstream>
#include <unistd.h>

// Sockets
#include <QTcpSocket>

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
    std::string get();

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
    std::string get();

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
    bool get();

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
    QGroupBox* item();
    std::string get();

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
    QGroupBox* item();
    std::string get();
    void set(std::string content);

private:
    QGroupBox *group;
    QPlainTextEdit *text;
    QVBoxLayout *layout;
};

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow();
    ~MainWindow();

public slots:
    void sendRequest();
    void clear();

private:
    QWidget *mainWidget;
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
std::string curlRequest(std::string method, std::string target, std::string content);

#endif // INCLUDES_H
