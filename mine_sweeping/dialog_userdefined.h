#ifndef DIALOG_USERDEFINED_H
#define DIALOG_USERDEFINED_H

#include <QDialog>

namespace Ui {
class Dialog_userDefined;
}

class Dialog_userDefined : public QDialog
{
    Q_OBJECT

public:
    Dialog_userDefined(QWidget *parent, void **paras);
    ~Dialog_userDefined();

private slots:
    void on_buttonBox_accepted();

private:
    Ui::Dialog_userDefined *ui;
    void *p;//用来接收由外部申请的内存块地址
};

#endif // DIALOG_USERDEFINED_H
