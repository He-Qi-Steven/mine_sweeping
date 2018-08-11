#include "mode_choice.h"
#include "ui_mode_choice.h"

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
