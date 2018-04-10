#include <QApplication>
#include <ctime>
#include "mainwindow.h"

int main(int argc, char *argv[])
{
    // Initialisation du generateur de nombres aleatoires
    srand(time(nullptr));

    // Creation de l'application QT
    QApplication app(argc, argv);
    MainWindow w;
    w.show();

	// Creation du widget opengl

    // Execution de l'application QT
    return app.exec();
}
