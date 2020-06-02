#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QInputDialog>
#include <QTime>
#include <QProcess>
#include "ui_mainwindow.h"
#include "mainwindow.h"


#include <QFile>
#include<QRandomGenerator>
#include<QDateTime>

/*create shared resource*/
char map[42][60];
QGraphicsPixmapItem *block[42][60];
QGraphicsScene *scene;
int dot_num, eat_sum, totalscore, gatex, gatey;
QLabel *score_title, *score_label, *win_label, *lose_label, *plase_label, *plase_label_n,*restart;
QString eat_str;
QVector<QGraphicsPixmapItem*> pball;
bool islose=false, iswin=false;


MainWindow::MainWindow(QWidget *parent) ://draw main window
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setWindowTitle(tr("Snake"));
    ui->graphicsView->setStyleSheet("QGraphicsView {border: none;}");
    ui->graphicsView->setBackgroundBrush(Qt::black);
    scene = new QGraphicsScene(50, 50, ui->graphicsView->width() - 2, ui->graphicsView->height() - 2);
    ui->graphicsView->setFocusPolicy(Qt::NoFocus);
    ui->graphicsView->setScene(scene);

    timer = new QTimer(this);
    flash = new QTimer(this);
    timer->start(6);
    flash->start(200);
    QString text = QInputDialog::getText(this, tr("Name"),
                            tr("Name"), QLineEdit::Normal,
                            tr("Your name"), &ok);

    if (ok && !text.isEmpty())
         name=text;
    QString text2 = QInputDialog::getText(this, tr("Map"),
                            tr("Map number from 1 to 5, default:1"), QLineEdit::Normal,
                            tr("Map number"), &ok);

    if (ok && !text2.isEmpty())
         map_n=text2;

    if ((map_n=="1")||(map_n=="2")||(map_n=="3")||(map_n=="4")||(map_n=="5")){
        set_board();
    }
    else {(map_n="1");
    set_board();}

}


void MainWindow::set_board() {//read map from file
    leftDirection = false;
    rightDirection = false;
    upDirection = false;
    downDirection = false;
    inGame = true;
    inMove = false;
    score=0;
    qsrand(QDateTime::currentDateTime().toTime_t());
    int ghost_ind=0;
    memset(map,'0',sizeof(map));
    dot_num = eat_sum = 0;
    totalscore = flashtik=0;
    QPixmap blockpix(":/rsc/block.png");
    QPixmap dotpix(":/rsc/dot.png");
    QPixmap snake_body(":/rsc/dot.png");
    name_map=":/rsc/map_"+map_n+".txt";
    QFile mapfile(name_map);

    QString mapstr;
    QByteArray mapline;
    dots = 2;//num of start dots
    temp_snake=dots;

    mapfile.open(QIODevice::ReadOnly|QIODevice::Text);
    for(int i=1;i<41;++i) {
        QByteArray mapline = mapfile.readLine();
        mapstr = QString(mapline);
        for(int j=1;j<59;++j) {
            map[i][j] = mapline.at(j-1);
            walls[i][j]=0;

            switch(map[i][j]) {
            case '0':


if (temp_snake<ALL_DOTS){
                y[temp_snake] = j;
                x[temp_snake] = i;
                y_snake[temp_snake]=j;
                x_snake[temp_snake]=i;
temp_snake=temp_snake+1;
                block[i][j] = new QGraphicsPixmapItem(snake_body);
                scene->addItem(block[i][j]);


}

                break;
            case '1':
                block[i][j] = new QGraphicsPixmapItem(blockpix);
                scene->addItem(block[i][j]);
                block[i][j]->setPos(_xborder+j*_width, _yborder+i*_width);
 walls[i][j]=1;

                break;

            case '2':
                num_check=delay_before_destroy/DELAY;



                for (int z = 0; z < dots; z++) {

                        y[z] = i;
                        x[z] = j+z;
                        y_snake[z]=i;
                        x_snake[z]=j+z;





                    if (z==0){

                    QPixmap snake(":/rsc/head.png");
                    block[x[z]][y[z]] = new QGraphicsPixmapItem(snake);
                    scene->addItem(block[x[z]][y[z]]);
                    block[x[z]][y[z]]->setPos(_xborder+x[z]*_width, _yborder+y[z]*_width);

                    }
                    else  {

                        block[x[z]][y[z]] = new QGraphicsPixmapItem(snake_body);
                        scene->addItem(block[x[z]][y[z]]);
                        block[x[z]][y[z]]->setPos(_xborder+x[z]*_width, _yborder+y[z]*_width);
                    }

                }


 break;
            case '3':
                QPixmap powerball(":/rsc/apple.png");
                block[i][j] = new QGraphicsPixmapItem(powerball);
                scene->addItem(block[i][j]);
                block[i][j]->setPos(_xborder+j*_width, _yborder+i*_width);
                apple_block_x=i;
                apple_block_y=j;
                apple_x=j;
                apple_y=i;
                break;









            }
          //  loadImages();

        }
    }


     timerId = startTimer(DELAY);
    score_title = new QLabel(this);
    score_title->setText("score");
    score_title->setStyleSheet("QLabel {font-family: Fixedsys;color: white;font-size: 16px;}");
    score_title->setGeometry(50,12,60,26);
    score_label = new QLabel(this);
    score_label->setIndent(-80);
    score_label->setText("0");
    score_label->setStyleSheet("QLabel {font-family: Fixedsys;color: white;font-size: 16px;}");
    score_label->setGeometry(110,12,150,26);

    win_label = new QLabel(this);
    win_label->hide();
    win_label->setText("You win!");
    win_label->setStyleSheet("QLabel {font-family: Fixedsys;color: yellow;font-size: 16px;}");
    win_label->setGeometry(310,12,150,26);


    lose_label = new QLabel(this);
    lose_label->hide();
    lose_label->setText("Game over");
    lose_label->setStyleSheet("QLabel {font-family: Fixedsys;color: red;font-size: 16px;}");
    lose_label->setGeometry(200,12,150,26);
    plase_label = new QLabel(this);
    plase_label->hide();
    plase_label->setText("Your plaсe:");
    plase_label->setStyleSheet("QLabel {font-family: Fixedsys;color: red;font-size: 16px;}");
    plase_label->setGeometry(300,12,150,26);

    plase_label_n = new QLabel(this);
    plase_label_n->hide();
    plase_label_n->setText("");
    plase_label_n->setStyleSheet("QLabel {font-family: Fixedsys;color: red;font-size: 16px;}");
    plase_label_n->setGeometry(400,12,150,26);
    restart = new QLabel(this);
    restart->hide();
    restart->setText("Press Q to restart");
    restart->setStyleSheet("QLabel {font-family: Fixedsys;color: red;font-size: 16px;}");
    restart->setGeometry(430,12,150,26);

    mapfile.close();
}



void MainWindow::locateApple() {//new local fruit
   apple_x=(qrand()%58+1) ;
   apple_y=(qrand()%40+1);
   if (walls[apple_y][apple_x]==0){
 block[apple_block_x][apple_block_y]->setPos(_xborder+apple_x*_width, _yborder+apple_y*_width);
}else {locateApple();}
}
void MainWindow::keyPressEvent(QKeyEvent *e) {//key event handler

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

    if( (key == Qt::Key_Q)&&(inGame==false) ) {

    QProcess process;
    process.startDetached("snake",QStringList());

    qApp->quit();}

   QWidget::keyPressEvent(e);
     checkCollision();

}
void MainWindow::timerEvent(QTimerEvent *e) {//check by timer

    Q_UNUSED(e);

    if (inGame) {
        current_num_check++;
        if (current_num_check>=num_check){
             locateApple();
             score=score-10;
              score_label->setText(QString::number(score));
             current_num_check=0;
        }

        checkApple();


    }

   repaint();
}
void MainWindow::checkApple() {//chech fruit

    if ((x_snake[0] == apple_x) && (y_snake[0] == apple_y)) {

        locateApple();
        score=score+10;
score_label->setText(QString::number(score));
         current_num_check=0;
      dots=dots+1;


    }
    if (inMove) { move();}
}
void MainWindow::checkCollision() {//check game over

    if (walls[(y_snake[0])][(x_snake[0])]==1)
    {inGame = false;
    gameOver();

    }


    for (int z = dots; z > 0; z--) {

           if ((z > 4) && (x_snake[0] == x_snake[z]) && (y_snake[0] == y_snake[z])) {
               inGame = false;
               gameOver();


           }
       }


    if(!inGame) {
     //  killTimer(timerId);
    }
}
void MainWindow::move() {//move snake


    for (int z = (dots-1); z > 0; z--) {




           x_snake[z] = x_snake[(z - 1)];
          y_snake[z] = y_snake[(z - 1)];
           block[x[z]][y[z]]->setPos(_xborder+(x_snake[z])*_width, _yborder+(y_snake[z])*_width);

        }

        if (leftDirection) {
x_snake[0] -= 1;
             block[x[0]][y[0]]->setPos(_xborder+(x_snake[0])*_width, _yborder+(y_snake[0])*_width);

        }

        if (rightDirection) {
x_snake[0] += 1;
            block[x[0]][y[0]]->setPos(_xborder+(x_snake[0])*_width, _yborder+(y_snake[0])*_width);

        }

        if (upDirection) {
 y_snake[0] -= 1;
            block[x[0]][y[0]]->setPos(_xborder+x_snake[0]*_width, _yborder+(y_snake[0])*_width);


        }

        if (downDirection) {
            y_snake[0] += 1;
 block[x[0]][y[0]]->setPos(_xborder+x_snake[0]*_width, _yborder+(y_snake[0])*_width);

        }
        if (x_snake[0]==0){x_snake[0]=59;}
        if (x_snake[0]==60){x_snake[0]=0;}
        if (y_snake[0]==0){y_snake[0]=39;}
        if (y_snake[0]==40){y_snake[0]=0;}





checkCollision();

}

void MainWindow::gameOver() {//game over fun



   QString tmp = QString::number(score);
   tmp=tmp+"\r\n";


QFile file("..\\Snake\\score.txt");

    if (file.open(QIODevice::ReadOnly)) {//write score to the file
        //читаем строку
        int str_num=1;
         while (!file.atEnd()) {
              QString str = file.readLine();
            //if ((str_num==2)||(str_num==4)||(str_num==6)||(str_num==8)||(str_num==10)){
//if(tmp<str){
if (str_num==2){
     str2=str;
     if (tmp<str){
    win_pos=1;}
   }
else if (str_num==4){
     str4=str;
     if (tmp<str){
    win_pos=2;}

   }
else if (str_num==6){
     str6=str;
     if (tmp<str){
    win_pos=3;}
   }
else if (str_num==8){
     str8=str;
     if (tmp<str){
    win_pos=4;}
   }
else if (str_num==10){
     str10=str;
     if (tmp<str){
    win_pos=5;}
   }
else if (str_num==1){str1=str;}
else if (str_num==3){str3=str;}
else if (str_num==5){str5=str;}
else if (str_num==7){str7=str;}
else if (str_num==9){str9=str;}



str_num++;
         }


if (win_pos==0){}
else if (win_pos==1){
    str1=name+"\r\n";
                 str2=tmp;}
    else if(win_pos==2){str3=name+"\r\n";
                     str4=tmp;}
    else if (win_pos==3){str5=name+"\r\n";
                     str6=tmp;}
    else if(win_pos==4){str7=name+"\r\n";
                     str8=tmp;}
    else if(win_pos==5){str9=name+"\r\n";
                     str10=tmp;}






    }
    else {

        qWarning("Could not open file");
      }
file.close();//close
if (file.open(QIODevice::WriteOnly)) {
    QTextStream out(&file);

    out << str1+str2+str3+str4+str5+str6+str7+str8+str9+str10<< endl;
}
else {

    qWarning("Could not open file");
  }
file.close();//close
lose_label->show();
  plase_label_n->setText(QString::number(win_pos));
 plase_label->show();
  plase_label_n->show();
  restart->show();
}




MainWindow::~MainWindow() {
    delete ui;
}
