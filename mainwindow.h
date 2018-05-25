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
    //gère l'interface graphique
    Ui::MainWindow *ui;
    //gère la webcam
    cv::VideoCapture capwebcam;

    //gère l'image de la webcam dans l'interface graphique
    QImage qimgOriginal;


    //timer qui gère l'affichage de la webcam
    QTimer* tmrTimer;
    //timer wui gère l'affichage des éléments graphique
    QTimer* timerScore;
    //definie le rectangle de traitement pour calculer le balayement de la main
    int frameWidth;
    int frameHeight;
    int subImageWidth;
    int subImageHeight;
    int templateWidth;
    int templateHeight;

    //compteur qui gère la pause
    int i=1;
    //gère l'etat de mouvement de la barre(arrété ou en marche)
    bool etat=false;
    //gère le traitement des images
    Mat frame1,frame2,frameRect1,frameRect2;






public:
    //gère les évènement liée au touche
    void keyPressEvent(QKeyEvent * event);

public slots:
    //gère le slot du timer de la webcam
    void processFrameAndUpdateGUI();
    //gère le slot du timer de l'affichage des éléments graphique
    void updateScore();


private slots:
    //gère le bouton valider de l'interface
    void on_valider_clicked();
};

#endif // MAINWINDOW_H
