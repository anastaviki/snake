#include <QPainter>
#include <QTime>
#include "Snake.h"
#include <QInputDialog>
#include <QTextStream>
#include <sstream>
#include <QMenu>
#include <QMenuBar>
#include <QObject>


QString filename = "..\\Snake\\score.txt";//address to file you also can use absolute
 QFile file(filename);


/*Snake::Snake(QWidget *parent) : QMainWindow(parent) {//set the window
     setStyleSheet("background-color:black; color:white;");

    leftDirection = false;
    rightDirection = true;
    upDirection = false;
    downDirection = false;
    inGame = true;
    inMove = false;
    score=0;
    resize(B_WIDTH, B_HEIGHT);




    loadImages();
    initGame();




}


*/




void Snake::paintEvent(QPaintEvent *e) {

    Q_UNUSED(e);

    doDrawing();
}


void Snake::doDrawing() {





  // QPainter qp(this);
    if (inGame) {

   //     qp.drawImage(apple_x, apple_y, apple);



        for (int z = 0; z < dots; z++) {
            if (z == 0) {
           //     qp.drawImage(x[z], y[z], head);
            } else {
           //     qp.drawImage(x[z], y[z], dot);
            }
        }

    } else {

        //gameOver(qp);
    }
}

 QTextStream out(stdout);
void Snake::gameOver(QPainter &qp) {



    QString tmp = QString::number(score);




    if (file.open(QIODevice::WriteOnly)) {//write score to the file
      QTextStream out(&file);

      out << name+": "+ tmp << endl;



    }
    else {

        qWarning("Could not open file");
      }
file.close();//close
    QString message = text_go;


    QFont font("Courier", 15, QFont::DemiBold);
    QFontMetrics fm(font);
    int textWidth = fm.width(message);

    qp.setPen(QColor(Qt::white));
    qp.setFont(font);
   // int h = height();
  //  int w = width();

  //  qp.translate(QPoint(w/2, h/2));
    qp.drawText(-textWidth/2, 0, message);
}

void Snake::checkApple() {//chech fruit

    if ((x[0] == apple_x) && (y[0] == apple_y)) {

        dots++;
        score=score+10;
        current_num_check=0;
        //locateApple();
    }
}

void Snake::move() {//move snake

    for (int z = dots; z > 0; z--) {
        x[z] = x[(z - 1)];
        y[z] = y[(z - 1)];
    }

    if (leftDirection) {
        x[0] -= DOT_SIZE;
    }

    if (rightDirection) {
        x[0] += DOT_SIZE;
    }

    if (upDirection) {
        y[0] -= DOT_SIZE;
    }

    if (downDirection) {
        y[0] += DOT_SIZE;
    }
}

void Snake::checkCollision() {//check game over
    y0=y[0];
    x0=x[0];

    for (int z = dots; z > 0; z--) {

        if ((z > 4) && (x[0] == x[z]) && (y[0] == y[z])) {
            inGame = false;
        }
    }

    if (y[0] >= B_HEIGHT) {
        inGame = false;
    }

    if (y[0] < 0) {
        inGame = false;
    }

    if (x[0] >= B_WIDTH) {
        inGame = false;
    }

    if (x[0] < 0) {
        inGame = false;
    }





    if(!inGame) {
   //     killTimer(timerId);
    }
}

/*void Snake::locateApple() {//new local fruit

    QTime time = QTime::currentTime();
    qsrand((uint) time.msec());

    int r = qrand() % RAND_POS;
    apple_x = (r * DOT_SIZE);

    r = qrand() % RAND_POS;
    apple_y = (r * DOT_SIZE);

}

*/

void Snake::timerEvent(QTimerEvent *e) {//check by timer

    Q_UNUSED(e);

    if (inGame) {
        current_num_check++;
        if (current_num_check>=num_check){
            // locateApple();
             score=score-10;
             current_num_check=0;
        }

        checkApple();
        checkCollision();
       if (inMove) { move();}
    }

   // repaint();
}

void Snake::keyPressEvent(QKeyEvent *e) {//key event handler

    int key = e->key();

    if ((key == Qt::Key_A) && (!rightDirection)) {
        leftDirection = true;
        upDirection = false;
        downDirection = false;
        inMove = true;
    }

    if ((key == Qt::Key_D) && (!leftDirection)) {
        rightDirection = true;
        upDirection = false;
        downDirection = false;
        inMove = true;
    }

    if ((key == Qt::Key_W) && (!downDirection)) {
        upDirection = true;
        rightDirection = false;
        leftDirection = false;
        inMove = true;
    }

    if ((key == Qt::Key_S) && (!upDirection)) {
        downDirection = true;
        rightDirection = false;
        leftDirection = false;
        inMove = true;
    }

 //   QWidget::keyPressEvent(e);
}
