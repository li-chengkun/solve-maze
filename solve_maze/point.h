#ifndef POINT_H
#define POINT_H

//迷宫的每个点
class point{
public:
    int i;
    int j;//行列坐标
    int state;//对应不同状态：不可行走，可行走,人在上面，终点或者以后可以扩充的状态
    //不可行走-0；可行走-1；人-2；终点-3
    point();
    ~point();
    point(int i,int j,int state);
};

#endif // POINT_H
