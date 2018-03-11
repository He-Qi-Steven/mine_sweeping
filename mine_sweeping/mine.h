#ifndef MINE_H
#define MINE_H

/*功能：接受来自Mainwindow的输入，并响应
 * 1.接收地图参数，生成地图
 * 2.接收点击事件，实时响应
 * */
class Mine
{
public:
    Mine();

    /* 函数：GenerateMap
     * 功能：根据传入参数，生成二维数组地图
     * Input:int raw, 行数
     *       int column, 列数
     *       int mineNum, 雷数
     * Output：bool ret，返回是否成功生成地图
     * */
    bool GenerateMap(int in_raw, int in_column, int in_mineNum);

private:
    unsigned char **map;
    int raw;//行数
    int column;//列数
    int mineNum;//雷数

    /* 函数：MallocMemForMap
     * 功能：为二维指针申请内存
     * Input:int raw, 行数
     *       int column, 列数
     *       int mineNum, 雷数
     * Output：bool ret，返回是否成功申请内存
     * */
    bool MallocMemForMap(int in_raw, int in_column, int in_mineNum);

    /* 函数：InitMap
     * 功能：在地图中埋雷，为每个方格填值
     * Input: NONE
     * Output：bool ret，返回是否完成埋雷与填值
     * */
    bool InitMap();

    /* 函数：PrintMap
     * 功能：打印地图
     * Input: NONE
     * Output：NONE
     * */
    void PrintMap();
};


#endif // MINE_H
