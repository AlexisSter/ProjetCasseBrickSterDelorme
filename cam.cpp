#include "cam.h"

#include <QTime>
#include <QtCore>

Cam::Cam()
{
    capwebcam.open(0);


    if(capwebcam.isOpened() == false){

        return;



    }
    tmrTimer = new QTimer(this);
    connect(tmrTimer,SIGNAL(timeout()),this,SLOT(processFrameAndUpdateGUI()));
    tmrTimer->start(100);
    frameWidth=320;
    frameHeight=240;
    subImageWidth=100;
    subImageHeight=100;
    templateWidth=50;
    templateHeight=50;

}
