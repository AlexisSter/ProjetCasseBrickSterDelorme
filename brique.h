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
    //Constructeur : initialisation de tous les champs
    Brique(float x, float y,float z, float longueur, float hauteur,float profondeur,GLuint text,QImage texture);
    //Affichage d'une brique
    void Display(const float timeInDays) const;
    //Destruction de la brique
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
    //Coordonnées du centre d'une brique
    float x_;
    float y_;
    float z_;
    //Taille d'une brique en 3D
    float longueur_;
    float hauteur_;
    float profondeur_;
    //Couleur de la brique
    float red;
    float green;
    float blue;
    //Savoir si la une brique est touchée
    bool touched_;
    //Variables de texture d'une brique
    GLuint texture_id;
    QImage texture_image;
    //Point de vie d'une brique
    int hpBrique;


};

#endif // BRIQUE_H
