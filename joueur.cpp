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

void Joueur::setNomJoueur(QString text)
{
     listeNoms.push_back(text);
     qDebug() << listeNoms[0];
}

void Joueur::enregistrer()
{
    ofstream os;
    os.open("Score.txt");
    os << "Bonjour";
    os.close();

}
