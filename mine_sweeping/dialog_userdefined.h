#ifndef DIALOG_USERDEFINED_H
#define DIALOG_USERDEFINED_H

#include <QDialog>
#include <QLayout>
#include <QSpinBox>
#include <QLabel>

namespace Ui {
class Dialog_userDefined;
}

typedef struct
{
    int raw;
    int column;
    int num_mine;
}strParas;

class Dialog_userDefined : public QDialog
{
    Q_OBJECT

public:
    Dialog_userDefined(void **paras, QWidget *parent = 0);
    ~Dialog_userDefined();

private slots:
    void on_buttonBox_accepted();

private:
    Ui::Dialog_userDefined *ui;
    void *p;//用来接收由外部申请的内存块地址
    strParas *pstr;

    QSpinBox *pSpinBox_raw;
    QSpinBox *pSpinBox_column;
    QSpinBox *pSpinBox_mineNum;
    QLabel *pLabelRaw;
    QLabel *pLabelColumn;
    QLabel *pLabelMineNum;
    QVBoxLayout *pSpinBoxLayout;
    QVBoxLayout *pLabelLayout;
    QHBoxLayout *pMainlayout;


    void InitWidget();
};

#endif // DIALOG_USERDEFINED_H
