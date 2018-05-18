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
    QString m_ScoreAAfficher = "";
    QList<int> listeScores;
    QList<QString> listeJoueur;
    QList<QString> listeNoms;
    string nomJoueur;

    Joueur();
    void score();
    QString displayScore();
    void charger();
    void enregistrer();
    void topPlayer();
    void getName(string name){nomJoueur=name;}
    void checkTop();
    void displayTop();
    void setNomJoueur(string a){nomJoueur=a;}
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
