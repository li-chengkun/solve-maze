#ifndef PLAY_MAZE_H
#define PLAY_MAZE_H

#include <QDialog>
#include "qpainter.h"
#include <QKeyEvent>
#include <QWidget>
#include <QQueue>
#include <QVector>
#include <QMessageBox>
#include <QStack>
#include <stdlib.h>
#include <time.h>
#include "point.h"
#include <math.h>
#include <QtAlgorithms>
#include <QTimer>
#include <QDesktopWidget>
#include <QTime>

//using namespace std;

namespace Ui {
class play_maze;
}

class play_maze : public QWidget
{
    Q_OBJECT

public:
    explicit play_maze(QWidget *parent = nullptr);
    ~play_maze();

private slots:
    void on_get_row_valueChanged(int arg1);
    
    void on_get_col_valueChanged(int arg1);
    
    void on_creat_maze_clicked();
    
    void on_search_path_clicked();
    
    void on_DFS_clicked();

    void on_A_search_clicked();

    void on_A_search_2_clicked();

    void on_greedy_clicked();

private:
    Ui::play_maze *ui;

    int maze_row;
    int maze_col;
    int pre_maze_row;
    int pre_maze_col;
    bool flag_get_row=false;
    bool flag_get_col=false;
    bool flag_click=false;//判断是否自动寻路
    bool flag_target=false;//自动寻路若经过target，就会覆盖，暂时不会显示，所以通过这个flag解决这个问题
    bool flag_target2=false;//感觉一个解决不了问题
    bool flag_success=false;//完成后不进行搜索

    int W;
    int H;//界面宽度和高度
    int maze_cell_size;//每个块的大小

    point maze[200][200];//迷宫
    bool creat_maze=false;

    int control_X;
    int control_Y;//控制点的位置
    int target_X;
    int target_Y;//目标点位置
    int target_X2;
    int target_Y2;//鼠标点击位置坐标

    int control_direction;//控制点行走的方向,1,2分别代表左右
    int pre_control_direction;
    
    QTime ftime;//计算搜索时间

    QPixmap control_RIGHT;
    QPixmap control_LEFT;
    QPixmap target;//目标图片
    QPixmap wall;//墙
    QPixmap road;//路

    int graph[200][200];//用于标记是否被搜索过

    QQueue<point> open;//开节点表,用于宽度优先搜索
    //QQueue<point> search_path;//搜索路径队列，宽搜
    QStack<point> DFS_search;//用于深度优先搜索的栈
    QVector<point> A_search;//用于A*算法搜索和贪婪算法的队列。
    QVector<point> auto_path;//自动寻路用
    QStack<point> auto_path2;//因为寻路只记录了儿子节点，需要一个栈进行反序
    //用于自动寻路
    point mypoint;
    //point pre_mypoint;

//    int X;
//    int Y;

    QStack<point> build_maze_stack;//创建迷宫的栈
    point path[200][200];//用于搜索路径的矩阵


    void keyPressEvent(QKeyEvent *);
    void paintEvent(QPaintEvent *);    
    void mousePressEvent(QMouseEvent *);
    void timerEvent(QTimerEvent *);

};

#endif // PLAY_MAZE_H
