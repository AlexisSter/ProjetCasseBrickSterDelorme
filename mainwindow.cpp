#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QtCore>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);


    capwebcam.open(0);

    if(capwebcam.isOpened() == false){
        //ui->textXYRadius->appendPlainText("error webcam access denied");
        return;



    }
    tmrTimer = new QTimer(this);
    connect(tmrTimer,SIGNAL(timeout()),this,SLOT(processFrameAndUpdateGUI()));
    tmrTimer->start(20);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::processFrameAndUpdateGUI(){
capwebcam.read(matOriginal);

if(matOriginal.empty() == true) return;

cv::inRange(matOriginal, cv::Scalar(0,0,175),cv::Scalar(100,100,255),matProcess);
cv::GaussianBlur(matProcess,matProcess,cv::Size(9,9),1.5);
cv::HoughCircles(matProcess,VecCircles,CV_HOUGH_GRADIENT,2, matProcess.rows / 4, 100,50,10,400);

for(itrCircles = VecCircles.begin();itrCircles != VecCircles.end() ; itrCircles++){
    //ui->textXYRadius->appendPlainText(QString("Ball position x : ") + QString::number((*itrCircles)[0]).rightJustified(4,' ')+
                                      //QString("ball position y : ") + QString::number((*itrCircles)[1]).rightJustified(4,' ')+
                                      //QString("ball radius : ") + QString::number((*itrCircles)[2],'f',3).rightJustified(7,' '));

    cv::circle(matOriginal, cv::Point((int)(*itrCircles)[0],(int)(*itrCircles)[1]),3,cv::Scalar(0,255,0),CV_FILLED);
    cv::circle(matOriginal, cv::Point((int)(*itrCircles)[0],(int)(*itrCircles)[1]),(int)(*itrCircles)[2],cv::Scalar(0,0,255),3);



}
cv::cvtColor(matOriginal,matOriginal,CV_BGR2RGB);

QImage qimgOriginal((uchar*)matOriginal.data,matOriginal.cols,matOriginal.rows,matOriginal.step,QImage::Format_RGB888);
//QImage qimgProcess((uchar*)matProcess.data,matProcess.cols,matProcess.rows,matProcess.step,QImage::Format_Indexed8);
ui->lblOriginal->setPixmap(QPixmap::fromImage(qimgOriginal));
//ui->lblProcess->setPixmap(QPixmap::fromImage(qimgProcess));





}
