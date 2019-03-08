#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setWindowFlags(windowFlags()&~Qt::WindowMaximizeButtonHint); // 禁止最大化按钮
    setFixedSize(this->width(),this->height());                     // 禁止拖动窗口大小
//    QString PATH=QApplication::applicationDirPath();
//    mymainwindow.load(PATH+"/img/mainwindow.jpg");
    //mymainwindow.load("../solve_maze/img/mainwindow.jpg");
    mymainwindow.load(":img/img/mainwindow.jpg");
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{

    this->hide();
    //mymaze.resize(800,700);
    mymaze.show();
}

void MainWindow::paintEvent(QPaintEvent *){

    QPainter painter(this);
    painter.drawPixmap(0,0,500,325,mymainwindow);

}
