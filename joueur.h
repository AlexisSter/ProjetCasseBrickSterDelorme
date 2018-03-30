#ifndef JOUEUR_H
#define JOUEUR_H
#include <QString>
#include <fstream>
#include <QList>
#include<iostream>
using namespace std;

class Joueur
{
public:
    int score_;
    QString m_ScoreAAfficher = "";
    QList<int> listeScores;
    QList<string> listeNoms;
    string nomJoueur;

    Joueur();
    void score();
    QString displayScore();
    void charger();
    void enregistrer();
    void topPlayer();
    void getName(string name){nomJoueur=name;}
private :

};

#endif // JOUEUR_H
