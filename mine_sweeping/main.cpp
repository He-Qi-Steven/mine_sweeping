#include "mainwindow.h"
#include "mode_choice.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    a.setQuitOnLastWindowClosed(false);
    mode_choice entry;
    entry.show();

    return a.exec();
}
