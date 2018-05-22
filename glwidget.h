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

    // Constructeur
    void setXbarre(int x);
    void setPause(bool pause_);
    void setStart(bool start_);
    string getNomJoueur() {return nomJoueur;}
    void setNomJoueur(string a) {nomJoueur=a;}
    QString getNbBoule() {return QString::number(nBouleRestante);}
    QString getNiveau() {return QString::number(niveau);}
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


    // Fonction de gestion d'interactions clavier
    void keyPressEvent(QKeyEvent * event);
    void wheelEvent(QScrollEvent *event);

    void affiche_barre();

    void mouseMoveEvent(QMouseEvent *event);
    void wheelEvent(QWheelEvent * event);
    void placerBrique(int n,int x,int y);
    void placerTSE();

    QPoint gestion_barre(float largeur);
    void drawBoule(float radius);
    int gestionBoule( float larg_balle);
    setBoule(float x, float y){XBoule = x; YBoule = y;}
    setBarre(float x, float y, float longueur, float hauteur){xBarre_ = x, yBarre_ = y, longueurBarre_ = longueur, hauteurBarre_ = hauteur;}
    void etatPartie(); //vérifie le nombre de boules
    void etatVictoire();
    void playNextBoule(); // réinitialise la plateau pour la boule suivante
    void afficheFond(GLuint a, QImage b);



private:
    // Quelques variables a definir
    // changer de primitive
    Joueur joueur_;
    string nomJoueur;

    std::vector<Brique *> m_Brique;
    bool briqueAlive_;
    //coordonnées
    int pas;
    QString score;
    bool bordDroit=false;
    bool bordGauche=false;
    int niveau=1;
    int nBouleRestante=3;
    float XBoule;
    float YBoule;
    float xBarre_;
    float yBarre_;
    float longueurBarre_;
    float hauteurBarre_;
    float Xdir;
    float Ydir;
    bool start;
    bool occupied1;
    bool occupied2;
    bool etatJeu;
    QTimer m_AnimationTimer;
    float m_TimeElapsed { 0.0f };
    bool place;
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
