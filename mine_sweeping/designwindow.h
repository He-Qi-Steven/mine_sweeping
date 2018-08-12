#ifndef DESIGNWINDOW_H
#define DESIGNWINDOW_H

#include <QWidget>
#include <QLayout>
#include <QPushButton>

namespace Ui {
class DesignWindow;
}

class DesignWindow : public QWidget
{
    Q_OBJECT

public:
    explicit DesignWindow(QWidget *parent = 0);
    ~DesignWindow();

private:
    Ui::DesignWindow *ui;

    QVBoxLayout *pMainlayout;
    QGridLayout *pGridlayout;
    QHBoxLayout *pButtonlayout;
    QPushButton *pQuit_button;
    QPushButton *pSave_button;
    QPushButton *pStart_button;
};

#endif // DESIGNWINDOW_H
