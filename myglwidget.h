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
class MyGLWidget : public QGLWidget
{
    Q_OBJECT

public:

    // Constructeur
    MyGLWidget(QWidget * parent = nullptr);

protected:

    // Fonction d'initialisation
    void initializeGL();

    // Fonction de redimensionnement
    void resizeGL(int width, int height);

    // Fonction d'affichage
    void paintGL();

    // Fonction de gestion d'interactions clavier
    void keyPressEvent(QKeyEvent * event);

    void affiche_barre();
    void mouseMoveEvent(QMouseEvent *event);
    void placerBrique(int n);
    QPoint gestion_barre(float largeur);
    void drawBoule(float radius);
    int gestionBoule( float larg_balle);
    void setBoule(float x, float y){XBoule = x; YBoule = y;}
    void setBarre(float x, float y, float longueur, float hauteur){xBarre_ = x, yBarre_ = y, longueurBarre_ = longueur, hauteurBarre_ = hauteur;}
    void etatPartie(); //vérifie le nombre de boules
    void playNextBoule(); // réinitialise la plateau pour la boule suivante
    void afficheFond();

private:
    // Quelques variables a definir
    // changer de primitive
    Joueur joueur_;
    std::vector<Brique *> m_Brique;
    bool briqueAlive_;
    //coordonnées
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
    QImage imageBarre;
    bool pause;
    int nbBoules_;
    int score_;
    QString m_TexteAAfficher;



};

#endif // MYGLWIDGET_H
