#ifndef JOUEUR_H
#define JOUEUR_H
#include <QString>

class Joueur
{
public:
    int score_;
    QString m_ScoreAAfficher = "";

    Joueur();
    void score();
    QString displayScore();

private :

};

#endif // JOUEUR_H
