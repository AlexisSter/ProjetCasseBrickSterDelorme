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
    Brique(float x, float y,float z, float longueur, float hauteur,float profondeur,GLuint text,QImage texture);
    void Display(const float timeInDays) const;
    void briqueTouched();
    float getX(){return x_;}
    float getY(){return y_;}
    float getLongueur(){return longueur_;}
    float getHauteur(){return hauteur_;}
    bool getTouched(){return touched_;}
    void setTouched(bool valeur){ touched_=valeur;}

    void setColor(float red_, float green_, float blue_) {red = red_, green=green_, blue = blue_;}
    int getHpBrique(){return hpBrique;}
    void setHpBrique(int hp){ hpBrique=hp;}
private :
    float x_;
    float y_;
    float z_;
    float longueur_;
    float hauteur_;
    float profondeur_;
    float red;
    float green;
    float blue;
    bool touched_;
    GLuint texture_id;
    QImage texture_image;
    int hpBrique;


protected :
    ~Brique();


};

#endif // BRIQUE_H
