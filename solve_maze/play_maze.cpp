#include "play_maze.h"
#include "ui_play_maze.h"
#include <QDebug>

//using namespace std;

play_maze::play_maze(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::play_maze)
{
    ui->setupUi(this);

    control_direction=2;//往右
    setWindowFlags(windowFlags()&~Qt::WindowMaximizeButtonHint); // 禁止最大化按钮
    setFixedSize(this->width(),this->height());                     // 禁止拖动窗口大小
    //this->move((a.desktop()->width() - this->width()) / 2, (app.desktop()->height() - win.height()) / 2);

    QDesktopWidget *deskdop = QApplication::desktop();
    move((deskdop->width() - this->width())/2, (deskdop->height() - this->height())/2);


    control_LEFT.load(":img/img/control_left.jpg");
    control_RIGHT.load(":img/img/control_right.jpg");
    target.load(":img/img/target.jpg");
    road.load(":img/img/road.jpg");
    wall.load(":img/img/wall.jpg");
    
}

play_maze::~play_maze()
{
    delete ui;
}

void play_maze::on_get_row_valueChanged(int arg1)
{
    pre_maze_row=arg1;
    flag_get_row=true;

    // qDebug()<<"pre_maze_row";
}

void play_maze::on_get_col_valueChanged(int arg1)
{
    pre_maze_col=arg1;
    flag_get_col=true;
}

void play_maze::on_creat_maze_clicked()//创建迷宫
{
    if(flag_click){
        return;
    }
    if(flag_get_row){
        maze_row=pre_maze_row;
    }
    else{
        maze_row=10;
        //qDebug()<<"hhhh";
    }
    if(flag_get_col){
        maze_col=pre_maze_col;
    }
    else{
        maze_col=10;
    }
    //qDebug()<<maze_row<<" "<<maze_col<<endl;
    flag_success=false;

    //获取行列值
    control_X=1;
    control_Y=1;
    target_X=maze_row-3;
    target_Y=maze_col-3;
    //qDebug()<<target_X<<" "<<target_Y<<endl;
    //    maze=new point *[maze_row];
    //    for(int i=0;i<maze_row;i++){
    //        maze[i]=new point[maze_col];
    //    }

    for(int i=0;i<maze_row;i++){
        for(int j=0;j<maze_col;j++){
            maze[i][j].i=i;
            maze[i][j].j=j;
            maze[i][j].state=0;
        }
    }
    int max;
    if(maze_row>=maze_col)
        max=maze_row;
    else
        max=maze_col;

    maze_cell_size=650/max;

    startTimer(5*650/max);
    //qDebug()<<"get row and col"<<endl;
    build_maze_stack.clear();

    int i=3,j=3;
    maze[i][j].state=1;

    point temp;
    temp.i=i;
    temp.j=j;
    temp.state=1;
    bool up=false,down=false,left=false,right=false;

    srand((unsigned)time(NULL));

    while(true){//利用prim算法生成迷宫
        temp.i=i;
        temp.j=j;

        int randnum=rand()%4;

        switch (randnum) {
        case 0: if(!up&&i>2&&maze[i-2][j].state==0){
                build_maze_stack.push(temp);
                maze[i-2][j].state=1;
                maze[i-1][j].state=1;
                i=i-2;
                if(maze[i-1][j].state==0)
                    up=false;
                else
                    up=true;
                if(maze[i+1][j].state==0)
                    down=false;
                else
                    down=true;
                if(maze[i][j-1].state==0)
                    left=false;
                else
                    left=true;
                if(maze[i][j+1].state==0)
                    right=false;
                else
                    right=true;
            }
            else{
                up=true;
            }
            break;
        case 1: if(!down&&i<maze_row-3&&maze[i+2][j].state==0)
            {
                build_maze_stack.push(temp);
                maze[i+2][j].state=1;
                maze[i+1][j].state=1;
                i=i+2;
                if(maze[i-1][j].state==0)
                    up=false;
                else
                    up=true;
                if(maze[i+1][j].state==0)
                    down=false;
                else
                    down=true;
                if(maze[i][j-1].state==0)
                    left=false;
                else
                    left=true;
                if(maze[i][j+1].state==0)
                    right=false;
                else
                    right=true;
            }
            else{
                down=true;
            }
            break;
        case 2: if(!left&&j>2&&maze[i][j-2].state==0)
            {
                build_maze_stack.push(temp);
                maze[i][j-2].state=1;
                maze[i][j-1].state=1;
                j=j-2;
                if(maze[i-1][j].state==0)
                    up=false;
                else
                    up=true;
                if(maze[i+1][j].state==0)
                    down=false;
                else
                    down=true;
                if(maze[i][j-1].state==0)
                    left=false;
                else
                    left=true;
                if(maze[i][j+1].state==0)
                    right=false;
                else
                    right=true;
            }
            else{
                left=true;
            }
            break;
        case 3: if(!right&&j<maze_col-3&&maze[i][j+2].state==0)
            {
                build_maze_stack.push(temp);
                maze[i][j+2].state=1;
                maze[i][j+1].state=1;
                j=j+2;
                if(maze[i-1][j].state==0)
                    up=false;
                else
                    up=true;
                if(maze[i+1][j].state==0)
                    down=false;
                else
                    down=true;
                if(maze[i][j-1].state==0)
                    left=false;
                else
                    left=true;
                if(maze[i][j+1].state==0)
                    right=false;
                else
                    right=true;
            }
            else{
                right=true;
            }
            break;
        }
        if(up&&down&&left&&right){
            if(!build_maze_stack.isEmpty()){
                i=build_maze_stack.top().i;
                j=build_maze_stack.top().j;
                build_maze_stack.pop();
                if(maze[i-1][j].state==0)
                    up=false;
                else
                    up=true;
                if(maze[i+1][j].state==0)
                    down=false;
                else
                    down=true;
                if(maze[i][j-1].state==0)
                    left=false;
                else
                    left=true;
                if(maze[i][j+1].state==0)
                    right=false;
                else
                    right=true;
            }
            else{
                maze[1][1].state=2;
                maze[maze_row-3][maze_col-3].state=3;
                creat_maze=true;
                for(int i=0; i<maze_row; i++)//这一段是防止生成迷宫后依旧显示路线
                    for(int j=0; j<maze_col; j++){
                        path[i][j].state=0;//在这里的状态表示父节点，1,2,3,4分别表示从上下左右发展过来
                        path[i][j].i=i;
                        path[i][j].j=j;
                    }
                //qDebug()<<"creat maze successfully!"<<endl;
                return;
            }
        }
    }

}

void play_maze::on_search_path_clicked()//宽度优先算法
{
    if(!creat_maze){
        return;
    }
    if(flag_click||flag_success){
        return;
    }
    open.clear();

    qDebug()<<"begin find path";
    ftime.start();

    for(int i=0; i<maze_row; i++)
        for(int j=0; j<maze_col; j++){
            path[i][j].state=0;//在这里的状态表示父节点，1,2,3,4分别表示从上下左右发展过来
            path[i][j].i=i;
            path[i][j].j=j;
        }
    //用于记录该点是否搜索的矩阵
    for(int i=0; i<maze_row; i++)
        for(int j=0; j<maze_col; j++){
            if(maze[i][j].state==0)
                graph[i][j]=1;
            else
                graph[i][j]=0;//初始化未被搜索
        }
    QString message;
    int searchnum=0;//搜索节点次数
    point top;
    top.i=control_X;
    top.j=control_Y;
    top.state=0;
    open.push_back(top);//这里的状态什么也不表示

    while(!open.isEmpty()){
        top=open.front();
        //qDebug()<<top.i<<" "<<top.j<<" "<<top.state<<endl;
        open.pop_front();
        if(graph[top.i][top.j]==0){
            searchnum+=1;
            if(maze[top.i][top.j].state==3){
                QString s=QString::number(ftime.elapsed(),10);
                message="花费时间："+s+"ms";
                QMessageBox::information(NULL, " ",message, QMessageBox::Yes, QMessageBox::Yes);
                break;
            }
            //将未访问的子节点放入开节点表
            if((graph[top.i+1][top.j]==0)&&(maze[top.i+1][top.j].state!=0)){
                open.push_back(point(top.i+1,top.j,0));
                path[top.i+1][top.j].state=1;
                //searchnum+=1;
            }
            if((graph[top.i-1][top.j]==0)&&(maze[top.i-1][top.j].state!=0)){
                open.push_back(point(top.i-1,top.j,0));
                path[top.i-1][top.j].state=2;
                //searchnum+=1;
            }
            if((graph[top.i][top.j+1]==0)&&(maze[top.i][top.j+1].state!=0)){
                open.push_back(point(top.i,top.j+1,0));
                path[top.i][top.j+1].state=3;
                //searchnum+=1;
            }
            if((graph[top.i][top.j-1]==0)&&(maze[top.i][top.j-1].state!=0)){
                open.push_back(point(top.i,top.j-1,0));
                path[top.i][top.j-1].state=4;
                //searchnum+=1;
            }
            //将此点标记为访问过
            graph[top.i][top.j]=1;
        }
    }
    qDebug()<<"find the path!"<<endl;

}

void play_maze::on_DFS_clicked()//深度优先搜索
{
    if(!creat_maze){
        return;
    }
    if(flag_click||flag_success){
        return;
    }
    //open.clear();
    DFS_search.clear();

    qDebug()<<"begin find path";

    ftime.start();
    for(int i=0; i<maze_row; i++)
        for(int j=0; j<maze_col; j++){
            path[i][j].state=0;//在这里的状态表示父节点，1,2,3,4分别表示从上下左右发展过来
            path[i][j].i=i;
            path[i][j].j=j;
        }
    //用于记录该点是否搜索的矩阵
    for(int i=0; i<maze_row; i++)
        for(int j=0; j<maze_col; j++){
            if(maze[i][j].state==0)
                graph[i][j]=1;
            else
                graph[i][j]=0;//初始化未被搜索
        }

    QString message;
    int searchnum=0;//搜索节点次数
    point top;
    top.i=control_X;
    top.j=control_Y;
    top.state=0;
    DFS_search.push(top);

    while(!DFS_search.isEmpty()){
        top=DFS_search.top();
        qDebug()<<top.i<<" "<<top.j<<" "<<top.state<<endl;
        //DFS_search.pop();

        if(graph[top.i][top.j]==0){
            searchnum+=1;
            if(maze[top.i][top.j].state==3){
                QString s=QString::number(ftime.elapsed(),10);
                message="花费时间："+s+"ms";
                QMessageBox::information(NULL, " ", message, QMessageBox::Yes, QMessageBox::Yes);
                break;
            }
        }
        //将未访问的子节点放入开节点表
        if((graph[top.i-1][top.j]==0)&&(maze[top.i-1][top.j].state!=0)){
            DFS_search.push(point(top.i-1,top.j,0));
            path[top.i-1][top.j].state=2;
            //searchnum+=1;
        }
        else if((graph[top.i+1][top.j]==0)&&(maze[top.i+1][top.j].state!=0)){
            DFS_search.push(point(top.i+1,top.j,0));
            path[top.i+1][top.j].state=1;
            //searchnum+=1;
        }
        else if((graph[top.i][top.j+1]==0)&&(maze[top.i][top.j+1].state!=0)){
            DFS_search.push(point(top.i,top.j+1,0));
            path[top.i][top.j+1].state=3;
            //searchnum+=1;
        }
        else if((graph[top.i][top.j-1]==0)&&(maze[top.i][top.j-1].state!=0)){
            DFS_search.push_back(point(top.i,top.j-1,0));
            path[top.i][top.j-1].state=4;
            //searchnum+=1;
        }
        else{
            DFS_search.pop();
        }

        //将此点标记为访问过
        graph[top.i][top.j]=1;

    }
    qDebug()<<"find the path!"<<endl;

}

bool cmp(point &a,point &b){//为了实现qsort函数的排序
    return a.state<b.state;
}

void play_maze::on_A_search_clicked()//A*算法
{

    if(flag_click||flag_success){
        return;
    }
    if(!creat_maze){
        return;
    }
    A_search.clear();

    //int md;//曼哈顿距离

    qDebug()<<"begin find path";

    ftime.start();

    for(int i=0; i<maze_row; i++)
        for(int j=0; j<maze_col; j++){
            path[i][j].state=0;//在这里的状态表示父节点，1,2,3,4分别表示从上下左右发展过来
            path[i][j].i=i;
            path[i][j].j=j;
        }
    //用于记录该点是否搜索的矩阵
    for(int i=0; i<maze_row; i++)
        for(int j=0; j<maze_col; j++){
            if(maze[i][j].state==0)
                graph[i][j]=1;
            else
                graph[i][j]=0;//初始化未被搜索
        }

    QString message;
    int searchnum=0;//搜索节点次数
    point top;
    top.i=control_X;
    top.j=control_Y;
    top.state=abs(control_X-target_X)+abs(control_Y-target_Y);

    A_search.push_back(top);//这里的状态什么也不表示
    graph[top.i][top.j]=0;

    while(!A_search.isEmpty()){

        qSort(A_search.begin(),A_search.end(),cmp);



        top=A_search.front();
        //qDebug()<<top.i<<" "<<top.j<<" "<<top.state<<endl;
        A_search.pop_front();


        if(graph[top.i][top.j]==0){
            searchnum+=1;
            if(maze[top.i][top.j].state==3){
                QString s=QString::number(ftime.elapsed(),10);
                message="花费时间："+s+"ms";
                QMessageBox::information(NULL, " ", message, QMessageBox::Yes, QMessageBox::Yes);
                break;
            }
            //将此点标记为访问过
            //并将真实路径代价计算进去,用graph存储
            switch (path[top.i][top.j].state) {
            case 1:
                graph[top.i][top.j]=graph[top.i-1][top.j]+1;
                break;
            case 2:
                graph[top.i][top.j]=graph[top.i+1][top.j]+1;
                break;
            case 3:
                graph[top.i][top.j]=graph[top.i][top.j-1]+1;
                break;
            case 4:
                graph[top.i][top.j]=graph[top.i][top.j+1]+1;
                break;
            default:
                graph[top.i][top.j]=1;
                break;
            }
            //将未访问的子节点放入开节点表
            if((graph[top.i+1][top.j]==0)&&(maze[top.i+1][top.j].state!=0)){
                A_search.push_back(point(top.i+1,top.j,(graph[top.i][top.j]+1+abs(top.i+1-target_X)+abs(top.j-target_Y))));
                path[top.i+1][top.j].state=1;

                //graph[top.i+1][top.j]=graph[top.i][top.j]+1;
            }
            if((graph[top.i-1][top.j]==0)&&(maze[top.i-1][top.j].state!=0)){
                A_search.push_back(point(top.i-1,top.j,(graph[top.i][top.j]+1+abs(top.i-1-target_X)+abs(top.j-target_Y))));
                path[top.i-1][top.j].state=2;

                //graph[top.i-1][top.j]=graph[top.i][top.j]+1;
            }
            if((graph[top.i][top.j+1]==0)&&(maze[top.i][top.j+1].state!=0)){
                A_search.push_back(point(top.i,top.j+1,(graph[top.i][top.j]+1+abs(top.i-target_X)+abs(top.j+1-target_Y))));
                path[top.i][top.j+1].state=3;
                //searchnum+=1;
                //graph[top.i][top.j+1]=graph[top.i][top.j]+1;
            }
            if((graph[top.i][top.j-1]==0)&&(maze[top.i][top.j-1].state!=0)){
                A_search.push_back(point(top.i,top.j-1,(graph[top.i][top.j]+1+abs(top.i-target_X)+abs(top.j-1-target_Y))));
                path[top.i][top.j-1].state=4;
                //searchnum+=1;
                //graph[top.i][top.j-1]=graph[top.i][top.j]+1;
            }


        }
    }
    qDebug()<<"find the path!"<<endl;



}

void play_maze::on_greedy_clicked()//贪婪算法
{
    if(flag_click||flag_success){
        return;
    }
    if(!creat_maze){
        return;
    }
    A_search.clear();

    //int md;//曼哈顿距离

    qDebug()<<"begin find path";
    ftime.start();
    for(int i=0; i<maze_row; i++)
        for(int j=0; j<maze_col; j++){
            path[i][j].state=0;//在这里的状态表示父节点，1,2,3,4分别表示从上下左右发展过来
            path[i][j].i=i;
            path[i][j].j=j;
        }
    //用于记录该点是否搜索的矩阵
    for(int i=0; i<maze_row; i++)
        for(int j=0; j<maze_col; j++){
            if(maze[i][j].state==0)
                graph[i][j]=1;
            else
                graph[i][j]=0;//初始化未被搜索
        }

    QString message;
    int searchnum=0;//搜索节点次数
    point top;
    top.i=control_X;
    top.j=control_Y;
    top.state=abs(control_X-target_X)+abs(control_Y-target_Y);

    A_search.push_back(top);//这里的状态什么也不表示

    while(!A_search.isEmpty()){

        qSort(A_search.begin(),A_search.end(),cmp);



        top=A_search.front();
        //qDebug()<<top.i<<" "<<top.j<<" "<<top.state<<endl;
        A_search.pop_front();


        if(graph[top.i][top.j]==0){
            searchnum+=1;
            if(maze[top.i][top.j].state==3){
                QString s=QString::number(ftime.elapsed(),10);
                message="花费时间："+s+"ms";
                QMessageBox::information(NULL, " ", message, QMessageBox::Yes, QMessageBox::Yes);
                break;
            }
            //将未访问的子节点放入开节点表
            if((graph[top.i+1][top.j]==0)&&(maze[top.i+1][top.j].state!=0)){
                A_search.push_back(point(top.i+1,top.j,abs(top.i+1-target_X)+abs(top.j-target_Y)));
                path[top.i+1][top.j].state=1;
                //searchnum+=1;
            }
            if((graph[top.i-1][top.j]==0)&&(maze[top.i-1][top.j].state!=0)){
                A_search.push_back(point(top.i-1,top.j,abs(top.i-1-target_X)+abs(top.j-target_Y)));
                path[top.i-1][top.j].state=2;
                //searchnum+=1;
            }
            if((graph[top.i][top.j+1]==0)&&(maze[top.i][top.j+1].state!=0)){
                A_search.push_back(point(top.i,top.j+1,abs(top.i-target_X)+abs(top.j+1-target_Y)));
                path[top.i][top.j+1].state=3;
                //searchnum+=1;
            }
            if((graph[top.i][top.j-1]==0)&&(maze[top.i][top.j-1].state!=0)){
                A_search.push_back(point(top.i,top.j-1,abs(top.i-target_X)+abs(top.j-1-target_Y)));
                path[top.i][top.j-1].state=4;
                //searchnum+=1;
            }
            //将此点标记为访问过
            graph[top.i][top.j]=1;
        }
    }
    qDebug()<<"find the path!"<<endl;
}

void play_maze::keyPressEvent(QKeyEvent *event){//控制移动
    if(flag_click)
        return;
    switch (event->key()) {
    case Qt::Key_W: if((control_Y>0)&&((maze[control_X][control_Y-1].state==1)||(maze[control_X][control_Y-1].state==3))){
            path[control_X][control_Y-1].state=0;//这一段是防止到达终点依旧显示路线
            maze[control_X][control_Y-1].state=2;
            maze[control_X][control_Y].state=1;
            control_Y-=1;
        }
        break;
    case Qt::Key_S: if((control_Y<maze_col-1)&&((maze[control_X][control_Y+1].state==1)||(maze[control_X][control_Y+1].state==3))){
            path[control_X][control_Y+1].state=0;
            maze[control_X][control_Y+1].state=2;
            maze[control_X][control_Y].state=1;
            control_Y+=1;
        }
        break;
    case Qt::Key_A: if((control_X>0)&&((maze[control_X-1][control_Y].state==1)||(maze[control_X-1][control_Y].state==3))){
            path[control_X-1][control_Y].state=0;
            maze[control_X-1][control_Y].state=2;
            maze[control_X][control_Y].state=1;
            control_X-=1;
            control_direction=1;
        }
        break;
    case Qt::Key_D: if((control_X<maze_row-1)&&((maze[control_X+1][control_Y].state==1)||(maze[control_X+1][control_Y].state==3))){
            path[control_X+1][control_Y].state=0;
            maze[control_X+1][control_Y].state=2;
            maze[control_X][control_Y].state=1;
            control_X+=1;
            control_direction=2;
        }
        break;
        //目标移动
    case Qt::Key_I: if((target_Y>0)&&((maze[target_X][target_Y-1].state==1)&&((maze[target_X][target_Y].state!=2)))){
            //path[target_X][target_Y-1].state=0;//这一段是防止到达终点依旧显示路线
            maze[target_X][target_Y-1].state=3;
            maze[target_X][target_Y].state=1;
            target_Y-=1;
        }
        break;
    case Qt::Key_K: if((target_Y<maze_col-1)&&((maze[target_X][target_Y+1].state==1))&&((maze[target_X][target_Y].state!=2))){
            //path[target_X][target_Y+1].state=0;
            maze[target_X][target_Y+1].state=3;
            maze[target_X][target_Y].state=1;
            target_Y+=1;
        }
        break;
    case Qt::Key_J: if((target_X>0)&&((maze[target_X-1][target_Y].state==1))&&((maze[target_X][target_Y].state!=2))){
            //path[target_X-1][target_Y].state=0;
            maze[target_X-1][target_Y].state=3;
            maze[target_X][target_Y].state=1;
            target_X-=1;
            //target_direction=1;
        }
        break;
    case Qt::Key_L: if((target_X<maze_row-1)&&((maze[target_X+1][target_Y].state==1))&&((maze[target_X][target_Y].state!=2))){
            //path[target_X+1][target_Y].state=0;
            maze[target_X+1][target_Y].state=3;
            maze[target_X][target_Y].state=1;
            target_X+=1;
            //target_direction=2;
        }
        break;
    }
    //maze[target_X][target_Y].state=3;
    if((control_X==target_X)&&(control_Y==target_Y)&&creat_maze){
        maze[target_X][target_Y].state=2;
        //        for(int i=0; i<maze_row; i++)//这一段是防止到达终点依旧显示路线
        //            for(int j=0; j<maze_col; j++){
        //                path[i][j].state=0;//在这里的状态表示父节点，1,2,3,4分别表示从上下左右发展过来
        //                path[i][j].i=i;
        //                path[i][j].j=j;
        //            }
        target_X=0;
        target_Y=0;
        maze[target_X][target_Y].state=0;
        flag_success=true;
        QMessageBox::information(NULL, "恭喜您", "僵尸吃掉了您的脑子！", QMessageBox::Yes, QMessageBox::Yes);
    }
}

void play_maze::paintEvent(QPaintEvent *){//显示图像
    QPainter painter(this);
        QPen Pen(Qt::blue);

        //qDebug()<<"ahah"<<maze_row<<" "<<maze_col<<endl;

        for(int i=0;i<maze_row;i++){
            for(int j=0;j<maze_col;j++){

                if(maze[i][j].state==0){
                    painter.drawPixmap(maze_cell_size*i+5,maze_cell_size*j+5,maze_cell_size,maze_cell_size,wall);
                }
                else if(maze[i][j].state==1){
                    painter.drawPixmap(maze_cell_size*i+5,maze_cell_size*j+5,maze_cell_size,maze_cell_size,road);
                }
                else if(maze[i][j].state==2){
                    if(control_direction==1){
                        painter.drawPixmap(maze_cell_size*i+5,maze_cell_size*j+5,maze_cell_size,maze_cell_size,control_LEFT);
                    }
                    else{
                        painter.drawPixmap(maze_cell_size*i+5,maze_cell_size*j+5,maze_cell_size,maze_cell_size,control_RIGHT);
                    }
                }
                else if(maze[i][j].state==3){
                    painter.drawPixmap(maze_cell_size*i+5,maze_cell_size*j+5,maze_cell_size,maze_cell_size,target);
                }
                else{}
            }
        }

        if(!flag_click){
            painter.setPen(Pen);
            point draw_point=path[target_X][target_Y];
            point pre_draw_point;

            while(draw_point.state!=0){
                if(draw_point.i==control_X&&draw_point.j==control_Y)
                    break;
                if(draw_point.state==1)//上
                    pre_draw_point=path[draw_point.i-1][draw_point.j];
                if(draw_point.state==2)//下
                    pre_draw_point=path[draw_point.i+1][draw_point.j];
                if(draw_point.state==3)//左
                    pre_draw_point=path[draw_point.i][draw_point.j-1];
                if(draw_point.state==4)//右
                    pre_draw_point=path[draw_point.i][draw_point.j+1];

                painter.drawLine(QPointF(maze_cell_size*draw_point.i+(maze_cell_size/2)+5,maze_cell_size*draw_point.j+(maze_cell_size/2)+5),QPointF(maze_cell_size*pre_draw_point.i+(maze_cell_size/2)+5,maze_cell_size*pre_draw_point.j+(maze_cell_size/2)+5));

                draw_point=pre_draw_point;

            }

        }

        update();
}

void play_maze::mousePressEvent(QMouseEvent *mouse){//自动寻路
    if(!creat_maze){
        return;
    }
    int x=mouse->x()-5;
    int y=mouse->y()-5;
    target_X2=x/maze_cell_size;
    target_Y2=y/maze_cell_size;
    //qDebug()<<maze[target_X2][target_Y2].state<<" aaaa";
    if(maze[target_X2][target_Y2].state==0||maze[target_X2][target_Y2].state==3){
        flag_click=false;
        return;
    }
    else{
        flag_click=true;
    }

    //下面开始找路
    if(creat_maze==false){
        return;
    }
    auto_path2.clear();
    auto_path.clear();
    //int md;//曼哈顿距离

    qDebug()<<"begin find path";

    for(int i=0; i<maze_row; i++)
        for(int j=0; j<maze_col; j++){
            path[i][j].state=0;//在这里的状态表示父节点，1,2,3,4分别表示从上下左右发展过来
            path[i][j].i=i;
            path[i][j].j=j;
        }
    //用于记录该点是否搜索的矩阵
    for(int i=0; i<maze_row; i++)
        for(int j=0; j<maze_col; j++){
            if(maze[i][j].state==0)
                graph[i][j]=1;
            else
                graph[i][j]=0;//初始化未被搜索
        }


    point top;
    top.i=control_X;
    top.j=control_Y;
    top.state=abs(control_X-target_X2)+abs(control_Y-target_Y2);

    auto_path.push_back(top);//这里的状态什么也不表示

    while(!auto_path.isEmpty()){

        qSort(auto_path.begin(),auto_path.end(),cmp);



        top=auto_path.front();
        //qDebug()<<top.i<<" "<<top.j<<" "<<top.state<<endl;
        auto_path.pop_front();


        if(graph[top.i][top.j]==0){
            if(top.i==target_X2&&top.j==target_Y2){
                //QMessageBox::information(NULL, " ", "搜索成功", QMessageBox::Yes, QMessageBox::Yes);
                break;
            }
            //将未访问的子节点放入开节点表
            if((graph[top.i+1][top.j]==0)&&(maze[top.i+1][top.j].state!=0)){
                auto_path.push_back(point(top.i+1,top.j,abs(top.i+1-target_X2)+abs(top.j-target_Y2)));
                path[top.i+1][top.j].state=1;
            }
            if((graph[top.i-1][top.j]==0)&&(maze[top.i-1][top.j].state!=0)){
                auto_path.push_back(point(top.i-1,top.j,abs(top.i-1-target_X2)+abs(top.j-target_Y2)));
                path[top.i-1][top.j].state=2;
            }
            if((graph[top.i][top.j+1]==0)&&(maze[top.i][top.j+1].state!=0)){
                auto_path.push_back(point(top.i,top.j+1,abs(top.i-target_X2)+abs(top.j+1-target_Y2)));
                path[top.i][top.j+1].state=3;
            }
            if((graph[top.i][top.j-1]==0)&&(maze[top.i][top.j-1].state!=0)){
                auto_path.push_back(point(top.i,top.j-1,abs(top.i-target_X)+abs(top.j-1-target_Y2)));
                path[top.i][top.j-1].state=4;
            }
            //将此点标记为访问过
            graph[top.i][top.j]=1;
        }
    }
    qDebug()<<"find the path!"<<endl;

    //下面进行反序
    point mypoint;
    point pre_mypoint;
    mypoint=path[target_X2][target_Y2];

    while(mypoint.state!=0){

        if(mypoint.i==control_X&&mypoint.j==control_Y)
            break;
        if(mypoint.state==1)//上
            pre_mypoint=path[mypoint.i-1][mypoint.j];
        if(mypoint.state==2)//下
            pre_mypoint=path[mypoint.i+1][mypoint.j];
        if(mypoint.state==3)//左
            pre_mypoint=path[mypoint.i][mypoint.j-1];
        if(mypoint.state==4)//右
            pre_mypoint=path[mypoint.i][mypoint.j+1];

        auto_path2.push(mypoint);
        mypoint=pre_mypoint;
    }


    for(int i=0; i<maze_row; i++)
        for(int j=0; j<maze_col; j++){
            path[i][j].state=0;//在这里的状态表示父节点，1,2,3,4分别表示从上下左右发展过来
            path[i][j].i=i;
            path[i][j].j=j;
        }



}

void play_maze::timerEvent(QTimerEvent *){//自动寻路的显示



    if(!auto_path2.isEmpty()){
        mypoint=auto_path2.top();
        auto_path2.pop();

        if(maze[mypoint.i][mypoint.j].state==3){
            flag_target=true;
            flag_target2=false;//用两个flag的二进制编码考虑不同的状态
        }

        if(flag_target&&flag_target2){
            maze[mypoint.i][mypoint.j].state=2;
            maze[control_X][control_Y].state=3;
            flag_target=false;
            flag_target2=false;
        }
        else if(flag_target&&!flag_target2){
            maze[mypoint.i][mypoint.j].state=2;
            maze[control_X][control_Y].state=1;
            flag_target=true;
            flag_target2=true;
        }
        else{
            maze[mypoint.i][mypoint.j].state=2;
            maze[control_X][control_Y].state=1;
            flag_target=false;
            flag_target2=false;
        }


        control_X=mypoint.i;
        control_Y=mypoint.j;
    }
    else{
        flag_click=false;
    }



}
