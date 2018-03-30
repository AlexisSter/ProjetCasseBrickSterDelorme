#include "joueur.h"
#include "myglwidget.h"
#include <fstream>
#include<QDir>
#include<QInputDialog>
#include<qDebug>
#include<QLineEdit>
using namespace std;

Joueur::Joueur()
{
    score_ = 0;
    nomJoueur = "";
}

void Joueur::score()
{
    score_ = score_ +10;
}

QString Joueur::displayScore()
{
    m_ScoreAAfficher = QString::number(score_);
    return m_ScoreAAfficher;
}


void Joueur::enregistrer()
{
    ofstream os;
    os.open("Score.txt");
    listeScores.push_back(score_);
    os << listeScores[0];
    os.close();
}

void Joueur::charger()
{
    QString texte;
       QFile fichier("Score.txt");

       if(fichier.open(QIODevice::ReadOnly | QIODevice::Text))
       {
            texte = fichier.readAll();
            fichier.close();
       }
       else texte = "Impossible d'ouvrir le fichier !";
    qDebug() << texte;
}
