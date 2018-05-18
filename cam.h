#ifndef CAM_H
#define CAM_H
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

class Cam
{
public:

    Q_OBJECT

public:
    explicit Cam(QWidget *parent = 0);
    ~Cam();

private:




    cv::VideoCapture capwebcam;
    cv::Mat matOriginal;
    cv::Mat matProcess;


    QImage qimgOriginal;
    QImage qimgProcess;

    std::vector<cv::Vec3f>VecCircles;
    std::vector<cv::Vec3f>::iterator itrCircles;

    QTimer* tmrTimer;
    int frameWidth;
    int frameHeight;
    int subImageWidth;
    int subImageHeight;
    int templateWidth;
    int templateHeight;
    int i=2;
    bool etat=false;

    Mat frame1,frame2,frameRect1,frameRect2;






public:
    void keyPressEvent(QKeyEvent * event);



public slots:
    void processFrameAndUpdateGUI();




};

#endif // CAM_H
