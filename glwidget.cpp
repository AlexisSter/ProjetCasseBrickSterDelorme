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
#include<QDir>
#include<QInputDialog>
#include<QLineEdit>
#include<QList>
#include<QMessageBox>

// Declarations des constantes
const unsigned int WIN_WIDTH  = 1000;
const unsigned int WIN_HEIGHT = 500;
const float ASPECT_RATIO      = 0.4f;
const float ORTHO_DIM         = 50.0f;

const float MAX_DIMENSION     = 50.0f;
int a=0;


// Constructeur
GLWidget::GLWidget(QWidget * parent) : QGLWidget(parent)
{
    // Reglage de la taille/position
    //setFixedSize(WIN_WIDTH, WIN_HEIGHT);
    //move(QApplication::desktop()->screen()->rect().center() - rect().center());
    initializeGL();
    // Connexion du timer
    pause = false;
    start = false;
    joueur_.checkTop();
    un = joueur_.numero1();
    deux = joueur_.numero2();
    trois = joueur_.numero3();
    quatre = joueur_.numero4();
    cinq = joueur_.numero5();
    six = joueur_.numero6();
    sept = joueur_.numero7();
    huit = joueur_.numero8();
    neuf = joueur_.numero9();
    dix = joueur_.numero10();


    connect(&m_AnimationTimer,  &QTimer::timeout, [&] {


        if(start)
        {
            if(nBouleRestante>=nbBoules_) nBouleRestante--;
            if(!pause)
            {
                //m_TimeElapsed += 0.01f; // 12.0f;
                updateGL();



            }
        }

    });

    m_AnimationTimer.setInterval(1);
    m_AnimationTimer.start();
    briqueAlive_ = true;

    xBarre_ = 0.0;
    yBarre_ = 0.05;
    longueurBarre_ = 10;
    hauteurBarre_ = 1;
    Xdir = 0.0;
    Ydir = 0.3;
    place =false;
    occupied1 = false;
    occupied2 = false;

    XBoule = 0;
    YBoule = -18.5;
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
            QString path ="C:/Users/Alexis/Documents/ProjetCasseBrickSterDelorme/ProjetCasseBrickSterDelorme";
            QImage qim_Texture1 = QGLWidget::convertToGLFormat(QImage(path + "/texture10.png"));
            QImage qim_Texture2 = QGLWidget::convertToGLFormat(QImage(path + "/textureFond.jpg"));
            QImage qim_Texture3 = QGLWidget::convertToGLFormat(QImage(path + "/textureBoule.png"));
            QImage qim_Texture4 = QGLWidget::convertToGLFormat(QImage(path + "/texture12.png"));
            QImage qim_TextureFin = QGLWidget::convertToGLFormat(QImage(path + "/textureFondFin.jpg"));
            QImage qim_TextureWin = QGLWidget::convertToGLFormat(QImage(path + "/textureFondWin.jpg"));
            GLuint* m_TextureID = new GLuint[6];
            glGenTextures( 6, m_TextureID );
            m_texture=m_TextureID[0];
            image=qim_Texture1;
            m_textureFond=m_TextureID[1];
            imageFond=qim_Texture2;
            m_textureBoule=m_TextureID[2];
            imageBoule=qim_Texture3;
            m_textureBarre=m_TextureID[3];
            imageBarre=qim_Texture4;
            m_textureFin=m_TextureID[4];
            imageFin=qim_TextureFin;
            m_textureWin=m_TextureID[5];
            imageWin=qim_TextureWin;
            placerBrique(2,-5,10);
            //placerBrique(120,-45,18.30);

            //placerTSE();
            place=true;

        }
    }
}

void GLWidget::placerBrique(int n,float x, float y){


    float xStart = x ;
    float yStart = y;
    float pas = 0;
    float largeur =10;
    float hauteur = 3.33;
    int t=0;

    //


    for(int i=0; i<n;i++){
        if(xStart+(i-t)*pas+(i-t)*largeur+largeur>55) {
            t=i;

            yStart = yStart - hauteur;

        }

        Brique *briquei = new Brique(xStart+(i-t)*pas+(i-t)*largeur, yStart, -1, largeur,hauteur,5,m_texture,image);
        int hp = briquei->getHpBrique();
        if(hp == 0)
        {
            briquei->setColor(255,0,0);
        }
        else
        {
            briquei->setColor(0,0,255);
        }

        m_Brique.push_back(briquei);
    }
}
void GLWidget::placerTSE(){

    int n=7;
    float xStart = -40.5 ;
    float yStart = 10;
    float pas = 0;
    float largeur =10;
    float hauteur = 3.33;
    int t=0;
    int save=7;
    int h=10;

    //

    //T
    for(int i=0; i<28;i++){
        if(i<=2) {

            Brique *briquei = new Brique(xStart+(i-t)*pas+(i-t)*largeur, yStart, -1, largeur,hauteur,1,m_texture,image);
            briquei->setColor(0,0,255);
            m_Brique.push_back(briquei);


        }
        else if(i>2 && i<7){
            t=i;

            yStart = yStart - hauteur;
            Brique *briquei = new Brique(10+xStart+(i-t)*pas+(i-t)*largeur, yStart, -1, largeur,hauteur,1,m_texture,image);
            briquei->setColor(0,0,255);
            m_Brique.push_back(briquei);
        }
        else if(i>=7 && i<=9){
            t=7;

            yStart=10;
            Brique *briquei = new Brique(30+xStart+(i-t)*pas+(i-t)*largeur, yStart, -1, largeur,hauteur,1,m_texture,image);
            briquei->setColor(0,255,0);
            m_Brique.push_back(briquei);

        }
        else if(i>9 && i<=10){


            yStart = yStart - hauteur;
            Brique *briquei = new Brique(30+xStart+(i-h)*pas+(i-h)*largeur, yStart, -1, largeur,hauteur,1,m_texture,image);
            briquei->setColor(0,255,0);
            m_Brique.push_back(briquei);
            h++;

        }
        else if(i>10 && i<=13){

            if(i==11){
                yStart = yStart - hauteur;
                h=11;


            }

            Brique *briquei = new Brique(30+xStart+(i-h)*pas+(i-h)*largeur, yStart, -1, largeur,hauteur,1,m_texture,image);
            briquei->setColor(0,255,0);
            m_Brique.push_back(briquei);


        }
        else if(i>13 && i<=14){


            yStart = yStart - hauteur;
            h=14;




            Brique *briquei = new Brique(50+xStart+(i-h)*pas+(i-h)*largeur, yStart, -1, largeur,hauteur,1,m_texture,image);
            briquei->setColor(0,255,0);
            m_Brique.push_back(briquei);


        }
        else if(i>14 && i<=17 ){

            if(i==15){
                yStart = yStart - hauteur;
                h=15;


            }

            Brique *briquei = new Brique(30+xStart+(i-h)*pas+(i-h)*largeur, yStart, -1, largeur,hauteur,1,m_texture,image);
            briquei->setColor(0,255,0);
            m_Brique.push_back(briquei);


        }
        else if(i>17 && i<=20 ){

            yStart=10;
            h=18;

            Brique *briquei = new Brique(60+xStart+(i-h)*pas+(i-h)*largeur, yStart, -1, largeur,hauteur,1,m_texture,image);
            briquei->setColor(255,0,0);
            m_Brique.push_back(briquei);


        }
        else if(i>20 && i<=21 ){


            yStart = yStart - hauteur;
            h=21;




            Brique *briquei = new Brique(60+xStart+(i-h)*pas+(i-h)*largeur, yStart, -1, largeur,hauteur,1,m_texture,image);
            briquei->setColor(255,0,0);
            m_Brique.push_back(briquei);


        }
        else if(i>21 && i<=23 ){

            if(i==22){
                yStart = yStart - hauteur;
                h=22;


            }

            Brique *briquei = new Brique(60+xStart+(i-h)*pas+(i-h)*largeur, yStart, -1, largeur,hauteur,1,m_texture,image);
            briquei->setColor(255,0,0);
            m_Brique.push_back(briquei);


        }
        else if(i>23 && i<=24 ){


            yStart = yStart - hauteur;
            h=24;




            Brique *briquei = new Brique(60+xStart+(i-h)*pas+(i-h)*largeur, yStart, -1, largeur,hauteur,1,m_texture,image);
            briquei->setColor(255,0,0);
            m_Brique.push_back(briquei);


        }
        else if(i>24 ){

            if(i==25){
                yStart = yStart - hauteur;
                h=25;


            }

            Brique *briquei = new Brique(60+xStart+(i-h)*pas+(i-h)*largeur, yStart, -1, largeur,hauteur,1,m_texture,image);
            briquei->setColor(255,0,0);
            m_Brique.push_back(briquei);


        }
    }
}
void GLWidget::afficheFond(GLuint a, QImage b){
    glBindTexture( GL_TEXTURE_2D, a);
    glTexImage2D( GL_TEXTURE_2D, 0, 4, b.width(), b.height(), 0, GL_RGBA, GL_UNSIGNED_BYTE, b.bits() );
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    glBegin(GL_QUADS); // Primitive à afficher et début de la déclaration des vertices de cette primitive
    //face avant

    glTexCoord2f(0, 0);glVertex3f(-50,-25,-7);  // Définition des coordonnées des sommets (en 2D, z=0) OK
    glTexCoord2f(1, 0);glVertex3f(50,-25,-7);
    glTexCoord2f(1, 1);glVertex3f(50,25,-7);
    glTexCoord2f(0, 1);glVertex3f(-50,25,-7);

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
    glColor3f(0,0,0);
    glTexCoord2f(0, 1);glVertex3f(xBarre_ - longueurBarre_ / 2,-20 + hauteurBarre_,-1);  // Définition des coordonnées des sommets (en 2D, z=0) OK
    glTexCoord2f(1, 1);glVertex3f(xBarre_ + longueurBarre_/ 2 , -20+hauteurBarre_,-1);
    glTexCoord2f(1, 0);glVertex3f(xBarre_ + longueurBarre_ / 2, -20,-1);
    glTexCoord2f(0, 0);glVertex3f(xBarre_ - longueurBarre_ / 2, -20, -1);
    //face arrière
    glVertex3f(xBarre_ - longueurBarre_ / 2, -20,-3);  // Définition des coordonnées des sommets (en 2D, z=0) OK
    glVertex3f(xBarre_ + longueurBarre_ / 2 , -20,-3);
    glVertex3f(xBarre_ + longueurBarre_ / 2, -20+ hauteurBarre_,-3);
    glVertex3f(xBarre_ - longueurBarre_ / 2, -20+ hauteurBarre_,-3);
    //face dessous
    glVertex3f(xBarre_ - longueurBarre_ / 2, -20,-1);  // Définition des coordonnées des sommets (en 2D, z=0)OK
    glVertex3f(xBarre_ - longueurBarre_ / 2 , -20,-3);
    glVertex3f(xBarre_ + longueurBarre_ / 2, -20,-1);
    glVertex3f(xBarre_ + longueurBarre_ / 2, -20,-3);
    //face dessus
    glVertex3f(xBarre_ - longueurBarre_ / 2, -20 + hauteurBarre_,-1);  // Définition des coordonnées des sommets (en 2D, z=0)OK
    glVertex3f(xBarre_ - longueurBarre_ / 2 , -20 + hauteurBarre_ ,-3);
    glVertex3f(xBarre_ + longueurBarre_ / 2, -20 + hauteurBarre_,-1);
    glVertex3f(xBarre_ + longueurBarre_ / 2, -20 + hauteurBarre_,- 3);
    //face droite
    glVertex3f(xBarre_ + longueurBarre_ / 2, -20 + hauteurBarre_ ,-1);  // Définition des coordonnées des sommets (en 2D, z=0)
    glVertex3f(xBarre_ + longueurBarre_ / 2 , -20 + hauteurBarre_,-3);
    glVertex3f(xBarre_ + longueurBarre_ / 2,  - 20,-1);
    glVertex3f(xBarre_ + longueurBarre_ / 2, -20,-3);
    //face gauche
    glVertex3f(xBarre_ - longueurBarre_ / 2, -20+ hauteurBarre_ ,-1);  // Définition des coordonnées des sommets (en 2D, z=0)
    glVertex3f(xBarre_ - longueurBarre_ / 2 ,-20 + hauteurBarre_ ,-3);
    glVertex3f(xBarre_ - longueurBarre_ / 2, -20,-1);
    glVertex3f(xBarre_ - longueurBarre_ / 2, -20,-3);
    glEnd();

}
void GLWidget::mouseMoveEvent(QMouseEvent *event)
{

    if(start)
    {
        this->setMouseTracking(true);
        QPoint positionSouris = event->pos();
        QString message = "x : " + QString::number(positionSouris.x()) + " - y : " + QString::number(positionSouris.y())+ " - xbarre : " + QString::number(xBarre_);
        xBarre_ =-50+ positionSouris.x() /10;
    }
    event->accept();

}

void GLWidget::drawBoule(float radius)
{
    glColor3f(0.5,0.5,0.5);
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
    etatVictoire();
    drawBoule(larg_balle);

    // Avance la balle
    // Gère les rebonds

    if((XBoule+larg_balle/2)>50)  Xdir*=-1;
    if((XBoule-larg_balle/2)<-50) Xdir*=-1;
    if((YBoule+larg_balle/2)>19.5)  Ydir*=-1;
    if((YBoule-larg_balle/2)<-20)
    {
        etatPartie();
    }

    // Teste les collisions entre la boule et la barre
    if((YBoule-larg_balle/2<=-20+hauteurBarre_)) // Si la balle est au niveau de la barre
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
            if((XBoule+larg_balle >= xBrique-longueurBrique/2   && XBoule+larg_balle <= 0.5+xBrique-longueurBrique/2 )|| ((XBoule-larg_balle <= xBrique+longueurBrique/2   && XBoule-larg_balle >= -0.5+xBrique-longueurBrique/2 )) && !occupied2 ) // Si la balle est au niveau de la case
            {
                // Teste au niveau de l'axe des abscisses

                if((YBoule+larg_balle >= 0.3+yBrique-hauteurBrique/2 && YBoule-larg_balle <-0.3+ yBrique+hauteurBrique/2) )
                {
                    occupied1=true;
                    y=y+1;
                    if(y%2!=0){
                        int hp = m_Brique[j]->getHpBrique();
                        if(hp == 1)
                        {
                            m_Brique[j]->setHpBrique(0);
                            m_Brique[j]->setColor(255,0,0);
                            Xdir=Xdir * -1;
                            joueur_.score();
                        }
                        else
                        {
                            m_Brique[j]->setTouched(true);
                            m_Brique[j]->briqueTouched();
                            Xdir=Xdir * -1;
                            joueur_.score();
                        }
                    }
                }
                if((YBoule+larg_balle >= yBrique-hauteurBrique/2  && YBoule+larg_balle <=0.5+ yBrique-hauteurBrique/2 )|| ((YBoule-larg_balle <= yBrique+hauteurBrique/2  && YBoule-larg_balle >= -0.5+yBrique-hauteurBrique/2 )) && !occupied1 ) // Si la balle est au niveau de la case
                {
                    // Teste au niveau de l'axe des abscisses

                    if((XBoule+larg_balle >= 0.1+xBrique-longueurBrique/2 && XBoule-larg_balle <=-0.1+ xBrique+longueurBrique/2) )
                    {
                        occupied2=true;
                        i=i+1;
                        if(i%2!=0){
                            int hp = m_Brique[j]->getHpBrique();
                            if(hp == 1)
                            {
                                m_Brique[j]->setHpBrique(0);
                                m_Brique[j]->setColor(255,0,0);
                                Ydir=Ydir * -1;
                                joueur_.score();
                            }
                            else
                            {
                                m_Brique[j]->setTouched(true);
                                m_Brique[j]->briqueTouched();
                                Ydir=Ydir * -1;
                                joueur_.score();
                            }
                        }
                    }
                }

            }
        }

    }


    XBoule=XBoule+Xdir;
    YBoule=YBoule+Ydir;
    occupied1=false;
    occupied2=false;


    return 1; // Fin de la fonction, tous s'est bine pass� !
}
void GLWidget::etatVictoire(){
    int n=0;

    for(int i=0;i<m_Brique.size();i++){
        if(m_Brique[i]->getTouched()==true){
            n=n+1;
        }
    }
    if(n==m_Brique.size()){
        niveau=niveau+1;
        if(niveau==3){
            start=false;
            placerTSE();
            playNextBoule();
            updateGL();
        }
        else if(niveau<3){
            start=false;
            placerBrique(40,-34,16);

            playNextBoule();
            updateGL();
        }
        else{
            niveau=3;

            joueur_.setNomJoueur(nomJoueur);
            joueur_.checkTop();
            un = joueur_.numero1();
            deux = joueur_.numero2();
            trois = joueur_.numero3();
            quatre = joueur_.numero4();
            cinq = joueur_.numero5();
            six = joueur_.numero6();
            sept = joueur_.numero7();
            huit = joueur_.numero8();
            neuf = joueur_.numero9();
            dix = joueur_.numero10();

            start=false;

            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
            glMatrixMode(GL_PROJECTION);
            glLoadIdentity();
            glOrtho(-MAX_DIMENSION, MAX_DIMENSION, -MAX_DIMENSION * ASPECT_RATIO, MAX_DIMENSION * ASPECT_RATIO, -MAX_DIMENSION * 2.0f, MAX_DIMENSION * 2.0f);
            glMatrixMode(GL_MODELVIEW);
            glLoadIdentity();

            glMatrixMode(GL_MODELVIEW);
            glLoadIdentity();

            gluLookAt(0,0,5,0,0,0,0,1,0);
            //gluLookAt(10,2,5,0,0,0,0,1,0);
            glColor3f(1,1,1);
            afficheFond(m_textureWin,imageWin);
        }
    }


}

void GLWidget::etatPartie()
{
    if(start){
        nbBoules_ = nbBoules_ - 1;
        if(nbBoules_>0)
        {
            start = false;
            playNextBoule();
            updateGL();
        }
        else
        {
            m_TexteAAfficher ="You loose try again !";
            //renderText(480, 300, m_TexteAAfficher);
            bool ok;

            //imageFond=imageFin;
            //m_textureFond=m_textureFin;
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
            glMatrixMode(GL_PROJECTION);
            glLoadIdentity();
            glOrtho(-MAX_DIMENSION, MAX_DIMENSION, -MAX_DIMENSION * ASPECT_RATIO, MAX_DIMENSION * ASPECT_RATIO, -MAX_DIMENSION * 2.0f, MAX_DIMENSION * 2.0f);
            glMatrixMode(GL_MODELVIEW);
            glLoadIdentity();

            glMatrixMode(GL_MODELVIEW);
            glLoadIdentity();

            gluLookAt(0,0,5,0,0,0,0,1,0);
            //gluLookAt(10,2,5,0,0,0,0,1,0);
            glColor3f(1,1,1);
            afficheFond(m_textureFin,imageFin);

            score = joueur_.displayScore();




            /*QString text = QInputDialog::getText(this, tr("QInputDialog::getText()"),
                                                 tr("User name:"), QLineEdit::Normal,
                                                 QDir::home().dirName(), &ok);
            if (ok && !text.isEmpty())
                joueur_.getName(text.toStdString());*/

            start = false;
            pause = true;
            joueur_.setNomJoueur(nomJoueur);
            joueur_.checkTop();
            un = joueur_.numero1();
            deux = joueur_.numero2();
            trois = joueur_.numero3();
            quatre = joueur_.numero4();
            cinq = joueur_.numero5();
            six = joueur_.numero6();
            sept = joueur_.numero7();
            huit = joueur_.numero8();
            neuf = joueur_.numero9();
            dix = joueur_.numero10();



            //QMessageBox msgBox;
            //msgBox.setText("Tableau des scores !");
            //msgBox.setInformativeText("Un : " + un + "\n" +"Deux : " + deux + "\n" +"Trois : " + trois + "\n" +"Quatre : " + quatre + "\n" +"Cinq : " + cinq + "\n" +"Six : " + six + "\n" +"Sept : " + sept + "\n" +"Huit : " + huit + "\n" +"Neuf : " + neuf + "\n" +"Dix : " + dix);
            //msgBox.setStandardButtons(QMessageBox::Ok);
            //msgBox.setDefaultButton(QMessageBox::Ok);
            //int ret = msgBox.exec();
            //switch (ret) {
            //case QMessageBox::Ok:
            // Save was clicked
            //close();
            //}
            /*QList<int> score = joueur_.displayTop();
            for(int i=0; i<score.size();i++)
            {
                renderText(30,30+10*i,i + " : " + score.at(i));
            }*/
            //QString("Objet selectionne : %1").arg(QString::fromStdString(planet->GetName()));
        }
    }
}

void GLWidget::playNextBoule()
{
    setBarre(0.5,0.05,10,1);
    setBoule(0,-18.5);
    Xdir = 0.0;
    Ydir = 0.3;
    updateGL();

}

// Fonction de redimensionnement
void GLWidget::resizeGL(int width, int height)
{
    // Definition du viewport (zone d'affichage)
    glViewport(0,0,1000,500);
    // Definition de la matrice de projection
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-ORTHO_DIM * ASPECT_RATIO, ORTHO_DIM * ASPECT_RATIO, -ORTHO_DIM, ORTHO_DIM, -2.0f * ORTHO_DIM, 2.0f * ORTHO_DIM);

    // Definition de la matrice de modele
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void GLWidget::setXbarre(int x){
    if(start){

        if(x>1) pas = 1;
        else if(x<-1) pas=-1;
        else if ((x>0.1 && x<=1) ||(x<-0.1  && x>=-1)) pas=x;
        else if(x==0)pas=0;


    }




}
// Fonction d'affichage
void GLWidget::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Definition de la position de la camera
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-MAX_DIMENSION, MAX_DIMENSION, -MAX_DIMENSION * ASPECT_RATIO, MAX_DIMENSION * ASPECT_RATIO, -MAX_DIMENSION * 2.0f, MAX_DIMENSION * 2.0f);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(0,0,5,0,0,0,0,1,0);
    //gluLookAt(10,2,5,0,0,0,0,1,0);

    for ( int i = 0; i<m_Brique.size();i++){
        m_Brique[i]->Display(m_TimeElapsed);
    }

    if((xBarre_ -4 )<=-48){
        xBarre_=-44;

    }
    if((xBarre_+4) >=49 ){
        xBarre_=45;
        bordDroit=true;


    }
    if((pas<0 && bordDroit==true) || (pas>0 && bordGauche==true)){
        bordDroit = false;
        bordGauche= false;

        xBarre_=xBarre_ + pas;
    }
    if(!bordDroit && !bordGauche) xBarre_=xBarre_ + pas;


    if(pas<0){

    }

    glColor3f(1,1,1);

    //afficheFond(m_textureFin,imageFin);
    afficheFond(m_textureFond, imageFond);

    affiche_barre();
    score = joueur_.displayScore();
    //renderText(30,100, score);
    gestionBoule(0.5);

}
void GLWidget::wheelEvent(QWheelEvent * event)
{
    if(!start){
        if(event->delta() > 0)
        {
            if (longueurBarre_ < 30)
            {
                xBarre_ = 0.0;
                longueurBarre_ = longueurBarre_ + 1;
                YBoule = YBoule -Ydir;
                updateGL();
            }
        }
        else
        {
            if (longueurBarre_ > 5)
            {
                xBarre_ = 0.0;
                longueurBarre_ = longueurBarre_ - 1;
                YBoule = YBoule -Ydir;
                updateGL();
            }
        }
        event->accept();
    }
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
void GLWidget::setPause(bool pause_){
    pause=pause_;
}
void GLWidget::setStart(bool start_){
    start=start_;
}
