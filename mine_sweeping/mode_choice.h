#ifndef MODE_CHOICE_H
#define MODE_CHOICE_H

#include <QDialog>

namespace Ui {
class mode_choice;
}

class mode_choice : public QDialog
{
    Q_OBJECT

public:
    explicit mode_choice(QWidget *parent = 0);
    ~mode_choice();

private:
    Ui::mode_choice *ui;
};

#endif // MODE_CHOICE_H
