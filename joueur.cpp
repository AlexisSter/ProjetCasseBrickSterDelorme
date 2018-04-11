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
    for(int i = 0; i<listeScores.size(); i++)
    {
        qDebug() << listeScores[i];
        os << listeScores[i]<<";";
    }
    os.close();
}

void Joueur::charger()
{
    QFile fichier("Score.txt");
    QString texte;
    if(fichier.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        QStringList nb;
        QTextStream flux(&fichier);

        texte = flux.readLine();
        nb = texte.split(";");
        for(int i=0; i<nb.size();i++)
        {
            listeScores.push_back(nb[i].toInt());
        }

        fichier.close();
    }
    else texte = "Impossible d'ouvrir le fichier !";
}

void Joueur::checkTop()
{
    charger();
    for(int i = 0; i<listeScores.size(); i++)
    {
        if(score_ > listeScores.at(i))
        {
            listeScores.insert(i, score_);
            i = listeScores.size();
            listeScores.pop_back();
        }

    }

    enregistrer();
}
