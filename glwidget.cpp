#include "glwidget.h"
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
#include <QGLWidget>
#include "mainwindow.h"

// Declarations des constantes
const unsigned int WIN_WIDTH  = 1300;
const unsigned int WIN_HEIGHT = 600;
const float ASPECT_RATIO      = static_cast<float>(WIN_WIDTH) / WIN_HEIGHT;
const float ORTHO_DIM         = 50.0f;

const float MAX_DIMENSION     = 50.0f;
int a=0;


// Constructeur
GLWidget::GLWidget(QWidget * parent) : QGLWidget(parent)
{
    // Reglage de la taille/position




    setFixedSize(WIN_WIDTH, WIN_HEIGHT);
    move(QApplication::desktop()->screen()->rect().center() - rect().center());
    initializeGL();
    // Connexion du timer
    pause = false;
    start = true;
    connect(&m_AnimationTimer,  &QTimer::timeout, [&] {
        if(start)
        {
            if(!pause)
            {
                m_TimeElapsed += 0.01f; // 12.0f;
                updateGL();
            }
        }

    });

    m_AnimationTimer.setInterval(10);
    m_AnimationTimer.start();
    briqueAlive_ = true;

    xBarre_ = 0.5;
    yBarre_ = 0.05;
    longueurBarre_ = 10;
    hauteurBarre_ = 1;
    Xdir = 0.0;
    Ydir = 0.1;
    place =false;
    occupied1 = false;
    occupied2 = false;

    XBoule = 0;
    YBoule = -20.5;
    nbBoules_ = 3;
}


// Fonction d'initialisation
void GLWidget::initializeGL()
{
    // Reglage de la couleur de fond
    glEnable(GL_TEXTURE_2D);
    glClearColor(0.5f, 0.5f, 0.5f, 1.0f);
    glEnable(GL_DEPTH_TEST);


    if(!place){
        a=a+1;
        if(a==1){
            QImage qim_Texture1 = QGLWidget::convertToGLFormat(QImage("C:/Users/Alexis/Documents/ProjetCasseBrickSterDelorme/ProjetCasseBrickSterDelorme/texture10.png"));
            QImage qim_Texture2 = QGLWidget::convertToGLFormat(QImage("C:/Users/Alexis/Documents/ProjetCasseBrickSterDelorme/ProjetCasseBrickSterDelorme/texture6.jpg"));
            QImage qim_Texture3 = QGLWidget::convertToGLFormat(QImage("C:/Users/Alexis/Documents/ProjetCasseBrickSterDelorme/ProjetCasseBrickSterDelorme/texture11.png"));
            QImage qim_Texture4 = QGLWidget::convertToGLFormat(QImage("C:/Users/Alexis/Documents/ProjetCasseBrickSterDelorme/ProjetCasseBrickSterDelorme/texture12.png"));
            GLuint* m_TextureID = new GLuint[4];
            glGenTextures( 4, m_TextureID );
            m_texture=m_TextureID[0];
            image=qim_Texture1;
            m_textureFond=m_TextureID[1];
            imageFond=qim_Texture2;
            m_textureBoule=m_TextureID[2];
            imageBoule=qim_Texture3;
            m_textureBarre=m_TextureID[3];
            imageBarre=qim_Texture4;
            placerBrique(100);
            place=true;
            qDebug("coucou");
        }
    }
}

void GLWidget::placerBrique(int n){


    float xStart = -41 ;
    float yStart = 21 ;
    float pas = 0;
    float largeur =9;
    float hauteur = 1.4;
    int t=0;
    for(int i=0; i<n;i++){
        if(xStart+(i-t)*pas+(i-t)*largeur+largeur>50) {
            t=i;

            yStart = yStart - hauteur;

        }

        Brique *briquei = new Brique(xStart+(i-t)*pas+(i-t)*largeur, yStart, -1, largeur,hauteur,1,m_texture,image);
        briquei->setColor((float)rand()/RAND_MAX,(float)rand()/RAND_MAX,(float)rand()/RAND_MAX);
        m_Brique.push_back(briquei);
    }
}
void GLWidget::afficheFond(){
    glBindTexture( GL_TEXTURE_2D, m_textureFond);
    glTexImage2D( GL_TEXTURE_2D, 0, 4, imageFond.width(), imageFond.height(), 0, GL_RGBA, GL_UNSIGNED_BYTE, imageFond.bits() );
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glBegin(GL_QUADS); // Primitive à afficher et début de la déclaration des vertices de cette primitive
    //face avant

    glTexCoord2f(0, 0);glVertex3f(-50,-25,-5);  // Définition des coordonnées des sommets (en 2D, z=0) OK
    glTexCoord2f(1, 0);glVertex3f(50,-25,-5);
    glTexCoord2f(1, 1);glVertex3f(50,25,-5);
    glTexCoord2f(0, 1);glVertex3f(-50,25,-5);

    glEnd();



}
void GLWidget::affiche_barre()
{

    glBindTexture( GL_TEXTURE_2D, m_textureBarre);
    glTexImage2D( GL_TEXTURE_2D, 0, 4, imageBarre.width(), imageBarre.height(), 0, GL_RGBA, GL_UNSIGNED_BYTE, imageBarre.bits() );
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glBegin(GL_QUADS); // Primitive à afficher et début de la déclaration des vertices de cette primitive
    //face avant

    glTexCoord2f(0, 1);glVertex3f(xBarre_ - longueurBarre_ / 2,-22 + hauteurBarre_,-1);  // Définition des coordonnées des sommets (en 2D, z=0) OK
    glTexCoord2f(1, 1);glVertex3f(xBarre_ + longueurBarre_/ 2 , -22+hauteurBarre_,-1);
    glTexCoord2f(1, 0);glVertex3f(xBarre_ + longueurBarre_ / 2, -22,-1);
    glTexCoord2f(0, 0);glVertex3f(xBarre_ - longueurBarre_ / 2, -22, -1);
    //face arrière
    glVertex3f(xBarre_ - longueurBarre_ / 2, -22,-3);  // Définition des coordonnées des sommets (en 2D, z=0) OK
    glVertex3f(xBarre_ + longueurBarre_ / 2 , -22,-3);
    glVertex3f(xBarre_ + longueurBarre_ / 2, -22+ hauteurBarre_,-3);
    glVertex3f(xBarre_ - longueurBarre_ / 2, -22+ hauteurBarre_,-3);
    //face dessous
    glVertex3f(xBarre_ - longueurBarre_ / 2, -22,-1);  // Définition des coordonnées des sommets (en 2D, z=0)OK
    glVertex3f(xBarre_ - longueurBarre_ / 2 , -22,-3);
    glVertex3f(xBarre_ + longueurBarre_ / 2, -22,-1);
    glVertex3f(xBarre_ + longueurBarre_ / 2, -22,-3);
    //face dessus
    glVertex3f(xBarre_ - longueurBarre_ / 2, -22 + hauteurBarre_,-1);  // Définition des coordonnées des sommets (en 2D, z=0)OK
    glVertex3f(xBarre_ - longueurBarre_ / 2 , -22 + hauteurBarre_ ,-3);
    glVertex3f(xBarre_ + longueurBarre_ / 2, -22 + hauteurBarre_,-1);
    glVertex3f(xBarre_ + longueurBarre_ / 2, -22 + hauteurBarre_,- 3);
    //face droite
    glVertex3f(xBarre_ + longueurBarre_ / 2, -22 + hauteurBarre_ ,-1);  // Définition des coordonnées des sommets (en 2D, z=0)
    glVertex3f(xBarre_ + longueurBarre_ / 2 , -22 + hauteurBarre_,-3);
    glVertex3f(xBarre_ + longueurBarre_ / 2,  - 22,-1);
    glVertex3f(xBarre_ + longueurBarre_ / 2, -22,-3);
    //face gauche
    glVertex3f(xBarre_ - longueurBarre_ / 2, -22+ hauteurBarre_ ,-1);  // Définition des coordonnées des sommets (en 2D, z=0)
    glVertex3f(xBarre_ - longueurBarre_ / 2 ,-22 + hauteurBarre_ ,-3);
    glVertex3f(xBarre_ - longueurBarre_ / 2, -22,-1);
    glVertex3f(xBarre_ - longueurBarre_ / 2, -22,-3);
    glEnd();

}
void GLWidget::mouseMoveEvent(QMouseEvent *event)
{

    if(start)
    {
        this->setMouseTracking(true);
        QPoint positionSouris = event->pos();
        QString message = "x : " + QString::number(positionSouris.x()) + " - y : " + QString::number(positionSouris.y())+ " - xbarre : " + QString::number(xBarre_);
        xBarre_ =-50+ positionSouris.x() /13;
    }
    event->accept();

}


void GLWidget::drawBoule(float radius)
{
    glBindTexture(GL_TEXTURE_2D,m_textureBoule);
    //Transmet à OpenGL toutes les caractéristiques de la texture courante : largeur, hauteur, format, etc... et bien sûr l'image
    glTexImage2D( GL_TEXTURE_2D, 0, 4, imageBoule.width(),imageBoule.height(), 0, GL_RGBA, GL_UNSIGNED_BYTE, imageBoule.bits() );
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    glTranslatef(XBoule,YBoule,0);
    GLUquadric* quadrique=gluNewQuadric();
    gluQuadricTexture(quadrique,GL_TRUE);
    gluSphere(quadrique, radius, 100, 100);
    gluDeleteQuadric(quadrique);
}

int GLWidget::gestionBoule(float larg_balle)
{

    // Affiche la balle

    drawBoule(larg_balle);

    // Avance la balle
    // Gère les rebonds

    if((XBoule+larg_balle/2)>50)  Xdir*=-1;
    if((XBoule-larg_balle/2)<-50) Xdir*=-1;
    if((YBoule+larg_balle/2)>23)  Ydir*=-1;
    if((YBoule-larg_balle/2)<-23)
    {
        etatPartie();
    }

    // Teste les collisions entre la boule et la barre
    if((YBoule-larg_balle/2<=-22+hauteurBarre_)) // Si la balle est au niveau de la barre
    {
        // Teste au niveau de l'axe des abscisses
        if(((XBoule+larg_balle/2)>=(xBarre_-longueurBarre_/2)) && ((XBoule-larg_balle/2)<=(xBarre_+longueurBarre_/2)))
        {
            // Fait le rebond

            //Renvoie un angle différent selon la ou on tappe sur la barre
            Ydir=Ydir * -1;
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

    int i=0;
    int y=0;
    int coin=0;
    for(int j=0; j < m_Brique.size() ; j++){
        occupied1 = false;
        occupied2 = false;
        float xBrique = m_Brique[j]->getX();
        float yBrique = m_Brique[j]->getY();
        float hauteurBrique = m_Brique[j]->getHauteur();
        float longueurBrique = m_Brique[j]->getLongueur();
        bool touched = m_Brique[j]->getTouched();
        if(!touched)
        {
            if((YBoule+larg_balle >= yBrique-hauteurBrique/2  && YBoule+larg_balle <0.1+ yBrique-hauteurBrique/2 )|| ((YBoule-larg_balle <= yBrique+hauteurBrique/2  && YBoule-larg_balle > -0.1+yBrique-hauteurBrique/2 )) && !occupied1 ) // Si la balle est au niveau de la case
            {
                // Teste au niveau de l'axe des abscisses

                if((XBoule+larg_balle >= 0.1+xBrique-longueurBrique/2 && XBoule-larg_balle <=-0.1+ xBrique+longueurBrique/2) )
                {
                    i=i+1;
                    if(i%2!=0){
                        m_Brique[j]->setTouched(true);
                        m_Brique[j]->briqueTouched();
                        Ydir=Ydir * -1;
                        joueur_.score();
                    }
                }
            }
            if((XBoule+larg_balle >= xBrique-longueurBrique/2   && XBoule+larg_balle < 0.1+xBrique-longueurBrique/2 )|| ((XBoule-larg_balle <= xBrique+longueurBrique/2   && XBoule-larg_balle > -0.1+xBrique-longueurBrique/2 )) && !occupied2 ) // Si la balle est au niveau de la case
            {
                // Teste au niveau de l'axe des abscisses

                if((YBoule+larg_balle >= 0.1+yBrique-hauteurBrique/2 && YBoule-larg_balle <=-0.1+ yBrique+hauteurBrique/2) )
                {
                    y=y+1;
                    if(y%2!=0){
                        m_Brique[j]->setTouched(true);
                        m_Brique[j]->briqueTouched();
                        Xdir=Xdir * -1;
                        joueur_.score();
                    }
                }
            }
        }

    }


    XBoule=XBoule+Xdir;
    YBoule=YBoule+Ydir;

    return 1; // Fin de la fonction, tous s'est bine pass� !
}

void GLWidget::etatPartie()
{
    nbBoules_ = nbBoules_ - 1;
    if(nbBoules_>0)
    {
        start = false;
        playNextBoule();

        updateGL();


    }
    else
    {
            m_TexteAAfficher ="T'as perdu sale grosse merde";
            renderText(50, 500, m_TexteAAfficher);

            //QString("Objet selectionne : %1").arg(QString::fromStdString(planet->GetName()));
    }
}

void GLWidget::playNextBoule()
{
    setBarre(0.5,0.05,10,1);
    setBoule(0,-20.5);
    Xdir = 0.0;
    Ydir = 0.1;

}

// Fonction de redimensionnement
void GLWidget::resizeGL(int width, int height)
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
void GLWidget::paintGL()
{
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
    glColor3f(1,1,1);
    afficheFond();
    affiche_barre();
    QString score = joueur_.displayScore();
    renderText(30,30, score);
    gestionBoule(0.5);
}


// Fonction de gestion d'interactions clavier
void GLWidget::keyPressEvent(QKeyEvent * event)
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

    case Qt::Key_Space:
    {
        start = true;
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
        pause = !pause;
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
