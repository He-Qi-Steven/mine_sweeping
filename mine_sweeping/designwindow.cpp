#include "designwindow.h"
#include "ui_designwindow.h"

DesignWindow::DesignWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::DesignWindow)
{
    ui->setupUi(this);
    pMainlayout = new QVBoxLayout();
    pGridlayout = new QGridLayout();
    pButtonlayout = new QHBoxLayout();
    pQuit_button = new QPushButton("Quit");
    pSave_button = new QPushButton("Save");
    pStart_button = new QPushButton("Start");
    pButtonlayout->addWidget(pQuit_button);
    pButtonlayout->addWidget(pSave_button);
    pButtonlayout->addWidget(pStart_button);
    pMainlayout->addLayout(pGridlayout);
    pMainlayout->addLayout(pButtonlayout);
    this->setLayout(pMainlayout);
}

DesignWindow::~DesignWindow()
{
    delete ui;
}
