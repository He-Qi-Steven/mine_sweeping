#ifndef SOCKET_CLIENT_HQ_H
#define SOCKET_CLIENT_HQ_H

#include <QWidget>
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
class socket_client_hq;
}

class socket_client_hq : public QWidget
{
    Q_OBJECT

public:
    explicit socket_client_hq(QWidget *parent = 0);
    ~socket_client_hq();

private:
    Ui::socket_client_hq *ui;
    QGridLayout *mainLayout;
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
    QTcpSocket *pClientSocket;

    QString IP;
    int portNum;
    void InitSocketHq();

private slots:
    void on_button_connect_clicked();
    void on_button_disconnect_clicked();
    void on_button_start_clicked();
    void on_button_send_clicked();
    void on_socket_Read_Data();
    void on_socket_Connected();
    void on_socket_Disconnected();
};

#endif // SOCKET_CLIENT_HQ_H
