#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "mine.h"

namespace Ui {
class MainWindow;
}

/*功能：与用户直接交互
 * 1.等级切换外部接口
 * 2.重新开始外部接口
 * 3.纪录功能（待开发）
 * 4.联机对战功能（待细化）
 * */
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    /* 默认三个level的地图参数
     * -----------------------------------------
     * |     level    | raw | column | mineNum |
     * -----------------------------------------
     * |   low-level  |  9  |    9   |    10   |
     * -----------------------------------------
     * | intermediate | 16  |   16   |    40   |
     * -----------------------------------------
     * |   advanced   | 16  |   30   |   100   |
     * -----------------------------------------
     * */
    unsigned int defaultMap[3][3] = {{9,9,10},
                                     {16,16,40},
                                     {16,30,100}};

    /* 函数：ChangeLevel
     * 功能：等级切换外部接口，根据传等级参数给Mine类用于生成地图
     * Input:int raw, 行数
     *       int column, 列数
     *       int mineNum, 雷数
     * Output：bool ret，返回等级是否切换成功
     * */
    bool ChangeLevel(int raw, int column, int mineNum);

    /* 函数：Restart
     * 功能：重新开始外部接口
     * Input: NONE
     * Output：bool ret，返回是否成功restart
     * */
    bool Restart();
    Mine m;

private:
    Ui::MainWindow *ui;
};



#endif // MAINWINDOW_H
