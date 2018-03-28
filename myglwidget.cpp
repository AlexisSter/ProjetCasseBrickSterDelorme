#include "myglwidget.h"
#include <QApplication>
#include <QDesktopWidget>
#include <stdlib.h>
#include <time.h>
#include <stdio.h>
#include<QPoint>
#include<qDebug>
#include<QMouseEvent>
#include "brique.h"
#include <GL/glu.h>

// Declarations des constantes
const unsigned int WIN_WIDTH  = 1300;
const unsigned int WIN_HEIGHT = 600;
const float ASPECT_RATIO      = static_cast<float>(WIN_WIDTH) / WIN_HEIGHT;
const float ORTHO_DIM         = 50.0f;

const float MAX_DIMENSION     = 50.0f;


// Constructeur
MyGLWidget::MyGLWidget(QWidget * parent) : QGLWidget(parent)
{
    // Reglage de la taille/position
    setFixedSize(WIN_WIDTH, WIN_HEIGHT);
    move(QApplication::desktop()->screen()->rect().center() - rect().center());
    initializeGL();
    // Connexion du timer
    connect(&m_AnimationTimer,  &QTimer::timeout, [&] {
        m_TimeElapsed += 1.0f; // 12.0f;
        updateGL();
    });

    m_AnimationTimer.setInterval(10);
    m_AnimationTimer.start();
    briqueAlive_ = true;


    xBarre_ = 0.5;
    yBarre_ = 0.05;
    longueurBarre_ = 10;
    hauteurBarre_ = 3;
    Xdir = 0.1;
    Ydir = 0.1;
    start = false;

}


// Fonction d'initialisation
void MyGLWidget::initializeGL()
{
    // Reglage de la couleur de fond
    glClearColor(0.5f, 0.5f, 0.5f, 1.0f);
    glEnable(GL_DEPTH_TEST);
    Brique *brique1 = new Brique(-47, 21, -1, 5,3,1);
    Brique *brique2 = new Brique(-41, 21, -1, 5,3,1);
    Brique *brique3 = new Brique(-35, 21, -1, 5,3,1);
    Brique *brique4 = new Brique(-29, 21, -1, 5,3,1);
    Brique *brique5 = new Brique(-23, 21, -1, 5,3,1);
    Brique *brique6 = new Brique(-17, 21, -1, 5,3,1);
    Brique *brique7 = new Brique(-11, 21, -1, 5,3,1);
    Brique *brique8 = new Brique(-5, 21, -1, 5,3,1);

    m_Brique.push_back(brique1);
    m_Brique.push_back(brique2);
    m_Brique.push_back(brique3);
    m_Brique.push_back(brique4);
    m_Brique.push_back(brique5);
    m_Brique.push_back(brique6);
    m_Brique.push_back(brique7);
    m_Brique.push_back(brique8);




}


void MyGLWidget::affiche_barre()
{


    glBegin(GL_QUADS); // Primitive à afficher et début de la déclaration des vertices de cette primitive
    //face avant
    glVertex3f(xBarre_ - longueurBarre_ / 2,-25 + hauteurBarre_,-1);  // Définition des coordonnées des sommets (en 2D, z=0) OK
    glVertex3f(xBarre_ + longueurBarre_/ 2 , -25+hauteurBarre_,-1);
    glVertex3f(xBarre_ + longueurBarre_ / 2, -25,-1);
    glVertex3f(xBarre_ - longueurBarre_ / 2, -25, -1);
    //face arrière
    glVertex3f(xBarre_ - longueurBarre_ / 2, -25,-3);  // Définition des coordonnées des sommets (en 2D, z=0) OK
    glVertex3f(xBarre_ + longueurBarre_ / 2 , -25,-3);
    glVertex3f(xBarre_ + longueurBarre_ / 2, -25+ hauteurBarre_,-3);
    glVertex3f(xBarre_ - longueurBarre_ / 2, -25+ hauteurBarre_,-3);
    //face dessous
    glVertex3f(xBarre_ - longueurBarre_ / 2, -25,-1);  // Définition des coordonnées des sommets (en 2D, z=0)OK
    glVertex3f(xBarre_ - longueurBarre_ / 2 , -25,-3);
    glVertex3f(xBarre_ + longueurBarre_ / 2, -25,-1);
    glVertex3f(xBarre_ + longueurBarre_ / 2, -25,-3);
    //face dessus
    glVertex3f(xBarre_ - longueurBarre_ / 2, -25 + hauteurBarre_,-1);  // Définition des coordonnées des sommets (en 2D, z=0)OK
    glVertex3f(xBarre_ - longueurBarre_ / 2 , -25 + hauteurBarre_ ,-3);
    glVertex3f(xBarre_ + longueurBarre_ / 2, -25 + hauteurBarre_,-1);
    glVertex3f(xBarre_ + longueurBarre_ / 2, -25 + hauteurBarre_,- 3);
    //face droite
    glVertex3f(xBarre_ + longueurBarre_ / 2, -25 + hauteurBarre_ ,-1);  // Définition des coordonnées des sommets (en 2D, z=0)
    glVertex3f(xBarre_ + longueurBarre_ / 2 , -25 + hauteurBarre_,-3);
    glVertex3f(xBarre_ + longueurBarre_ / 2,  - 25,-1);
    glVertex3f(xBarre_ + longueurBarre_ / 2, -25,-3);
    //face gauche
    glVertex3f(xBarre_ - longueurBarre_ / 2, -25+ hauteurBarre_ ,-1);  // Définition des coordonnées des sommets (en 2D, z=0)
    glVertex3f(xBarre_ - longueurBarre_ / 2 ,-25 + hauteurBarre_ ,-3);
    glVertex3f(xBarre_ - longueurBarre_ / 2, -25,-1);
    glVertex3f(xBarre_ - longueurBarre_ / 2, -25,-3);
    glEnd();

}
void MyGLWidget::mouseMoveEvent(QMouseEvent *event)
{
    this->setMouseTracking(true);
    QPoint positionSouris = event->pos();
    QString message = "x : " + QString::number(positionSouris.x()) + " - y : " + QString::number(positionSouris.y())+ " - xbarre : " + QString::number(xBarre_);
    start  = true;
    if(start)
    {



        xBarre_ =-50+ positionSouris.x() /13;
        qDebug() << message;


    }
    else
    {
        qDebug() << message;
    }
    event->accept();

}


void MyGLWidget::drawBoule(float x, float y, float radius)
{
    glTranslatef(XBoule,YBoule,0);
    GLUquadric* quadrique=gluNewQuadric();
    gluSphere(quadrique, radius, 100, 100);

    gluDeleteQuadric(quadrique);
}

int MyGLWidget::gestionBoule(float larg_balle)
{
        // Position de la balle
       // Direction de la balle

  // Affiche la balle
  drawBoule(XBoule, YBoule, larg_balle);

  // Avance la balle


  // G�re les rebonds
  if((XBoule+larg_balle/2)>50)  Xdir*=-1;
  if((XBoule-larg_balle/2)<-50) Xdir*=-1;
  if((YBoule+larg_balle/2)>25)  Ydir*=-1;
  if((YBoule-larg_balle/2)<-25) return 0; // La balle est derri�re la barre... fin du jeu

  // Teste les contacts entre la balle et la barre
  if((YBoule-larg_balle/2<=-25+hauteurBarre_)) // Si la balle est au niveau de la barre
  {
    // Teste au niveau de l'axe des abscisses
    if(((XBoule+larg_balle/2)>=(xBarre_-longueurBarre_/2)) && ((XBoule-larg_balle/2)<=(xBarre_+longueurBarre_/2)))
    {
      // Fait le rebond
      Ydir*=-1;
            if((XBoule-xBarre_ > 1) && (XBoule-xBarre_ <=2)) Xdir=0.1;
            if((XBoule-xBarre_ > 2) && (XBoule-xBarre_ <= 3)) Xdir=0.2;
            if((XBoule-xBarre_ > 3) && (XBoule-xBarre_ <=4)) Xdir=0.3;
            if((XBoule-xBarre_ > 4) && (XBoule-xBarre_ <= 5)) Xdir=0.4;
            if((XBoule-xBarre_ > 5) && (XBoule-xBarre_ <=6)) Xdir=0.5;

            if((XBoule-xBarre_ < -1) && (XBoule-xBarre_ <= -2)) Xdir=-0.1;
            if((XBoule-xBarre_ < -2) && (XBoule-xBarre_ <= -3)) Xdir=-0.2;
            if((XBoule-xBarre_ < -3) && (XBoule-xBarre_ <= -4)) Xdir=-0.3;
            if((XBoule-xBarre_ < -4) && (XBoule-xBarre_ <= -5)) Xdir=-0.4;
            if((XBoule-xBarre_ < -5) && (XBoule-xBarre_ <= -6)) Xdir=-0.5;

    }
  }
  XBoule=XBoule+Xdir;
  YBoule=YBoule+Ydir;

  return 1; // Fin de la fonction, tous s'est bine pass� !
}



// Fonction de redimensionnement
void MyGLWidget::resizeGL(int width, int height)
{
    // Definition du viewport (zone d'affichage)
    glViewport(0,0,1300,600);
    // Definition de la matrice de projection
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-ORTHO_DIM * ASPECT_RATIO, ORTHO_DIM * ASPECT_RATIO, -ORTHO_DIM, ORTHO_DIM, -2.0f * ORTHO_DIM, 2.0f * ORTHO_DIM);

    // Definition de la matrice de modele
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}


// Fonction d'affichage
void MyGLWidget::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT);


    // Reinitialisation du tampon de couleur

    // Reinitialisation de la matrice courante


    // Reinitialisation des tampons
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Definition de la position de la camera
    glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        glOrtho(-MAX_DIMENSION, MAX_DIMENSION, -MAX_DIMENSION * WIN_HEIGHT / static_cast<float>(WIN_WIDTH), MAX_DIMENSION * WIN_HEIGHT / static_cast<float>(WIN_WIDTH), -MAX_DIMENSION * 2.0f, MAX_DIMENSION * 2.0f);
        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    gluLookAt(0,0,5,0,0,0,0,1,0);

    for ( int i = 0; i<m_Brique.size();i++){
        m_Brique[i]->Display(m_TimeElapsed);
    }



    affiche_barre();
    //drawBoule(0.5, 0.2, 0.03);
    gestionBoule(1);


}


// Fonction de gestion d'interactions clavier
void MyGLWidget::keyPressEvent(QKeyEvent * event)
{
    switch(event->key())
    {
    // Changement de couleur du fond
    case Qt::Key_B:
    {

        break;
    }

        // Changement de couleur de l'objet
    case Qt::Key_C:
    {

        break;
    }

        // Affichage/Masquage de l'objet
    case Qt::Key_H:
    {

        break;
    }

        // Changement de l'objet a afficher
    case Qt::Key_Space:
    {
        //start = !start;
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

    case Qt::Key_R:
    {

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
    updateGL();
}


