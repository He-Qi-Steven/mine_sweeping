#ifndef MODE_CHOICE_H
#define MODE_CHOICE_H

#include <QDialog>
#include "mainwindow.h"
#include <QCloseEvent>

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

private:
    Ui::mode_choice *ui;
    MainWindow *pNormalWindow;

    void closeEvent(QCloseEvent *event);
};

#endif // MODE_CHOICE_H
