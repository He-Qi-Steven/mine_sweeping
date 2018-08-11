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

void mode_choice::on_designedButton_Return_clicked()
{
    this->Set_modeButton_visible(true);
    this->Set_designedButton_visible(false);
}

void mode_choice::Set_modeButton_visible(bool flag)
{
    modeButton_normal->setVisible(flag);
    modeButton_designed->setVisible(flag);
    modeButton_Exit->setVisible(flag);
}

void mode_choice::Set_designedButton_visible(bool flag)
{
    designedButton_New->setVisible(flag);
    designedButton_Load->setVisible(flag);
    designedButton_Return->setVisible(flag);
}

void mode_choice::Init_modeWindow()
{
    this->modeButton_normal = new QPushButton("Normal");
    this->modeButton_designed = new QPushButton("Designed");
    this->modeButton_Exit = new QPushButton("Exit");
    modeButton_normal->setSizePolicy(QSizePolicy::Policy::Preferred,QSizePolicy::Policy::Preferred);
    modeButton_designed->setSizePolicy(QSizePolicy::Policy::Preferred,QSizePolicy::Policy::Preferred);
    modeButton_Exit->setSizePolicy(QSizePolicy::Policy::Preferred,QSizePolicy::Policy::Preferred);
    ui->verticalLayout->addWidget(modeButton_normal);
    ui->verticalLayout->addWidget(modeButton_designed);
    ui->verticalLayout->addWidget(modeButton_Exit);

    this->designedButton_New = new QPushButton("New");
    this->designedButton_Load = new QPushButton("Load");
    this->designedButton_Return = new QPushButton("Return");
    designedButton_New->setSizePolicy(QSizePolicy::Policy::Preferred,QSizePolicy::Policy::Preferred);
    designedButton_Load->setSizePolicy(QSizePolicy::Policy::Preferred,QSizePolicy::Policy::Preferred);
    designedButton_Return->setSizePolicy(QSizePolicy::Policy::Preferred,QSizePolicy::Policy::Preferred);
    ui->verticalLayout->addWidget(designedButton_New);
    ui->verticalLayout->addWidget(designedButton_Load);
    ui->verticalLayout->addWidget(designedButton_Return);

    connect(this->modeButton_normal,SIGNAL(clicked()),this,SLOT(on_modeButton_Normal_pressed()));
    connect(this->modeButton_Exit,SIGNAL(clicked()),this,SLOT(on_modeButton_Exit_clicked()));
    connect(this->modeButton_designed,SIGNAL(clicked()),this,SLOT(on_modeButton_Designed_clicked()));
    connect(this->designedButton_Return,SIGNAL(clicked()),this,SLOT(on_designedButton_Return_clicked()));

    this->Set_modeButton_visible(true);
    this->Set_designedButton_visible(false);
}


