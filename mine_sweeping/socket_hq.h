#ifndef SOCKET_HQ_H
#define SOCKET_HQ_H

#include <QWidget>
#include <QLineEdit>
#include <QLabel>
#include <QGridLayout>
#include <QPushButton>
#include <QTcpServer>
#include <QTcpSocket>

#define SOCKET_TYPE_SERVER 0
#define SOCKET_TYPE_CLIENT 1

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
    void on_server_New_Connect();
    void on_socket_Read_Data();

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


    QTcpServer *pServer;
    QTcpSocket *pSocket;

    QString IP;
    int portNum;





    void InitSocketHq(char socketType);
};

#endif // SOCKET_HQ_H
