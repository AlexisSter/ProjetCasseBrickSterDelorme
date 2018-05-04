#include "brique.h"
#include<QPoint>
#include<qDebug>
Brique::Brique(float x, float y,float z, float longueur, float hauteur,float profondeur,GLuint text,QImage texture)
{
    x_ = x;
    y_ = y;
    z_ = z;
    longueur_ = longueur;
    hauteur_ = hauteur;
    profondeur_=profondeur;
    touched_ = false;
    texture_id=text;
    texture_image=texture;
}


void Brique::briqueTouched()
{
     x_ = 0;
     y_ = 0;
     longueur_ = 0;
     hauteur_ = 0;
     touched_=true;
}
void Brique::Display(const float timeInDays) const
{

    glBindTexture( GL_TEXTURE_2D, texture_id);
    glTexImage2D( GL_TEXTURE_2D, 0, 4, texture_image.width(), texture_image.height(), 0, GL_RGBA, GL_UNSIGNED_BYTE, texture_image.bits() );
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    glBegin(GL_QUADS); // Primitive à afficher et début de la déclaration des vertices de cette primitive
    //face avant
    glColor3f(red,green,blue);
    glTexCoord2f(0, 0); glVertex3f(x_ - longueur_ / 2, y_ - hauteur_ / 2,z_);  // Définition des coordonnées des sommets (en 2D, z=0)
    glTexCoord2f(1, 0); glVertex3f(x_ + longueur_ / 2 , y_ - hauteur_ / 2,z_);
    glTexCoord2f(1, 1); glVertex3f(x_ + longueur_ / 2, y_ + hauteur_/2,z_);
    glTexCoord2f(0, 1); glVertex3f(x_ - longueur_ / 2, y_ + hauteur_/2,z_);
    //face arrière
    glVertex3f(x_ - longueur_ / 2, y_ - hauteur_ / 2,z_- profondeur_);  // Définition des coordonnées des sommets (en 2D, z=0)
    glVertex3f(x_ + longueur_ / 2 , y_ - hauteur_ / 2,z_ - profondeur_);
    glVertex3f(x_ + longueur_ / 2, y_ + hauteur_/2,z_ - profondeur_);
    glVertex3f(x_ - longueur_ / 2, y_ + hauteur_/2,z_ - profondeur_);
    //face dessous
    glVertex3f(x_ - longueur_ / 2, y_ - hauteur_ / 2,z_);  // Définition des coordonnées des sommets (en 2D, z=0)
    glVertex3f(x_ - longueur_ / 2 , y_ - hauteur_ / 2,z_ - profondeur_);
    glVertex3f(x_ + longueur_ / 2, y_ - hauteur_/2,z_);
    glVertex3f(x_ + longueur_ / 2, y_ - hauteur_/2,z_ - profondeur_);
    //face dessus
    glVertex3f(x_ - longueur_ / 2, y_ + hauteur_ / 2,z_);  // Définition des coordonnées des sommets (en 2D, z=0)
    glVertex3f(x_ - longueur_ / 2 , y_ + hauteur_ / 2,z_ - profondeur_);
    glVertex3f(x_ + longueur_ / 2, y_ + hauteur_/2,z_);
    glVertex3f(x_ + longueur_ / 2, y_ + hauteur_/2,z_ - profondeur_);
    //face droite
    glVertex3f(x_ + longueur_ / 2, y_ + hauteur_ / 2,z_);  // Définition des coordonnées des sommets (en 2D, z=0)
    glVertex3f(x_ + longueur_ / 2 , y_ + hauteur_ / 2,z_ - profondeur_);
    glVertex3f(x_ + longueur_ / 2, y_ - hauteur_/2,z_);
    glVertex3f(x_ + longueur_ / 2, y_ - hauteur_/2,z_ - profondeur_);
    //face gauche
    glVertex3f(x_ - longueur_ / 2, y_ + hauteur_ / 2,z_);  // Définition des coordonnées des sommets (en 2D, z=0)
    glVertex3f(x_ - longueur_ / 2 , y_ + hauteur_ / 2,z_ - profondeur_);
    glVertex3f(x_ - longueur_ / 2, y_ - hauteur_/2,z_);
    glVertex3f(x_ - longueur_ / 2, y_ - hauteur_/2,z_ - profondeur_);
    glEnd();


    //glPopMatrix();
}
