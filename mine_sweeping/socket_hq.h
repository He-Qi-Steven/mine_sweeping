#ifndef SOCKET_HQ_H
#define SOCKET_HQ_H

#include <QWidget>
#include <QLineEdit>
#include <QLabel>
#include <QGridLayout>
#include <QPushButton>
#include <QTcpServer>
#include <QTcpSocket>
#include <QTextEdit>

#define SOCKET_TYPE_SERVER 0
#define SOCKET_TYPE_CLIENT 1

#define BUFFER_MAX_LEN 512

namespace Ui {
class socket_hq;
}

class socket_hq : public QWidget
{
    Q_OBJECT

public:
    explicit socket_hq(char socketType, QWidget *parent = 0);
    ~socket_hq();

private slots:
    void on_button_connect_clicked();
    void on_button_disconnect_clicked();
    void on_button_send_clicked();
    void on_server_New_Connect();
    void on_socket_Read_Data();
    void on_socket_Connected();
    void on_socket_Disconnected();

private:
    Ui::socket_hq *ui;

    char socketType;

    QGridLayout *gridlayout_upper;
    QLabel *label_IP;
    QLabel *label_Port;
    QLineEdit *lineEdit_IP;
    QLineEdit *lineEdit_Port;
    QLabel *label_status;
    QPushButton *button_connect;
    QPushButton *button_disconnect;
    QPushButton *button_start;
    QPushButton *button_send;
    QTextEdit *textedit_output;
    QTextEdit *textedit_input;


    QTcpServer *pServer;
    QVector<QTcpSocket *> pVecSocket;

    //在server手动触发disconnect时，置1，处理结束，恢复为0
    char serverDisconnectFlag;

    QString IP;
    int portNum;

    void InitSocketHq(char socketType);
    void serverBroadCastMsg(const char * buffer);
};

#endif // SOCKET_HQ_H
