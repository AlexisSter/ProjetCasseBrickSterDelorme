#ifndef BRIQUE_H
#define BRIQUE_H
#include<QPoint>
#include "myglwidget.h"
class Brique
{
public:
    Brique(float x, float y, float longueur, float hauteur);
    void briqueTouched();
private :
    float x_;
    float y_;
    float longueur_;
    float hauteur_;

protected :
    ~Brique();
    getX(){return x_;}
    getY(){return y_;}
    getLongueur(){return longueur_;}
    getHauteur(){return hauteur_;}

};

#endif // BRIQUE_H
