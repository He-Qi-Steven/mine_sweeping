#ifndef MODE_CHOICE_H
#define MODE_CHOICE_H

#include <QDialog>
#include "mainwindow.h"
#include <QCloseEvent>
#include <QPushButton>

namespace Ui {
class mode_choice;
}

class mode_choice : public QDialog
{
    Q_OBJECT

public:
    explicit mode_choice(QWidget *parent = 0);
    ~mode_choice();

private slots:
    void on_modeButton_Exit_clicked();

    void on_modeButton_Normal_pressed();

    void on_modeButton_Designed_clicked();

    void on_designedButton_Return_clicked();

private:
    Ui::mode_choice *ui;
    MainWindow *pNormalWindow;
    QPushButton *modeButton_normal;
    QPushButton *modeButton_designed;
    QPushButton *modeButton_Exit;

    QPushButton *designedButton_New;
    QPushButton *designedButton_Load;
    QPushButton *designedButton_Return;

    void Set_modeButton_visible(bool flag);
    void Set_designedButton_visible(bool flag);

    void Init_modeWindow();

    void closeEvent(QCloseEvent *event);
};

#endif // MODE_CHOICE_H
