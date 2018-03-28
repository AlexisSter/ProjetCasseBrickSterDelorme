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

private:
    // Quelques variables a definir
    // changer de primitive
    std::vector<Brique *> m_Brique;
    bool briqueAlive_;
    //coordonnées
    float XBoule=0;
    float YBoule=0;
    float xBarre_;
    float yBarre_;
    float longueurBarre_;
    float hauteurBarre_;
    float Xdir;
    float Ydir;
    QPoint oldPosition_;
    bool start;
    QTimer m_AnimationTimer;
    float m_TimeElapsed { 0.0f };


};

#endif // MYGLWIDGET_H
