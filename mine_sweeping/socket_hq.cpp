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
        if(this->pVecSocket.size() == 0)
        {
            QTcpSocket *tempTcpSocket = new QTcpSocket();
            this->pVecSocket.append(tempTcpSocket);
        }
        else if(this->pVecSocket[0] == NULL)
        {
            this->pVecSocket[0] = new QTcpSocket();
        }
        connect(this->pVecSocket[0], SIGNAL(readyRead()), this, SLOT(on_socket_Read_Data()));
        connect(this->pVecSocket[0], SIGNAL(connected()), this, SLOT(on_socket_Connected()));
        this->pVecSocket[0]->connectToHost(this->IP,this->portNum);
        connect(this->pVecSocket[0], SIGNAL(disconnected()), this, SLOT(on_socket_Disconnected()));
    }
}

void socket_hq::on_button_disconnect_clicked()
{
    if(SOCKET_TYPE_SERVER == socketType)
    {
        QTcpSocket *tempSender = (QTcpSocket *)sender();
        char buffer[BUFFER_MAX_LEN];
        memset(buffer, 0, BUFFER_MAX_LEN);
        sprintf(buffer, "server is offline!\n");
        serverBroadCastMsg(buffer);
    }
    this->serverDisconnectFlag = 1;
    QVector<QTcpSocket *>::iterator iter;
    for(iter = this->pVecSocket.begin(); iter != this->pVecSocket.end(); iter++)
    {
        if(*iter != NULL)
        {
            (*iter)->disconnectFromHost();
        }
    }
    if(SOCKET_TYPE_SERVER == socketType)
    {
        cout << "count: " << this->pVecSocket.size() << endl;
        this->pVecSocket.remove(0,this->pVecSocket.size());
        this->label_status->setText("status: Listening port: " + this->lineEdit_Port->text());
    }
    this->serverDisconnectFlag = 0;
}

void socket_hq::on_button_send_clicked()
{
    if(SOCKET_TYPE_CLIENT == socketType)
    {
        if(this->pVecSocket.size() != 0)
        {
            this->pVecSocket[0]->write(this->textedit_output->toPlainText().toLatin1() + '\n');
            this->textedit_output->clear();
        }
    }
}

void socket_hq::on_server_New_Connect()
{
    char buffer[BUFFER_MAX_LEN];
    memset(buffer, 0, BUFFER_MAX_LEN);
    QTcpSocket *pTempSocket = this->pServer->nextPendingConnection();
    cout << "new connection!!" << endl;
    this->label_status->setText("status: connected");
    this->pVecSocket.append(pTempSocket);
    sprintf(buffer, "0x%x connect!\n", (unsigned int)this->pVecSocket.constLast());
    serverBroadCastMsg(buffer);
    connect(this->pVecSocket.constLast(), SIGNAL(readyRead()), this, SLOT(on_socket_Read_Data()));
    connect(this->pVecSocket.constLast(), SIGNAL(disconnected()), this, SLOT(on_socket_Disconnected()));
}

void socket_hq::on_socket_Read_Data()
{
    QByteArray buffer;
    QTcpSocket *tempSocketRead = (QTcpSocket *)sender();
    cout << "receive a new message!" << endl;
    buffer = tempSocketRead->readAll();
    if(SOCKET_TYPE_SERVER == socketType)
    {
        serverBroadCastMsg(buffer.data());
    }
    else
    {
        this->textedit_input->setText(this->textedit_input->toPlainText() + buffer);
    }

    //buffer = this->pSocket->readAll();
    //cout << buffer.data() << endl;
}

void socket_hq::on_socket_Connected()
{
    this->label_status->setText("status: connected");
}

void socket_hq::on_socket_Disconnected()
{
    if(SOCKET_TYPE_SERVER == socketType)
    {
        if(this->serverDisconnectFlag == 1)
        {
            return;
        }
        QTcpSocket *tempSender = (QTcpSocket *)sender();
        char buffer[BUFFER_MAX_LEN];
        memset(buffer, 0, BUFFER_MAX_LEN);
        sprintf(buffer, "0x%x disconnect!\n", (unsigned int)tempSender);
        serverBroadCastMsg(buffer);

        this->pVecSocket.removeOne(tempSender);
        if(pVecSocket.size() == 0)
        {
            this->label_status->setText("status: Listening port: " + this->lineEdit_Port->text());
        }
    }
    else if(SOCKET_TYPE_CLIENT == socketType)
    {
        this->label_status->setText("status: disconnected");
        delete(pVecSocket[0]);
        this->pVecSocket[0] = NULL;
    }
}

void socket_hq::InitSocketHq(char socketType)
{
    setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
    setMinimumHeight(500);
    setMinimumWidth(400);
    this->serverDisconnectFlag = 0;
    this->socketType = socketType;
    this->gridlayout_upper = new QGridLayout();
    this->label_IP = new QLabel("IP:");
    this->lineEdit_IP = new QLineEdit("127.0.0.1");
    this->label_Port = new QLabel("Port:");
    this->lineEdit_Port = new QLineEdit("2345");
    this->label_status = new QLabel();
    this->label_status->setFixedHeight(20);
    this->button_connect = new QPushButton();
    this->button_disconnect = new QPushButton("disconnect");
    this->button_start = new QPushButton("start");
    this->button_send = new QPushButton("send");
    this->textedit_input = new QTextEdit();
    this->textedit_input->setReadOnly(1);
    this->textedit_output = new QTextEdit();
    this->textedit_input->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);
    this->textedit_output->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);
    gridlayout_upper->addWidget(label_IP, 0, 0, 1, 1);
    gridlayout_upper->addWidget(lineEdit_IP, 0, 1, 1, 1);
    gridlayout_upper->addWidget(label_Port, 0, 2, 1, 1);
    gridlayout_upper->addWidget(lineEdit_Port, 0, 3, 1, 1);
    gridlayout_upper->addWidget(button_connect, 1, 0, 1, 2);
    gridlayout_upper->addWidget(button_disconnect, 1, 2, 1, 2);
    gridlayout_upper->addWidget(textedit_input, 2, 0, 4, 4);
    gridlayout_upper->addWidget(textedit_output, 6, 0, 2, 4);
    gridlayout_upper->addWidget(button_start, 8, 0, 1, 2);
    gridlayout_upper->addWidget(button_send, 8, 2, 1, 2);
    gridlayout_upper->addWidget(label_status, 9, 0, 1, 4);
    setLayout(gridlayout_upper);
    if(SOCKET_TYPE_SERVER == socketType)
    {
        this->lineEdit_IP->setText("127.0.0.1");
        this->lineEdit_IP->setEnabled(false);
        this->label_status->setText("status: Not Listening");
        this->button_connect->setText("Listen");
        this->pServer = new QTcpServer();
        connect(this->pServer,SIGNAL(newConnection()),this,SLOT(on_server_New_Connect()));
        connect(this->button_connect,SIGNAL(clicked()),this,SLOT(on_button_connect_clicked()));
        connect(this->button_disconnect,SIGNAL(clicked()),this,SLOT(on_button_disconnect_clicked()));
    }
    else if(SOCKET_TYPE_CLIENT == socketType)
    {
        this->label_status->setText("status: Not Connected");
        this->button_connect->setText("Connect");
        connect(this->button_connect,SIGNAL(clicked()),this,SLOT(on_button_connect_clicked()));
        connect(this->button_disconnect,SIGNAL(clicked()),this,SLOT(on_button_disconnect_clicked()));
    }
    else
    {
    }
    connect(this->button_send,SIGNAL(clicked()),this,SLOT(on_button_send_clicked()));


}

void socket_hq::serverBroadCastMsg(const char *buffer)
{
    if(buffer == NULL)
    {
        return;
    }
    cout << "BroadCastMsg: \n" << buffer << endl;
    this->textedit_input->setText(this->textedit_input->toPlainText() + QString(buffer));
    QVector<QTcpSocket *>::iterator iter;
    for(iter = this->pVecSocket.begin(); iter != this->pVecSocket.end(); iter++)
    {
        (*iter)->write(buffer);
    }

}
