#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QMainWindow>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QGraphicsItem>
#include <QPixmap>
#include <QKeyEvent>
#include <QString>
#include <QObject>
#include <QCoreApplication>
#include <QDebug>
#include <QTimer>
#include <QLabel>
#include "QThread"


#define _width 10       //width of items
#define _xborder 40     //(x of qgraphicsview) - 20
#define _yborder 40     //(y of qgraphicsview) - 20
#define _slptime 5000   //moving sleep time

/*item move direction*/
#define _up 0
#define _down 1
#define _left 2
#define _right 3
#define _stop 4





/*declare shared resource*/
extern char map[42][60]; //20,29
extern QGraphicsPixmapItem *block[42][60];
extern QGraphicsScene *scene;
extern int dot_num, eat_sum, totalscore, gatex, gatey, pball_num;
extern QLabel *score_title, *score, *win_label, *lose_label;
extern QString eat_str;

extern QVector<QGraphicsPixmapItem*> pball;
extern bool islose, iswin;

namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    void set_board();

bool ok;
 QString name = "";
    ~MainWindow() override;

private:
    QImage dot;
    QImage head;
    QImage apple;
    static const int DELAY = 140;
static const int delay_before_destroy = 11400;
static const int B_WIDTH = 900;//field
static const int B_HEIGHT = 900;
static const int RAND_POS = 29;
static const int DOT_SIZE = 10; //change speed of dot
static const int ALL_DOTS = 900;
private:
    Ui::MainWindow *ui;  
    QTimer *timer, *flash;
    bool flashtik;

    void loadImages();
    void initGame(int x_h,int y_h);
    void locateApple();
protected:
    int num_check;
    int current_num_check=0;
    int x[ALL_DOTS];
    int y[ALL_DOTS];
    int value;
    int x0;
    int y0;
     int dots;
     int apple_x;
     int apple_y;
  int timerId;

};


#endif // MAINWINDOW_H
