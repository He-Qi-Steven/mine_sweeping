#include "dialog_userdefined.h"
#include "ui_dialog_userdefined.h"

Dialog_userDefined::Dialog_userDefined(void **paras, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog_userDefined)
{
    ui->setupUi(this);
    InitWidget();
    //this->p = *paras;
    this->pstr = (strParas *)*paras;
}

Dialog_userDefined::~Dialog_userDefined()
{
    delete ui;
}

void Dialog_userDefined::on_buttonBox_accepted()
{
    //内存块：行+列+雷数
    pstr->raw = this->pSpinBox_raw->value();
    pstr->column = this->pSpinBox_column->value();
    pstr->num_mine = this->pSpinBox_mineNum->value();
}

void Dialog_userDefined::InitWidget()
{
    pSpinBox_raw = new QSpinBox();
    pSpinBox_column = new QSpinBox();
    pSpinBox_mineNum = new QSpinBox();
    pSpinBox_mineNum->setMinimum(1);
    pLabelRaw = new QLabel("Raw:");
    pLabelColumn = new QLabel("Column:");
    pLabelMineNum = new QLabel("MineNum:");
    pSpinBoxLayout = new QVBoxLayout();
    pLabelLayout = new QVBoxLayout();
    pMainlayout = new QHBoxLayout();
    pSpinBoxLayout->addWidget(pSpinBox_raw);
    pSpinBoxLayout->addWidget(pSpinBox_column);
    pSpinBoxLayout->addWidget(pSpinBox_mineNum);
    pLabelLayout->addWidget(pLabelRaw);
    pLabelLayout->addWidget(pLabelColumn);
    pLabelLayout->addWidget(pLabelMineNum);
    pMainlayout->addLayout(pLabelLayout);
    pMainlayout->addLayout(pSpinBoxLayout);
    this->setLayout(pMainlayout);
}
