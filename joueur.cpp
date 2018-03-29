#include "joueur.h"
#include "myglwidget.h"
#include <fstream>
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


void Joueur::charger(ifstream &is)
{
    int n;
    clear();
    is>>n;
    is.ignore();
    for (int i=0;i<n;i++)
    {
        Alarme a;
        a.charger(is);
        push_back(a);

    }

}

void Joueur::sauver(ofstream &os)
{
    os<<size()<<endl;
    for (iterator it=begin();it!=end();it++) it->sauver(os);

}

void Joueur::charger()
{
    ifstream os;
    os.open("Alarmes.txt");
    liste->charger(os);
    os.close();
}

void Joueur::enregistrer()
{
    ofstream os;
    os.open("Alarmes.txt");
    liste->sauver(os);
    os.close();
}
