#include "socket_client_hq.h"
#include "ui_socket_client_hq.h"
#include <iostream>

socket_client_hq::socket_client_hq(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::socket_client_hq)
{
    ui->setupUi(this);
    InitSocketHq();
}

socket_client_hq::~socket_client_hq()
{
    delete mainLayout;
    delete label_IP;
    delete label_Port;
    delete lineEdit_IP;
    delete lineEdit_Port;
    delete label_status;
    delete button_connect;
    delete button_disconnect;
    delete button_start;
    delete button_send;
    delete textedit_output;
    delete textedit_input;
    delete pClientSocket;
    delete ui;
}

void socket_client_hq::InitSocketHq()
{
    this->setAttribute(Qt::WA_DeleteOnClose);
    this->pClientSocket = NULL;
    this->pClientSocket = new QTcpSocket();
    if(this->pClientSocket == NULL)
    {
        this->close();
    }
    setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
    setMinimumHeight(500);
    setMinimumWidth(400);
    this->mainLayout = new QGridLayout();
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
    mainLayout->addWidget(label_IP, 0, 0, 1, 1);
    mainLayout->addWidget(lineEdit_IP, 0, 1, 1, 1);
    mainLayout->addWidget(label_Port, 0, 2, 1, 1);
    mainLayout->addWidget(lineEdit_Port, 0, 3, 1, 1);
    mainLayout->addWidget(button_connect, 1, 0, 1, 2);
    mainLayout->addWidget(button_disconnect, 1, 2, 1, 2);
    mainLayout->addWidget(textedit_input, 2, 0, 4, 4);
    mainLayout->addWidget(textedit_output, 6, 0, 2, 4);
    mainLayout->addWidget(button_start, 8, 0, 1, 2);
    mainLayout->addWidget(button_send, 8, 2, 1, 2);
    mainLayout->addWidget(label_status, 9, 0, 1, 4);
    setLayout(mainLayout);

    this->button_start->setEnabled(false);//只有处于连接状态，start按钮才可用
    this->label_status->setText("status: Not Connected");
    this->button_connect->setText("Connect");
    connect(this->button_connect,SIGNAL(clicked()),this,SLOT(on_button_connect_clicked()));
    connect(this->button_disconnect,SIGNAL(clicked()),this,SLOT(on_button_disconnect_clicked()));
    connect(this->button_send,SIGNAL(clicked()),this,SLOT(on_button_send_clicked()));
}


void socket_client_hq::on_button_connect_clicked()
{
    this->IP = this->lineEdit_IP->text();
    this->portNum = this->lineEdit_Port->text().toInt();
    this->pClientSocket->connectToHost(this->IP,this->portNum);
    connect(this->pClientSocket, SIGNAL(readyRead()), this, SLOT(on_socket_Read_Data()));
    connect(this->pClientSocket, SIGNAL(connected()), this, SLOT(on_socket_Connected()));
    connect(this->pClientSocket, SIGNAL(disconnected()), this, SLOT(on_socket_Disconnected()));
}

void socket_client_hq::on_button_disconnect_clicked()
{
    this->pClientSocket->disconnectFromHost();
}

void socket_client_hq::on_button_start_clicked()
{
    this->label_status->setText("status: Ready！");
}

void socket_client_hq::on_button_send_clicked()
{
    this->pClientSocket->write(this->textedit_output->toPlainText().toLatin1() + '\n');
    this->textedit_output->clear();
}

void socket_client_hq::on_socket_Read_Data()
{
    QByteArray buffer;
    QTcpSocket *tempSocketRead = (QTcpSocket *)sender();
    //std::cout << "receive a new message!" << endl;
    buffer = tempSocketRead->readAll();
    this->textedit_input->append(buffer);
}

void socket_client_hq::on_socket_Connected()
{
    this->label_status->setText("status: connected");
    this->button_start->setEnabled(true);
}

void socket_client_hq::on_socket_Disconnected()
{
    this->label_status->setText("status: disconnected");
    this->button_start->setEnabled(false);
}
