#include "joueur.h"
#include "glwidget.h"
#include <fstream>
#include<QDir>
#include<QInputDialog>
#include<qDebug>
#include<QLineEdit>
#include<QMessageBox>
#include<iostream>
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
void Joueur::enregistrer()
{
    ofstream os;
    os.open("C:/Users/Alexis/Documents/ProjetCasseBrickSterDelorme/ProjetCasseBrickSterDelorme/Score.txt");
    for(int i = 0; i<10; i++)
    {
        os << listeScores.at(i);
        if(i != 9)
            os <<";";
    }
    os.close();
    ofstream os2;
    os2.open("C:/Users/Alexis/Documents/ProjetCasseBrickSterDelorme/ProjetCasseBrickSterDelorme/Joueur.txt");
    for(int i = 0; i<10; i++)
    {
        os2 << listeJoueur.at(i).toStdString();
        if(i != 9)
            os2 <<";";
    }
    os2.close();
}

void Joueur::charger()
{
    QFile fichier("C:/Users/Alexis/Documents/ProjetCasseBrickSterDelorme/ProjetCasseBrickSterDelorme/Score.txt");
    QFile fichier2("C:/Users/Alexis/Documents/ProjetCasseBrickSterDelorme/ProjetCasseBrickSterDelorme/Joueur.txt");
    QString texte;
    if(fichier.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        QStringList nb;
        QTextStream flux(&fichier);

        texte = flux.readLine();
        nb = texte.split(";");
        for(int i=0; i<10;i++)
        {
            listeScores.push_back(nb[i].toInt());
        }

        fichier.close();
    }
    else texte = "Impossible d'ouvrir le fichier !";
    QString texte2;
    if(fichier2.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        QStringList nb2;
        QTextStream flux2(&fichier2);

        texte2 = flux2.readLine();
        nb2 = texte2.split(";");
        for(int i=0; i<10;i++)
        {
            listeJoueur.push_back(nb2[i]);
        }

        fichier.close();
    }
    else texte = "Impossible d'ouvrir le fichier !";
}

void Joueur::checkTop()
{
    charger();

    for(int i = 0; i<10; i++)
    {
        if(score_ > listeScores.at(i))
        {
            listeScores.insert(i, score_);
            listeJoueur.insert(i,QString::fromStdString(nomJoueur));
            i = 10;
            listeScores.pop_back();
            listeJoueur.pop_back();

        }

    }

    enregistrer();
}


QString Joueur::numero1()
{
    string result="1-" +listeJoueur[0].toStdString()+" | "+ std::to_string(listeScores[0]);
    QString num = QString::fromStdString(result);
    return num;
}

QString Joueur::numero2()
{
    string result="2-" +listeJoueur[1].toStdString()+" | "+ std::to_string(listeScores[1]);
    QString num = QString::fromStdString(result);
    return num;
}

QString Joueur::numero3()
{
    string result="3-" +listeJoueur[2].toStdString()+" | "+ std::to_string(listeScores[2]);
    QString num = QString::fromStdString(result);
    return num;
}

QString Joueur::numero4()
{
    string result="4-" +listeJoueur[3].toStdString()+" | "+ std::to_string(listeScores[3]);
    QString num = QString::fromStdString(result);
    return num;
}

QString Joueur::numero5()
{
    string result="5-" +listeJoueur[4].toStdString()+" | "+ std::to_string(listeScores[4]);
    QString num = QString::fromStdString(result);
    return num;
}

QString Joueur::numero6()
{
    string result="6-" +listeJoueur[5].toStdString()+" | "+ std::to_string(listeScores[5]);
    QString num = QString::fromStdString(result);
    return num;
}

QString Joueur::numero7()
{
    string result="7-" +listeJoueur[6].toStdString()+" | "+ std::to_string(listeScores[6]);
    QString num = QString::fromStdString(result);
    return num;
}

QString Joueur::numero8()
{
    string result="8-" +listeJoueur[7].toStdString()+" | "+ std::to_string(listeScores[7]);
    QString num = QString::fromStdString(result);
    return num;
}

QString Joueur::numero9()
{
    string result="9-" +listeJoueur[8].toStdString()+" | "+ std::to_string(listeScores[8]);
    QString num = QString::fromStdString(result);
    return num;
}

QString Joueur::numero10()
{
    string result="10-" +listeJoueur[9].toStdString()+" | "+ std::to_string(listeScores[9]);
    QString num = QString::fromStdString(result);
    return num;
}
