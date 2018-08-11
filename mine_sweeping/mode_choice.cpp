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


