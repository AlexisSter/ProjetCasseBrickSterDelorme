#ifndef JOUEUR_H
#define JOUEUR_H
#include <QString>
#include <fstream>
#include <QList>


class Joueur
{
public:
    int score_;
    QString m_ScoreAAfficher = "";
    QList<int> listeScores;
    QList<QString> listeNoms;

    Joueur();
    void score();
    QString displayScore();
    void charger();
    void enregistrer();
private :

};

#endif // JOUEUR_H
