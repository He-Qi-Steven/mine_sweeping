#include "socket_hq.h"
#include "ui_socket_hq.h"
#include <iostream>

using namespace  std;

socket_hq::socket_hq(char socketType, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::socket_hq)
{
    ui->setupUi(this);
    InitSocketHq(socketType);
}

socket_hq::~socket_hq()
{
    delete ui;
}

void socket_hq::on_button_connect_clicked()
{
    this->IP = this->lineEdit_IP->text();
    this->portNum = this->lineEdit_Port->text().toInt();
    if(SOCKET_TYPE_SERVER == this->socketType)
    {
        this->pServer->listen(QHostAddress::Any, this->portNum);
        this->label_status->setText("status: Listening port: " + this->lineEdit_Port->text());
    }
    else if(SOCKET_TYPE_CLIENT == this->socketType)
    {
        this->pSocket->connectToHost(this->IP,this->portNum);
    }
}

void socket_hq::on_server_New_Connect()
{
    cout << "new connection!!" << endl;
    this->label_status->setText("status: connected");
    this->pSocket = this->pServer->nextPendingConnection();
    this->pSocket->write("Hello!");
}

void socket_hq::on_socket_Read_Data()
{
    cout << "receive a new message!" << endl;
    this->label_status->setText("status: connected");
}

void socket_hq::InitSocketHq(char socketType)
{
    this->socketType = socketType;
    this->gridlayout_upper = new QGridLayout();
    this->label_IP = new QLabel("IP:");
    this->lineEdit_IP = new QLineEdit();
    this->label_Port = new QLabel("Port:");
    this->lineEdit_Port = new QLineEdit();
    this->label_status = new QLabel();
    this->button_connect = new QPushButton();
    gridlayout_upper->addWidget(label_IP, 0, 0, 1, 1);
    gridlayout_upper->addWidget(lineEdit_IP, 0, 1, 1, 1);
    gridlayout_upper->addWidget(label_Port, 0, 2, 1, 1);
    gridlayout_upper->addWidget(lineEdit_Port, 0, 3, 1, 1);
    gridlayout_upper->addWidget(label_status, 1, 0, 1, 2);
    gridlayout_upper->addWidget(button_connect, 1, 2, 1, 2);

    if(SOCKET_TYPE_SERVER == socketType)
    {
        this->lineEdit_IP->setText("127.0.0.1");
        this->lineEdit_IP->setEnabled(false);
        this->label_status->setText("status: Not Listening");
        this->button_connect->setText("Listen");
        this->pServer = new QTcpServer();
        connect(this->pServer,SIGNAL(newConnection()),this,SLOT(on_server_New_Connect()));
    }
    else if(SOCKET_TYPE_CLIENT == socketType)
    {
        this->label_status->setText("status: Not Connected");
        this->button_connect->setText("Connect");
    }
    else
    {
    }


    ui->verticalLayout_socketMain->addLayout(gridlayout_upper);


    this->pSocket = new QTcpSocket();
    connect(this->button_connect,SIGNAL(clicked()),this,SLOT(on_button_connect_clicked()));
    connect(this->pSocket, SIGNAL(readyRead()), this, SLOT(on_socket_Read_Data()));


}
