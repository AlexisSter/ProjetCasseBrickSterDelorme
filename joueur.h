#ifndef JOUEUR_H
#define JOUEUR_H
#include <QString>
#include <QString>
#include <fstream>
#include <QList>
#include<iostream>
using namespace std;

class Joueur
{
public:
    int score_;
    //Affichage du score
    QString m_ScoreAAfficher = "";
    QList<int> listeScores;
    QList<QString> listeJoueur;
    QList<QString> listeNoms;
    string nomJoueur;

    Joueur();
    //Calcul le score du joueur
    void score();
    QString displayScore();
    //Chargement et enregistrement des 10 meilleurs scores/joueurs
    void charger();
    void enregistrer();
    //Verification si le score du joueur fait parti des 10 meilleurs
    void checkTop();
    //Affichage
    void displayTop();
    void getName(string name){nomJoueur=name;}
    void setNomJoueur(string a){nomJoueur=a;}
    //Avoir le score et nom des joueurs du top 10
    QString numero1();
    QString numero2();
    QString numero3();
    QString numero4();
    QString numero5();
    QString numero6();
    QString numero7();
    QString numero8();
    QString numero9();
    QString numero10();

private :

};

#endif // JOUEUR_H
