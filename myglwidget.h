#ifndef MYGLWIDGET_H
#define MYGLWIDGET_H

#include <QGLWidget>
#include <QKeyEvent>
#include <QColor>
#include <QPoint>
#include <QVector2D>
#include"GL/gl.h"

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

    void glTranslatefR();
    void glTranslatefL();
    void glTranslatefB();
    void glTranslatefH();
    void affiche_barre(float hauteur);
    void mouseMoveEvent(QMouseEvent *event);
    QPoint gestion_barre(float largeur);
    void drawBoule(float x, float y, float radius);
    int gestionBoule(float x_barre, float larg_barre, float larg_balle);

private:
    // Quelques variables a definir
    // variable couleur primitive
    float red;
    float blue;
    float green;
    // couleur fond
    float redBackground;
    float blueBackground;
    float greenBackground;
    // changer de primitive
    bool briqueAlive_;
    //cacher la primitive
    bool hide;
    //coordonnées
    GLfloat x = 0.5;
    GLfloat y = 0.5;
    GLfloat rotate  = 0;
    float xBarre_;
    float yBarre_;
    float longueurBarre_;
    QPoint oldPosition_;
    bool start;
};

#endif // MYGLWIDGET_H
