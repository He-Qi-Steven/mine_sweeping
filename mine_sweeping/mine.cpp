#include "mine.h"
#include "stdlib.h"
#include <time.h>
#include <iostream>

using namespace std;

Mine::Mine()
{
    map = NULL;
}


bool Mine::GenerateMap(int in_raw, int in_column, int in_mineNum)
{
    if(false == MallocMemForMap(in_raw, in_column, in_mineNum))
    {
        cout << "error: malloc memory failed!" << endl;
        return false;
    }

    InitMap();

    if(false == InitMap())
    {
        cout << "error: init map failed!" << endl;
        return false;
    }

    return true;
}



bool Mine::MallocMemForMap(int in_raw, int in_column, int in_mineNum)
{

    //非法入参
    if(0 == in_raw || 0 == in_column || 0 == in_mineNum || in_mineNum > in_raw * in_column)
    {
        cout << "error: para error!" << endl;
        return false;
    }
    if(NULL != map)
    {
        for(int i = 0; i < raw; i ++)
        {
            delete map[i];
        }
        delete map;
    }
    map = NULL;

    raw = in_raw;
    column = in_column;
    mineNum = in_mineNum;

    map = new unsigned char*[raw];
    for(unsigned char j = 0; j < raw; j ++)
    {
        map[j] = new unsigned char[column];
    }
    return true;
}



bool Mine::InitMap()
{
    int xpos, ypos, mineLeft = mineNum;
    int xs, xe, ys, ye;//填值时使用的上下左右边界值

    if(NULL == map)
    {
        cout << "error: null ptr!" << endl;
        return false;
    }
    //初始化内存，全部填0
    for(int i = 0; i < raw; i ++)
    {
        for(int j = 0; j < column; j ++)
        {
            map[i][j] = 0;
        }
    }

    //埋雷---采用随机生成雷坐标的方式,雷使用符号'*'的ASCII
    srand(time(NULL));//以当前时间为随机种子，保证随机性
    while(0 != mineLeft)
    {
        xpos = rand() % raw;
        ypos = rand() % column;
        if(0 == map[xpos][ypos])
        {
            map[xpos][ypos] = '*';
            mineLeft --;
        }
        continue;
    }

    //根据雷的分布填充其他方格数值
    for(int i = 0; i < raw; i ++)
    {
        for(int j = 0; j < column; j ++)
        {
            if('*' == map[i][j])
            {
                //设定雷周围可遍历方格的区间
                xs = (i - 1 >= 0) ? (i - 1) : i;
                xe = (i + 1 < raw) ? (i + 1) : i;
                ys = (j - 1 >= 0) ? (j - 1) : j;
                ye = (j + 1 < column) ? (j + 1) : j;

                for(xpos = xs; xpos <= xe ; xpos ++)
                {
                    for(int ypos = ys; ypos <= ye; ypos ++)
                    {
                        if('*' == map[xpos][ypos])
                        {
                            continue;
                        }
                        map[xpos][ypos] ++;
                    }
                }
            }
        }
    }
    return true;
}

void Mine::PrintMap()
{
    for(int i = 0; i < raw; i ++)
    {
        for(int j = 0; j < column; j ++)
        {
            cout << (int)map[i][j] << "\t";
        }
        cout << endl;
    }
}

