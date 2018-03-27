#include "brique.h"
#include<QPoint>
#include<qDebug>
Brique::Brique(float x, float y, float longueur, float hauteur)
{
    x_ = x;
    y_ = y;
    longueur_ = longueur;
    hauteur_ = hauteur;
    glBegin(GL_QUADS); // Primitive à afficher et début de la déclaration des vertices de cette primitive
    glVertex2f(x_ - longueur_ / 2, y_ - hauteur_ / 2);  // Définition des coordonnées des sommets (en 2D, z=0)
    glVertex2f(x_ + longueur_ / 2 , y_ - hauteur_ / 2);
    glVertex2f(x_ + longueur_ / 2, y_ + hauteur_/2);
    glVertex2f(x_ - longueur_ / 2, y_ + hauteur_/2);
    glEnd();
}


void Brique::briqueTouched()
{
     x_ = 0;
     y_ = 0;
     longueur_ = 0;
     hauteur_ = 0;
}
