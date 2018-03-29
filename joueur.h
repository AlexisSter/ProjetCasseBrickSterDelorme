#ifndef JOUEUR_H
#define JOUEUR_H
#include <QString>
#include <fstream>
class Joueur
{
public:
    int score_;
    QString m_ScoreAAfficher = "";

    Joueur();
    void score();
    QString displayScore();
    void charger();
    void enregistrer();
private :
    std::vector<Brique *> nomJoueurs;
    std::vector<Brique *> scoreJoueurs;

};

#endif // JOUEUR_H
