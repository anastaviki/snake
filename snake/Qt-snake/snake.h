#pragma once

#include <QWidget>
#include <QKeyEvent>
#include <QMainWindow>
#include <QApplication>
#include <QObject>
#include <QGraphicsItem>
class Snake : public QGraphicsPixmapItem {

  public:
      Snake(QWidget *parent = 0);
public slots:
    void setValue(int value);



  protected:
      void paintEvent(QPaintEvent *);
      void timerEvent(QTimerEvent *);
      void keyPressEvent(QKeyEvent *);
      void drawLines(QPainter *qp);




      static const int B_WIDTH = 900;//field
      static const int B_HEIGHT = 900;
      static const int DOT_SIZE = 10; //change speed of dot
      static const int ALL_DOTS = 900;
      static const int RAND_POS = 29;
      static const int DELAY = 140;
      static const int delay_before_destroy = 11400;

      QString name = "";
      QString text_go = "Game over";
      int num_check;
      int current_num_check=0;
      int timerId;
      int dots;
      int score;
      int apple_x;
      int apple_y;
      int n_map = 2;//number of map y can create new maps by drowing new walls and creating collision maps

      int x[ALL_DOTS];
      int y[ALL_DOTS];
      int value;
      int x0;
      int y0;
      bool leftDirection;
      bool rightDirection;
      bool upDirection;
      bool downDirection;
      bool inGame;
      bool inMove;


      void checkApple();
      void checkCollision();
      void move();
      void doDrawing();
      void doMap(int map);
      void collision_map(int map,int y0,int x0);
      void gameOver(QPainter &);

};
