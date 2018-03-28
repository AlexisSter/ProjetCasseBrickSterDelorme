#ifndef BRIQUE_H
#define BRIQUE_H
#include<QPoint>
#include <GL/glu.h>
#include <QColor>
#include <QApplication>
#include <QDesktopWidget>
class Brique
{
public:
    Brique(float x, float y,float z, float longueur, float hauteur,float profondeur);
    void Display(const float timeInDays) const;
    void briqueTouched();
private :
    float x_;
    float y_;
    float z_;
    float longueur_;
    float hauteur_;
    float profondeur_;

protected :
    ~Brique();
    getX(){return x_;}
    getY(){return y_;}
    getLongueur(){return longueur_;}
    getHauteur(){return hauteur_;}

};

#endif // BRIQUE_H
