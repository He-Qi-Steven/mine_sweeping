#include "socket_server_hq.h"
#include "ui_socket_server_hq.h"
#include <iostream>

socket_server_hq::socket_server_hq(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::socket_server_hq)
{
    ui->setupUi(this);
    InitSocketHq();
}

socket_server_hq::~socket_server_hq()
{
    delete mainLayout;
    delete label_IP;
    delete label_Port;
    delete lineEdit_IP;
    delete lineEdit_Port;
    delete label_status;
    delete button_listen;
    delete button_disconnect;
    delete button_start;
    delete button_send;
    delete textedit_output;
    delete textedit_input;
    delete pServer;
    // pVecSocket 内存释放问题遗留;

    delete ui;
}

void socket_server_hq::on_button_listen_clicked()
{
    this->IP = this->lineEdit_IP->text();
    this->portNum = this->lineEdit_Port->text().toInt();
    this->pServer->listen(QHostAddress::Any, this->portNum);
    this->label_status->setText("status: Listening port: " + this->lineEdit_Port->text());
}

void socket_server_hq::on_button_disconnect_clicked()
{
    char buffer[BUFFER_MAX_LEN];
    memset(buffer, 0, BUFFER_MAX_LEN);
    sprintf(buffer, "server is offline!\n");
    serverBroadCastMsg(buffer);
    this->serverDisconnectFlag = 1;
    QVector<QTcpSocket *>::iterator iter;
    for(iter = this->pVecSocket.begin(); iter != this->pVecSocket.end(); iter++)
    {
        if(*iter != NULL)
        {
            (*iter)->disconnectFromHost();
        }
    }
    this->pVecSocket.remove(0,this->pVecSocket.size());
    this->label_status->setText("status: Listening port: " + this->lineEdit_Port->text());
    this->serverDisconnectFlag = 0;
}

void socket_server_hq::on_button_send_clicked()
{
    this->messageOrigin = "Server: ";
    char buffer[BUFFER_MAX_LEN] = "";
    sprintf(buffer, "%s\n", this->textedit_output->toPlainText().toLatin1().data());
    serverBroadCastMsg(buffer);
    this->textedit_output->clear();
}

void socket_server_hq::on_server_New_Connect()
{
    char buffer[BUFFER_MAX_LEN];
    memset(buffer, 0, BUFFER_MAX_LEN);
    QTcpSocket *pTempSocket = this->pServer->nextPendingConnection();
    //cout << "new connection!!" << endl;
    this->label_status->setText("status: connecting number:");
    this->pVecSocket.append(pTempSocket);
    sprintf(buffer, "0x%x connect!\n", (unsigned int)this->pVecSocket.constLast());
    serverBroadCastMsg(buffer);
    connect(this->pVecSocket.constLast(), SIGNAL(readyRead()), this, SLOT(on_socket_Read_Data()));
    connect(this->pVecSocket.constLast(), SIGNAL(disconnected()), this, SLOT(on_socket_Disconnected()));
}

void socket_server_hq::on_socket_Read_Data()
{

    QByteArray buffer;
    QTcpSocket *tempSocketRead = (QTcpSocket *)sender();
    char bufTemp[50];
    sprintf(bufTemp, "0x%x: ", tempSocketRead);
    this->messageOrigin = bufTemp;
    //cout << "receive a new message!" << endl;
    buffer = tempSocketRead->readAll();
    serverBroadCastMsg(buffer.data());
}

void socket_server_hq::on_socket_Disconnected()
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

void socket_server_hq::InitSocketHq()
{
    this->setAttribute(Qt::WA_DeleteOnClose);
    setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
    setMinimumHeight(500);
    setMinimumWidth(400);
    this->serverDisconnectFlag = 0;
    this->mainLayout = new QGridLayout();
    this->label_IP = new QLabel("IP:");
    this->lineEdit_IP = new QLineEdit("127.0.0.1");
    this->label_Port = new QLabel("Port:");
    this->lineEdit_Port = new QLineEdit("2345");
    this->label_status = new QLabel();
    this->label_status->setFixedHeight(20);
    this->button_listen = new QPushButton();
    this->button_disconnect = new QPushButton("disconnect");
    this->button_start = new QPushButton("start");
    this->button_send = new QPushButton("send");
    this->textedit_input = new QTextEdit();
    this->textedit_input->setReadOnly(1);
    this->textedit_output = new QTextEdit();
    this->textedit_input->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);
    this->textedit_output->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);
    mainLayout->addWidget(label_IP, 0, 0, 1, 1);
    mainLayout->addWidget(lineEdit_IP, 0, 1, 1, 1);
    mainLayout->addWidget(label_Port, 0, 2, 1, 1);
    mainLayout->addWidget(lineEdit_Port, 0, 3, 1, 1);
    mainLayout->addWidget(button_listen, 1, 0, 1, 2);
    mainLayout->addWidget(button_disconnect, 1, 2, 1, 2);
    mainLayout->addWidget(textedit_input, 2, 0, 4, 4);
    mainLayout->addWidget(textedit_output, 6, 0, 2, 4);
    mainLayout->addWidget(button_start, 8, 0, 1, 2);
    mainLayout->addWidget(button_send, 8, 2, 1, 2);
    mainLayout->addWidget(label_status, 9, 0, 1, 4);
    setLayout(mainLayout);

    this->lineEdit_IP->setText("127.0.0.1");
    this->lineEdit_IP->setEnabled(false);
    this->label_status->setText("status: Not Listening");
    this->button_listen->setText("Listen");
    this->pServer = new QTcpServer();
    connect(this->pServer,SIGNAL(newConnection()),this,SLOT(on_server_New_Connect()));
    connect(this->button_listen,SIGNAL(clicked()),this,SLOT(on_button_listen_clicked()));
    connect(this->button_disconnect,SIGNAL(clicked()),this,SLOT(on_button_disconnect_clicked()));
    connect(this->button_send,SIGNAL(clicked()),this,SLOT(on_button_send_clicked()));
}

void socket_server_hq::serverBroadCastMsg(const char *buffer)
{
    if(buffer == NULL)
    {
        return;
    }
    //cout << "BroadCastMsg: \n" << buffer << endl;
    this->textedit_input->append(this->messageOrigin + QString(buffer));
    //this->textedit_input->setText(this->textedit_input->toPlainText() + this->messageOrigin + QString(buffer));
    QVector<QTcpSocket *>::iterator iter;
    for(iter = this->pVecSocket.begin(); iter != this->pVecSocket.end(); iter++)
    {
        (*iter)->write(this->messageOrigin.toLatin1().data());
        (*iter)->write(buffer);
    }
}
