#ifndef SOCKET_SERVER_HQ_H
#define SOCKET_SERVER_HQ_H

#include <QWidget>
#include <QLineEdit>
#include <QLabel>
#include <QGridLayout>
#include <QPushButton>
#include <QTcpServer>
#include <QTcpSocket>
#include <QTextEdit>
#include "socket_message_hq.h"

namespace Ui {
class socket_server_hq;
}

class socket_server_hq : public QWidget
{
    Q_OBJECT

public:
    explicit socket_server_hq(QWidget *parent = 0);
    ~socket_server_hq();

private slots:
    void on_button_listen_clicked();
    void on_button_disconnect_clicked();
    void on_button_send_clicked();
    void on_server_New_Connect();
    void on_socket_Read_Data();
    void on_socket_Disconnected();

private:
    Ui::socket_server_hq *ui;

    QTcpServer *pServer;
    QVector<QTcpSocket *> pVecSocket;
    //在server手动触发disconnect时，置1，处理结束，恢复为0
    char serverDisconnectFlag;

    QString IP;
    int portNum;
    QGridLayout *mainLayout;
    QLabel *label_IP;
    QLabel *label_Port;
    QLineEdit *lineEdit_IP;
    QLineEdit *lineEdit_Port;
    QLabel *label_status;
    QPushButton *button_listen;
    QPushButton *button_disconnect;
    QPushButton *button_start;
    QPushButton *button_send;
    QTextEdit *textedit_output;
    QTextEdit *textedit_input;

    QString messageOrigin;//为了聊天窗口增加消息来源

    void InitSocketHq();
    void serverBroadCastMsg(const char * buffer);
};

#endif // SOCKET_SERVER_HQ_H
