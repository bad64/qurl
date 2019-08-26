#include "includes.h"

MainWindow::MainWindow()
{
    setWindowTitle("qurl");
    mainWidget = new QWidget();
    setCentralWidget(mainWidget);

    layout = new QGridLayout();

    buttonSend = new QPushButton("Go");
    QObject::connect(buttonSend, SIGNAL(clicked()), this, SLOT(sendRequest()));

    buttonClear = new QPushButton("Clear");
    QObject::connect(buttonClear, SIGNAL(clicked()), this, SLOT(clear()));

    target = new TargetBoxWidget();
    method = new MethodBoxWidget();
    headers = new HeadersBoxWidget();
    request = new RequestBoxWidget();
    response = new ResponseBoxWidget();

    layout->setRowStretch(3, 5);
    layout->setColumnStretch(2, 5);

    layout->addWidget(target, 0, 0, 1, 5);
    layout->addWidget(method, 1, 0, 1, 5);
    layout->addWidget(headers, 2, 0, 1, 5);
    layout->addWidget(request->item(), 3, 0, 4, 2);
    layout->addWidget(response->item(), 3, 2, 3, 4);
    layout->addWidget(buttonClear, 6, 2, 1, 1);
    layout->addWidget(buttonSend, 6, 3, 1, 1);

    mainWidget->setLayout(layout);
    setMinimumSize(800,600);
}

void MainWindow::sendRequest()
{
    if (target->get().size() != 0)
    {
        std::string resp = curlRequest(method->get(), target->get(), request->get());

        std::string _headers = "";
        std::string _body = "";
        if (resp != "Connection timed out")
        {
            _headers = resp.substr(0, resp.find("\r\n\r\n")+4);
            _body = resp.substr(resp.find("\r\n\r\n")+4);
        }

        // Alter the body to make it look like we actually parsed the JSON
        //if (method->get() == "POST")
        {
            uint8_t level = 0;
            size_t size = _body.size();
            bool noparse = false;
            for (unsigned int i = 0; i < size; i++)
            {
                // Check for quotation marks
                if ((_body[i] == '\"') && (_body[i-1] != '\\'))
                {
                    if (noparse == false) noparse = true;
                    else if (noparse == true) noparse = false;
                }
                else if ((_body[i] == '{') || (_body[i] == '['))
                {
                    if (noparse == false)
                    {
                        level++;
                        _body.insert(i+1, 1, '\n');
                    }
                }
                else if ((_body[i] == '}') || (_body[i] == ']'))
                {
                    if (noparse == false)
                    {
                        if (level - 1 >= 0) level--;

                        char buf = _body[i];
                        _body[i] = '\n';
                        _body.insert(i+1, level, '\t');
                        _body.insert(i+1+level, 1, buf);
                        i = i+1+level;
                    }
                }
                else if (_body[i] == ',')
                {
                    if (noparse == false) _body[i+1] = '\n';
                }
                else if (_body[i] == '\n')
                {
                    if (noparse == false) _body.insert(i+1, level, '\t');
                }

                size = _body.size();
            }
        }

        std::stringstream ss;

        if (headers->get() == true)
            ss << _headers;

        ss << _body;
        response->set(ss.str());
    }
    else
    {
        response->set("Point me somewhere !");
    }
}

MainWindow::~MainWindow()
{

}

void MainWindow::clear()
{
    response->set("");
}
