#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "play_maze.h"
#include "qpainter.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_pushButton_clicked();

private:
    Ui::MainWindow *ui;
    play_maze mymaze;

    QPixmap mymainwindow;
    void paintEvent(QPaintEvent *);

};

#endif // MAINWINDOW_H
