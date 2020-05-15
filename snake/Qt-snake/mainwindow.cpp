#include "mainwindow.h"
#include "snake.h"
#include "ui_mainwindow.h"
#include <QInputDialog>
#include <QTime>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setWindowTitle(tr("pac-man"));
    ui->graphicsView->setStyleSheet("QGraphicsView {border: none;}");
    ui->graphicsView->setBackgroundBrush(Qt::black);
    scene = new QGraphicsScene(50, 50, ui->graphicsView->width() - 2, ui->graphicsView->height() - 2);
    ui->graphicsView->setFocusPolicy(Qt::NoFocus);
    ui->graphicsView->setScene(scene);
    set_board();
    timer = new QTimer(this);
    flash = new QTimer(this);
    timer->start(6);
    flash->start(200);
    QString text = QInputDialog::getText(this, tr("Ввод теста"),
                            tr("Name"), QLineEdit::Normal,
                            tr("Your name"), &ok);

    if (ok && !text.isEmpty())
         name=text;

}

void MainWindow::loadImages() {

    dot.load("..\\img\\dot.png");//addresses to img
    head.load("..\\img\\head.png");
    apple.load("..\\img\\apple.png");

}

void MainWindow::initGame(int x_h,int y_h) {
    num_check=delay_before_destroy/DELAY;

    dots = 2;//num of start dots

    for (int z = 0; z < dots; z++) {
        x[z] = x_h+z;
        y[z] = y_h;
        QPixmap snake(":/rsc/head.png");
        block[x[z]][y[z]] = new QGraphicsPixmapItem(snake);
        scene->addItem(block[x[z]][y[z]]);
        block[x[z]][y[z]]->setPos(_xborder+x[z]*_width, _yborder+y[z]*_width);
    }

   locateApple();//draw a fruit

    //timerId = startTimer(DELAY);

}
void MainWindow::locateApple() {//new local fruit
 QPixmap powerball(":/rsc/apple.png");
 block[4][4] = new QGraphicsPixmapItem(powerball);
 scene->addItem(block[4][4]);
 block[4][4]->setPos(_xborder+4*_width, _yborder+4*_width);

}


MainWindow::~MainWindow() {
    delete ui;
}
