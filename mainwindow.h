#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <opencv2/opencv.hpp>

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


    QImage qimgOriginal;
    QImage qimgProcess;

    std::vector<cv::Vec3f>VecCircles;
    std::vector<cv::Vec3f>::iterator itrCircles;

    QTimer* tmrTimer;

public slots:
   void processFrameAndUpdateGUI();



private slots:




};

#endif // MAINWINDOW_H
