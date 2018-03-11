#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <iostream>

using namespace std;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //默认为初级
    m.GenerateMap(defaultMap[0][0],defaultMap[0][1],defaultMap[0][2]);
}

MainWindow::~MainWindow()
{
    delete ui;
}

bool MainWindow::ChangeLevel(int raw, int column, int mineNum)
{
    m.GenerateMap(raw, column, mineNum);
    return true;
}
