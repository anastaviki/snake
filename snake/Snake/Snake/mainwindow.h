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
extern QLabel *score_title, *score_label, *win_label, *lose_label;
extern QString eat_str;

extern QVector<QGraphicsPixmapItem*> pball;
extern bool islose, iswin;

namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    static const int ALL_DOTS = 900;
    explicit MainWindow(QWidget *parent = nullptr);
    void set_board();
    int x_snake[ALL_DOTS];
    int y_snake[ALL_DOTS];
    int  walls [42][60];


bool ok;
 QString name = "";
  QString map_n = "1";
   QString name_map = "";
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

private:
    Ui::MainWindow *ui;  
    QTimer *timer, *flash;
    bool flashtik;

    void loadImages();

    void locateApple();
protected:
     void keyPressEvent(QKeyEvent *);
      void timerEvent(QTimerEvent *);
       void move();
       void checkApple();
       void checkCollision();
          void gameOver();
    int num_check;
    int current_num_check=0;
    int x[ALL_DOTS];
    int y[ALL_DOTS];

int win_pos=0;
    int temp1;
    int temp2;
int score;
    int value;
    int x0;
    int y0;
     int dots;
     int temp_snake;
     int count=0;
     int apple_x;
     int apple_y;
    int  apple_block_x;
    int  apple_block_y;
  int timerId;
  bool leftDirection;
  bool rightDirection;
  bool upDirection;
  bool downDirection;
  bool inGame;
  bool inMove;
  QString str1;
  QString str2;
  QString str3;
  QString str4;
  QString str5;
  QString str6;
  QString str7;
  QString str8;
  QString str9;
  QString str10;



};


#endif // MAINWINDOW_H
