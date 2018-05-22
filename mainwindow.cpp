#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QTime>
#include <QtCore>
#include <QtGui>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->label->setAlignment(Qt::AlignLeft);
    ui->label->setAlignment(Qt::AlignTop);
    ui->joueur->setAlignment(Qt::AlignCenter);
    ui->score->setAlignment(Qt::AlignHCenter);
    ui->niveau->setAlignment(Qt::AlignHCenter);
    ui->boule->setAlignment(Qt::AlignHCenter);

    capwebcam.open(0);


    if(capwebcam.isOpened() == false){

        return;



    }
    tmrTimer = new QTimer(this);
    timerScore  = new QTimer(this);
    connect(tmrTimer,SIGNAL(timeout()),this,SLOT(processFrameAndUpdateGUI()));
    connect(tmrTimer,SIGNAL(timeout()),this,SLOT(updateScore()));
    timerScore->start(1);
    tmrTimer->start(100);

    frameWidth=320;
    frameHeight=240;
    subImageWidth=100;
    subImageHeight=100;
    templateWidth=50;
    templateHeight=50;
    compt = 0;
}

MainWindow::~MainWindow()
{
    delete ui;
}
void MainWindow::processFrameAndUpdateGUI(){
    compt++;
    //while(compt < 10){
        //if(compt==12)compt=0;

    Rect workingRect(120,65,subImageWidth,subImageHeight);
    Rect templateRect((workingRect.width-templateWidth)/2,(workingRect.height-templateHeight)/2,templateWidth,templateHeight);
    Point workingCenter(workingRect.x+subImageWidth/2,workingRect.y+subImageHeight/2);

    capwebcam.set(CV_CAP_PROP_FRAME_WIDTH,frameWidth);
    capwebcam.set(CV_CAP_PROP_FRAME_HEIGHT,frameHeight);
    capwebcam.read(frame1);

    cv::flip(frame1,frame1,1);
    // Extract rect1 and convert to gray
    cv::cvtColor(Mat(frame1,workingRect),frameRect1,COLOR_BGR2GRAY);
    //Mat(frame1,rect).copyTo(frameRect1);

    // Create the matchTemplate image result
    Mat resultImage;    // to store the matchTemplate result
    int result_cols =  frame1.cols-templateWidth  + 1;
    int result_rows = frame1.rows-templateHeight + 1;
    resultImage.create( result_cols, result_rows, CV_32FC1 );

        // Get frame2
        capwebcam.read(frame2);
        //cap >> frame2;
        // Mirror effect
        cv::flip(frame2,frame2,1);
        // Extract working rect in frame2 and convert to gray
        cv::cvtColor(Mat(frame2,workingRect),frameRect2,COLOR_BGR2GRAY);

        // Extract template image in frame1
        Mat templateImage(frameRect1,templateRect);
        // Do the Matching between the working rect in frame2 and the templateImage in frame1
        matchTemplate( frameRect2, templateImage, resultImage, TM_CCORR_NORMED );
        // Localize the best match with minMaxLoc
        double minVal; double maxVal; Point minLoc; Point maxLoc;
        minMaxLoc( resultImage, &minVal, &maxVal, &minLoc, &maxLoc);
        // Compute the translation vector between the origin and the matching rect
        Point vect(maxLoc.x-templateRect.x,maxLoc.y-templateRect.y);

        // Draw green rectangle and the translation vector
        rectangle(frame2,workingRect,Scalar( 0, 255, 0),2);
        Point p(workingCenter.x+vect.x,workingCenter.y+vect.y);
        arrowedLine(frame2,workingCenter,p,Scalar(255,255,255),2);


        if(vect.x>5 && etat ){
            //ui->label->setText("droite");

            ui->widget->setXbarre((vect.x)/6);
        }
        if(vect.x<-5 && etat){

             //ui->label->setText("gauche");

             ui->widget->setXbarre((vect.x)/6);
        }
        if(vect.y>15){
            qDebug()<<"coucou toi";
            ui->widget->setXbarre(0);
            etat=false;
        }
        if(vect.x >15 || vect.x<-15){
            etat=true;
            ui->widget->setXbarre((vect.x)/6);
        }

        // Display frame2
        //imshow("WebCam2", frame2);
        QImage qimgOriginal((uchar*)frame2.data,frame2.cols,frame2.rows,frame2.step,QImage::Format_RGB888);
        ui->lblOriginal->setPixmap(QPixmap::fromImage(qimgOriginal));
        // Swap matrixes
        swap(frameRect1,frameRect2);
        //}





}
void MainWindow::updateScore(){
    ui->label->clear();
    ui->label->setText("<html> "+ ui->widget->getUn()+"<br>" + ui->widget->getDeux() + "<br>" + ui->widget->getTrois() +"<br>" + ui->widget->getQuatre() +"<br>" + ui->widget->getCinq() + "<br>" + ui->widget->getSix() + "<br>" + ui->widget->getSept() +"<br>" + ui->widget->getHuit() +"<br>" + ui->widget->getNeuf() +"<br>" + ui->widget->getDix() + "</html");

    ui->score->setText(ui->widget->getScore());
    ui->boule->setText(ui->widget->getNbBoule());
    ui->niveau->setText(ui->widget->getNiveau());
    ui->widget->setNomJoueur(ui->joueur->text().toStdString());

}
void MainWindow::keyPressEvent(QKeyEvent * event)
{
    switch(event->key())
    {
    // Changement de couleur du fond
    case Qt::Key_B:
    {

        break;
    }

        // Changement de couleur de l'objet
    case Qt::Key_Enter:
    {

        break;
    }

        // Affichage/Masquage de l'objet
    case Qt::Key_I:
    {
        ui->widget->setStart(true);
        break;
    }

    case Qt::Key_Space:
    {

        break;
    }

        // Sortie de l'application
    case Qt::Key_Escape:
    {
        close();
        break;
    }
    case Qt::Key_Left:
    {

        break;
    }
    case Qt::Key_Right:
    {

        break;
    }
    case Qt::Key_Up:
    {

        break;
    }
    case Qt::Key_Down:
    {

        break;
    }

    case Qt::Key_P:
    {
        if(i%2==0){
            ui->widget->setPause(false);
            i=1;

        }
        else{
            ui->widget->setPause(true);
            i=2;
        }

        break;
    }
        // Cas par defaut
    default:
    {
        // Ignorer l'evenement
        event->ignore();
        return;
    }
    }

    // Acceptation de l'evenement et mise a jour de la scene
    event->accept();

}


void MainWindow::on_valider_clicked()
{
    ui->joueur->setText(ui->recupNom->text());
    ui->recupNom->setReadOnly(true);
    //ui->valider->setCheckable(false);
    //ui->valider->setChecked(true);

}
