#ifndef MYGLWIDGET_H
#define MYGLWIDGET_H

#include "brique.h"
#include <QGLWidget>
#include <QKeyEvent>
#include <QColor>
#include <QPoint>
#include <QVector2D>
#include"GL/gl.h"
#include <QTimer>
#include <QTextEdit>
#include "joueur.h"



// Classe dediee a l'affichage d'une scene OpenGL
class GLWidget : public QGLWidget
{
    Q_OBJECT

public:
    explicit GLWidget(QWidget *parent = 0);
    void setXbarre(int x);
    void setPause(bool pause_);
    void setStart(bool start_);
    string getNomJoueur() {return nomJoueur;}
    void setNomJoueur(string a) {nomJoueur=a;}
    QString getNbBoule() {return QString::number(nBouleRestante);}
    QString getNiveau() {return QString::number(niveau);}
    //Récupère les 10 meilleurs scores
    QString getUn() {return un;}
    QString getDeux() {return deux;}
    QString getTrois() {return trois;}
    QString getQuatre() {return quatre;}
    QString getCinq() {return cinq;}
    QString getSix() {return six;}
    QString getSept() {return sept;}
    QString getHuit() {return huit;}
    QString getNeuf() {return neuf;}
    QString getDix() {return dix;}
    QString getScore() {return score;}
protected:

    // Fonction d'initialisation
    void initializeGL();
    // Fonction de redimensionnement
    void resizeGL(int width, int height);
    // Fonction d'affichage
    void paintGL();
    // Fonction de gestion d'interactions clavier, souris
    void keyPressEvent(QKeyEvent * event);    
    void mouseMoveEvent(QMouseEvent *event);
    void wheelEvent(QWheelEvent * event);
    //Affiche le palet
    void affiche_barre();
    //Niveau 1 et 2 du jeu
    void placerBrique(int n,float x,float y);
    //Niveau 3 (TSE)
    void placerTSE();
    //Affichage de la boule
    void drawBoule(float radius);
    //Gère le déplacement (vitesse, direction) en fonction des collisions sur les murs, briques et le palets
    int gestionBoule( float larg_balle);
    setBoule(float x, float y){XBoule = x; YBoule = y;}
    setBarre(float x, float y, float longueur, float hauteur){xBarre_ = x, yBarre_ = y, longueurBarre_ = longueur, hauteurBarre_ = hauteur;}
    void etatPartie(); //vérifie le nombre de boules
    void etatVictoire();
    void playNextBoule(); // réinitialise la plateau pour la boule suivante
    void afficheFond(GLuint a, QImage b);



private:
    //Déclaration d'un joueur
    Joueur joueur_;
    string nomJoueur;
    //Appel de la classe brique, c'est un pointeur
    std::vector<Brique *> m_Brique;
    bool briqueAlive_;
    //Sert à bouger le palet avec la camera
    int pas;
    int nBouleRestante = 3;
    QString score;
    bool bordDroit=false;
    bool bordGauche=false;
    int niveau=1;
    float XBoule;
    float YBoule;
    //Coordonnées du palet, taille
    float xBarre_;
    float yBarre_;
    float longueurBarre_;
    float hauteurBarre_;
    //Incrément des coordonnées de la balle, c'est ce qui donne la vitesse et la direction
    float Xdir;
    float Ydir;
    //Début de la partie
    bool start;
    //Détection des collisions des bords
    bool occupied1;
    bool occupied2;
    bool etatJeu;
    QTimer m_AnimationTimer;
    float m_TimeElapsed { 0.0f };
    bool place;
    //Textures
    GLuint m_texture;
    QImage image;
    GLuint m_textureFond;
    QImage imageFond;
    GLuint m_textureBoule;
    QImage imageBoule;
    GLuint m_textureBarre;
    GLuint m_textureFin;
    GLuint m_textureWin;
    QImage imageWin;
    QImage imageBarre;
    QImage imageFin;
    bool pause;
    int nbBoules_;
    int score_;
    QString m_TexteAAfficher;
    QString un ="1" ;
    QString deux="2";
    QString trois="3";
    QString quatre="4";
    QString cinq="5";
    QString six="6";
    QString sept="7";
    QString huit="8";
    QString neuf="9";
    QString dix="10";



};

#endif // GLWIDGET_H
