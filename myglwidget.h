#ifndef MYGLWIDGET_H
#define MYGLWIDGET_H

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

    void affiche_barre(float hauteur);
    void mouseMoveEvent(QMouseEvent *event);
    QPoint gestion_barre(float largeur);
    void drawBoule(float x, float y, float radius);
    int gestionBoule(float x_barre, float larg_barre, float larg_balle);

private:
    // Quelques variables a definir
    // changer de primitive
    bool briqueAlive_;
    //coordonnées
    float xBarre_;
    float yBarre_;
    float longueurBarre_;
    QPoint oldPosition_;
    bool start;
    QTimer m_AnimationTimer;
    float m_TimeElapsed { 0.0f };

};

#endif // MYGLWIDGET_H
