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


// Constructeur
MyGLWidget::MyGLWidget(QWidget * parent) : QGLWidget(parent)
{
    // Reglage de la taille/position
    setFixedSize(WIN_WIDTH, WIN_HEIGHT);
    move(QApplication::desktop()->screen()->rect().center() - rect().center());
    red = 0.0;
    green = 0.0;
    blue = 255.0;

    redBackground = 0.5;
    blueBackground = 0.5;
    greenBackground = 0.5;

    briqueAlive_ = true;

    hide = false;
    xBarre_ = 0.5;
    yBarre_ = 0.05;
    longueurBarre_ = 0.1;
    start = false;

}


// Fonction d'initialisation
void MyGLWidget::initializeGL()
{
    // Reglage de la couleur de fond
    glClearColor(0.5f, 0.5f, 0.5f, 1.0f);
}


void MyGLWidget::affiche_barre(float hauteur)
{
    glBegin (GL_QUADS);
    glColor3f (0.0f, 0.0f, 1.0f);   glVertex2f (xBarre_ - longueurBarre_ / 2, hauteur);
    glColor3f (0.0f, 1.0f, 0.0f);   glVertex2f (xBarre_ - longueurBarre_ / 2, 0.0);
    glColor3f (0.0f, 1.0f, 1.0f);   glVertex2f (xBarre_ + longueurBarre_ / 2, 0.0);
    glColor3f (0.0f, 1.0f, 1.0f);   glVertex2f (xBarre_ + longueurBarre_ / 2, hauteur);
    glEnd ();
}
void MyGLWidget::mouseMoveEvent(QMouseEvent *event)
{
   this->setMouseTracking(true);
    QPoint positionSouris = event->pos();
    QString message = "x : " + QString::number(positionSouris.x()) + " - y : " + QString::number(positionSouris.y())+ " - xbarre : " + QString::number(xBarre_);

    if(start)
    {
        xBarre_ = positionSouris.x() / 1300.0;
        qDebug() << message;
    }
    else
    {
        qDebug() << message;
    }
    event->accept();
    updateGL();
}


void MyGLWidget::drawBoule(float x, float y, float radius)
{
    float PI = 3.14;
    int i;
    int triangleAmount = 20; //# of triangles used to draw circle

    //GLfloat radius = 0.8f; //radius
    GLfloat twicePi = 2.0f * PI;

    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(x, y); // center of circle
    for(i = 0; i <= triangleAmount;i++) {
        glVertex2f(
                    x + (radius * cos(i *  twicePi / triangleAmount)),
                    y + (radius * sin(i * twicePi / triangleAmount))
                    );
    }
    glTranslatef(50,0,0);
    glEnd();
    /*int numberOfVertices = numberOfSides + 2;

       GLfloat twicePi = 2.0f * M_PI;

       GLfloat circleVerticesX[numberOfVertices];
       GLfloat circleVerticesY[numberOfVertices];
       GLfloat circleVerticesZ[numberOfVertices];

       circleVerticesX[0] = x;
       circleVerticesY[0] = y;
       circleVerticesZ[0] = z;

       for ( unsigned int i = 1; i < numberOfVertices; i++ )
       {
           circleVerticesX[i] = x + ( radius * cos( i *  twicePi / numberOfSides ) );
           circleVerticesY[i] = y + ( radius * sin( i * twicePi / numberOfSides ) );
           circleVerticesZ[i] = z;
       }

       GLfloat allCircleVertices[( numberOfVertices ) * 3];

       for ( unsigned int i = 0; i < numberOfVertices; i++ )
       {
           allCircleVertices[i * 3] = circleVerticesX[i];
           allCircleVertices[( i * 3 ) + 1] = circleVerticesY[i];
           allCircleVertices[( i * 3 ) + 2] = circleVerticesZ[i];
       }

       glEnableClientState( GL_VERTEX_ARRAY );
       glVertexPointer( 3, GL_FLOAT, 0, allCircleVertices );
       glDrawArrays( GL_TRIANGLE_FAN, 0, numberOfVertices);
       glDisableClientState( GL_VERTEX_ARRAY );*/
}


int MyGLWidget::gestionBoule(float x_barre, float larg_barre, float larg_balle)
{
  static float Xballe=0.5, Yballe=0.2;     // Position de la balle
  static float Xdir=0.001, Ydir=0.001;     // Direction de la balle

  // Affiche la balle
  drawBoule(Xballe, Yballe, larg_balle);

  // Avance la balle
  Xballe=Xballe+Xdir;
  Yballe=Yballe+Ydir;

  // G�re les rebonds
  if((Xballe+larg_balle/2)>1)  Xdir*=-1;
  if((Xballe-larg_balle/2)<-1) Xdir*=-1;
  if((Yballe+larg_balle/2)>1)  Ydir*=-1;
  if((Yballe-larg_balle/2)<-1.5) return 0; // La balle est derri�re la barre... fin du jeu

  // Teste les contacts entre la balle et la barre
  if((Yballe-larg_balle/2<=-0.95) && (Yballe+larg_balle/2>=-0.98)) // Si la balle est au niveau de la barre
  {
    // Teste au niveau de l'axe des abscisses
    if(((Xballe+larg_balle/2)>=(x_barre-larg_barre/2)) && ((Xballe-larg_balle/2)<=(x_barre+larg_barre/2)))
    {
      // Fait le rebond
      Ydir*=-1;
      // Oriente diff�remment la balle selon le contact avec la barre
      Xdir=(Xballe-x_barre)/10;
      // Met une valeur max et une min
      if(Xdir>0.025)  Xdir=0.025;
      if(Xdir<-0.025) Xdir=-0.025;
    }
  }

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
    glColor3ub(red, green, blue);  // Couleur à utiliser pour dessiner les objets

    // Définir la zone à afficher
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0.0, 1.0, 0.0, 1.0, -1.0, 1.0);


    Brique *brique1 = new Brique(0.02, 0.98, 0.05,0.03);
    Brique *brique2 = new Brique(0.075, 0.98, 0.05,0.03);
    Brique *brique3 = new Brique(0.13, 0.98, 0.05,0.03);
    Brique *brique4 = new Brique(0.185, 0.98, 0.05,0.03);
    Brique *brique5 = new Brique(0.24, 0.98, 0.05,0.03);
    Brique *brique6 = new Brique(0.295, 0.98, 0.05,0.03);
    Brique *brique7 = new Brique(0.35, 0.98, 0.05,0.03);
    Brique *brique8 = new Brique(0.405, 0.98, 0.05,0.03);

    affiche_barre(0.02);
    //drawBoule(0.5, 0.2, 0.03);
    gestionBoule(0.5, 0.1, 0.03);


}


// Fonction de gestion d'interactions clavier
void MyGLWidget::keyPressEvent(QKeyEvent * event)
{
    switch(event->key())
    {
    // Changement de couleur du fond
    case Qt::Key_B:
    {
        redBackground = (float)rand()/RAND_MAX;
        blueBackground = (float)rand()/RAND_MAX;
        greenBackground = (float)rand()/RAND_MAX;
        glClearColor(redBackground, blueBackground, greenBackground, 1.0f);
        break;
    }

        // Changement de couleur de l'objet
    case Qt::Key_C:
    {
        red = rand();
        blue = rand();
        green = rand();
        break;
    }

        // Affichage/Masquage de l'objet
    case Qt::Key_H:
    {
        hide =  !hide;
        break;
    }

        // Changement de l'objet a afficher
    case Qt::Key_Space:
    {
        start = !start;
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
        glTranslatefL();
        break;
    }
    case Qt::Key_Right:
    {
        glTranslatefR();
        break;
    }
    case Qt::Key_Up:
    {
        glTranslatefH();
        break;
    }
    case Qt::Key_Down:
    {
        glTranslatefB();
        break;
    }

    case Qt::Key_R:
    {
        rotate = rotate + 5;
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

void MyGLWidget::glTranslatefL()
{
    x = x - 0.05;
}

void MyGLWidget::glTranslatefR()
{
    x = x + 0.05;
}

void MyGLWidget::glTranslatefH()
{
    y = y + 0.05;
}

void MyGLWidget::glTranslatefB()
{
    y = y - 0.05;
}
