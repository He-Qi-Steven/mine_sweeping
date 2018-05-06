#include "dialog_userdefined.h"
#include "ui_dialog_userdefined.h"

Dialog_userDefined::Dialog_userDefined(QWidget *parent, void **paras) :
    QDialog(parent),
    ui(new Ui::Dialog_userDefined)
{
    ui->setupUi(this);
    this->p = *paras;
}

Dialog_userDefined::~Dialog_userDefined()
{
    delete ui;
}

void Dialog_userDefined::on_buttonBox_accepted()
{
    //内存块：行+列+雷数
    *(int *)p = ui->spinBox_raw->value();
    p += sizeof(int);
    *(int *)p = ui->spinBox_column->value();
    p += sizeof(int);
    *(int *)p = ui->spinBox_num_mine->value();
}
