#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <opencv2/opencv.hpp>
#include "opencv2/video/tracking.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"
#include <QDebug>

#include <cstdio>
#include <iostream>
using namespace cv;
using namespace std;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;



    cv::VideoCapture capwebcam;
    cv::Mat matOriginal;
    cv::Mat matProcess;

    int compt;
    QImage qimgOriginal;
    QImage qimgProcess;

    std::vector<cv::Vec3f>VecCircles;
    std::vector<cv::Vec3f>::iterator itrCircles;

    QTimer* tmrTimer;
    QTimer* timerScore;
    int frameWidth;
    int frameHeight;
    int subImageWidth;
    int subImageHeight;
    int templateWidth;
    int templateHeight;
    int i=1;
    bool etat=false;

    Mat frame1,frame2,frameRect1,frameRect2;






public:
    void keyPressEvent(QKeyEvent * event);



public slots:
    void processFrameAndUpdateGUI();
    void updateScore();




private slots:
    void on_valider_clicked();
};

#endif // MAINWINDOW_H
