#include "includes.h"

TargetBoxWidget::TargetBoxWidget()
{
    label = new QLabel("Target");
    box = new QLineEdit();
    layout = new QHBoxLayout();

    layout->addWidget(label);
    layout->addWidget(box);

    setLayout(layout);
}
TargetBoxWidget::~TargetBoxWidget()
{}
std::string TargetBoxWidget::get()
{
    return box->text().toStdString();
}

MethodBoxWidget::MethodBoxWidget()
{
    label = new QLabel("Method");
    box = new QComboBox();
    box->addItem("GET");
    box->addItem("POST");
    layout = new QHBoxLayout();

    layout->addWidget(label);
    layout->addWidget(box);

    setLayout(layout);
}
MethodBoxWidget::~MethodBoxWidget()
{}
std::string MethodBoxWidget::get()
{
    return box->currentText().toStdString();
}

HeadersBoxWidget::HeadersBoxWidget()
{
    label = new QLabel("With headers");
    box = new QCheckBox();
    layout = new QHBoxLayout();

    layout->addWidget(label);
    layout->addWidget(box);

    setLayout(layout);
}
HeadersBoxWidget::~HeadersBoxWidget()
{}
bool HeadersBoxWidget::get()
{
    return box->isChecked();
}

RequestBoxWidget::RequestBoxWidget()
{
    group = new QGroupBox("Request body");
    text = new QPlainTextEdit();
    layout = new QVBoxLayout();

    layout->addWidget(text);
    group->setLayout(layout);
}
RequestBoxWidget::~RequestBoxWidget()
{}
QGroupBox* RequestBoxWidget::item()
{
    return group;
}
std::string RequestBoxWidget::get()
{
    return text->toPlainText().toStdString();
}

ResponseBoxWidget::ResponseBoxWidget()
{
    group = new QGroupBox("Response");
    text = new QPlainTextEdit();
    text->setReadOnly(true);
    text->setLineWrapMode(QPlainTextEdit::NoWrap);
    layout = new QVBoxLayout();

    layout->addWidget(text);
    group->setLayout(layout);
}
ResponseBoxWidget::~ResponseBoxWidget()
{}
QGroupBox* ResponseBoxWidget::item()
{
    return group;
}
std::string ResponseBoxWidget::get()
{
    return text->toPlainText().toStdString();
}
void ResponseBoxWidget::set(std::string content)
{
    text->setPlainText(QString::fromStdString(content));
}
