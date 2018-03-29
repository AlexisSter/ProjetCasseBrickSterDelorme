#include "joueur.h"
#include "myglwidget.h"

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
