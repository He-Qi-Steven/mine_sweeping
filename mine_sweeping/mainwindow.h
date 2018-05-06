#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "mine.h"
#include <QTimer>

namespace Ui {
class MainWindow;
}
typedef struct
{
    int raw;
    int column;
    int num_mine;
}strParas;

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

    /* 函数：paintEvent
     * 功能：绘制，Qt虚函数，重写
     * Input: QPaintEvent *
     * Output：NONE
     * */
    void paintEvent(QPaintEvent *);

    /* 函数：mousePressEvent
     * 功能：鼠标点击事件处理，Qt虚函数，重写
     * Input: QMouseEvent *
     * Output：NONE
     * */
    void mousePressEvent(QMouseEvent *event);

    /* 函数：MallocMemForMap_IsPushed
     * 功能：为上层标记地图申请内存，指针为maindow的成员
     * Input: 行、列
     * Output：是否成功
     * */
    bool MallocMemForMap_IsPushed(int in_raw, int in_column);

    /* 函数：InitMap_IsPushed
     * 功能：为上层标记地图初始化，用0、1、2代表未访问过、访问过、插旗标志
     * Input: 行、列
     * Output：是否成功
     * */
    void InitMap_IsPushed();

    /* 函数：GeneratePushedMap
     * 功能：生成上层标记地图，调用MallocMemForMap_IsPushed、InitMap_IsPushed
     * Input: 行、列
     * Output：是否成功
     * */
    bool GeneratePushedMap(int in_raw, int in_column);

    /* 函数：GenerateGlobalMap
     * 功能：生成两级地图
     * Input: 行、列、雷数
     * Output：是否成功
     * */
    bool GenerateGlobalMap(int in_raw, int in_column, int in_mineNum);

    /* 函数：changePosToIndex
     * 功能：将鼠标的点击位置转化为地图坐标
     * Input: x/y像素坐标
     * Output：NONE
     * */
    void changePosToIndex(int *px, int *py);

    void recursiveFreshBlock(int raw_pos, int col_pos);

    void pressLeftRightButtonPorc(int raw_pos, int col_pos);

    void pressLeftButtonProc(int raw_pos, int col_pos);

    void pressRightButtonProc(int raw_pos, int col_pos);

    //检查状态，标志置位处理
    void JudgeIsOver();

    Mine m;

    //地图方格的起始位置偏移
    int map_XOffset;
    int map_YOffset;

    //时间栏的起始位置偏移
    int time_XOffset;
    int time_YOffset;

    //初始状态均置为0
    struct StateFlag
    {
        bool IsOver;//游戏是否结束的状态，如果已经结束，置1，未结束置0。
        bool IsStart;//游戏是否开始的状态，如果已经开始，置1，未开始置0.
        bool result;//游戏结果，胜利置1,失败置0.
    }STATE_FLAG;


private slots:
    void on_actionExit_triggered();

    void on_actionprimary_triggered();

    void on_actionmedium_triggered();

    void on_actionexpert_triggered();

    void on_actionRestart_triggered();

    void on_timeChange();

    void on_actionVersion_triggered();

    void on_actionAuthor_triggered();

    void on_actionuser_defined_triggered();

private:
    //上层地图标记，0---未点击过，1---点击过，2---插上了小旗
    int **map_flag;
    int raw;
    int column;

    //剩余雷的个数
    int mine_Left;

    //计时器
    QTimer *timer;
    int time_cost;


    Ui::MainWindow *ui;
};



#endif // MAINWINDOW_H
