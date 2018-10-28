#include "mainwindow.h"
#include "mode_choice.h"
#include "ui_mode_choice.h"
#include <iostream>


using namespace std;

mode_choice::mode_choice(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::mode_choice)
{
    ui->setupUi(this);
    this->Init_modeWindow();

}

mode_choice::~mode_choice()
{
    delete ui;
}

void mode_choice::on_modeButton_Exit_clicked()
{
    this->close();
}

void mode_choice::closeEvent(QCloseEvent *event)
{
    exit(0);
}

void mode_choice::on_modeButton_Normal_pressed()
{
    pNormalWindow = new MainWindow();
    pNormalWindow->show();
    this->setVisible(false);
    connect(pNormalWindow,SIGNAL(close_signals()),this,SLOT(show()));
}

void mode_choice::on_modeButton_Designed_clicked()
{
    this->Set_modeButton_visible(false);
    this->Set_designedButton_visible(true);
}

void mode_choice::on_modeButton_Online_pressed()
{
    this->Set_modeButton_visible(false);
    this->Set_onlineButton_visible(true);
}

void mode_choice::on_designedButton_Return_clicked()
{
    this->Set_modeButton_visible(true);
    this->Set_designedButton_visible(false);
}

void mode_choice::on_designedButton_New_clicked()
{
    strParas *paras = (strParas *)malloc(sizeof(strParas));
    memset(paras, 0, sizeof(strParas));
    Dialog_userDefined diag((void **)&paras);
    diag.exec();
    if(0 == paras->raw || 0 == paras->column)
    {
        cout << "error: [user-defined]cannot get paras!" << endl;
        return ;
    }

    //pUserDefined = new Dialog_userDefined();
    /*
    pDesignWindow = new DesignWindow();
    pDesignWindow->show();
    this->setVisible(false);
    connect(pDesignWindow,SIGNAL(close_signals()),this,SLOT(show()));
    */
}

void mode_choice::on_onlineButton_Return_clicked()
{
    this->Set_modeButton_visible(true);
    this->Set_onlineButton_visible(false);
}

void mode_choice::on_onlineButton_Server_clicked()
{
    this->tcp_hq = new socket_hq(SOCKET_TYPE_SERVER);
    tcp_hq->show();
}

void mode_choice::on_onlineButton_Client_clicked()
{
    this->tcp_hq = new socket_hq(SOCKET_TYPE_CLIENT);
    tcp_hq->show();
}

void mode_choice::Set_modeButton_visible(bool flag)
{
    modeButton_normal->setVisible(flag);
    modeButton_designed->setVisible(flag);
    modeButton_Online->setVisible(flag);
    modeButton_Exit->setVisible(flag);
}

void mode_choice::Set_designedButton_visible(bool flag)
{
    designedButton_New->setVisible(flag);
    designedButton_Load->setVisible(flag);
    designedButton_Return->setVisible(flag);
}

void mode_choice::Set_onlineButton_visible(bool flag)
{
    onlineButton_Server->setVisible(flag);
    onlineButton_Client->setVisible(flag);
    onlineButton_Return->setVisible(flag);
}

void mode_choice::Init_modeWindow()
{
    this->pMainLayout = new QVBoxLayout();
    setLayout(this->pMainLayout);
    this->modeButton_normal = new QPushButton("Normal");
    this->modeButton_designed = new QPushButton("Designed");
    this->modeButton_Online = new QPushButton("Online");
    this->modeButton_Exit = new QPushButton("Exit");
    modeButton_normal->setSizePolicy(QSizePolicy::Policy::Preferred,QSizePolicy::Policy::Preferred);
    modeButton_designed->setSizePolicy(QSizePolicy::Policy::Preferred,QSizePolicy::Policy::Preferred);
    modeButton_Online->setSizePolicy(QSizePolicy::Policy::Preferred,QSizePolicy::Policy::Preferred);
    modeButton_Exit->setSizePolicy(QSizePolicy::Policy::Preferred,QSizePolicy::Policy::Preferred);
    pMainLayout->addWidget(modeButton_normal);
    pMainLayout->addWidget(modeButton_designed);
    pMainLayout->addWidget(modeButton_Online);
    pMainLayout->addWidget(modeButton_Exit);

    this->designedButton_New = new QPushButton("New");
    this->designedButton_Load = new QPushButton("Load");
    this->designedButton_Return = new QPushButton("Return");
    designedButton_New->setSizePolicy(QSizePolicy::Policy::Preferred,QSizePolicy::Policy::Preferred);
    designedButton_Load->setSizePolicy(QSizePolicy::Policy::Preferred,QSizePolicy::Policy::Preferred);
    designedButton_Return->setSizePolicy(QSizePolicy::Policy::Preferred,QSizePolicy::Policy::Preferred);

    pMainLayout->addWidget(designedButton_New);
    pMainLayout->addWidget(designedButton_Load);
    pMainLayout->addWidget(designedButton_Return);

    this->onlineButton_Server = new QPushButton("Server");
    this->onlineButton_Client = new QPushButton("Clinet");
    this->onlineButton_Return = new QPushButton("Return");
    onlineButton_Server->setSizePolicy(QSizePolicy::Policy::Preferred,QSizePolicy::Policy::Preferred);
    onlineButton_Client->setSizePolicy(QSizePolicy::Policy::Preferred,QSizePolicy::Policy::Preferred);
    onlineButton_Return->setSizePolicy(QSizePolicy::Policy::Preferred,QSizePolicy::Policy::Preferred);

    pMainLayout->addWidget(onlineButton_Server);
    pMainLayout->addWidget(onlineButton_Client);
    pMainLayout->addWidget(onlineButton_Return);

    connect(this->modeButton_normal,SIGNAL(clicked()),this,SLOT(on_modeButton_Normal_pressed()));
    connect(this->modeButton_Exit,SIGNAL(clicked()),this,SLOT(on_modeButton_Exit_clicked()));
    connect(this->modeButton_designed,SIGNAL(clicked()),this,SLOT(on_modeButton_Designed_clicked()));
    connect(this->modeButton_Online,SIGNAL(clicked()),this,SLOT(on_modeButton_Online_pressed()));
    connect(this->designedButton_Return,SIGNAL(clicked()),this,SLOT(on_designedButton_Return_clicked()));
    connect(this->designedButton_New,SIGNAL(clicked()),this,SLOT(on_designedButton_New_clicked()));
    connect(this->onlineButton_Server,SIGNAL(clicked()),this,SLOT(on_onlineButton_Server_clicked()));
    connect(this->onlineButton_Client,SIGNAL(clicked()),this,SLOT(on_onlineButton_Client_clicked()));
    connect(this->onlineButton_Return,SIGNAL(clicked()),this,SLOT(on_onlineButton_Return_clicked()));


    this->Set_modeButton_visible(true);
    this->Set_designedButton_visible(false);
    this->Set_onlineButton_visible(false);
}


