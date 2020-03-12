#include "mainwindow.h"
#include <QApplication>
#include <QDir>
#include <QStringList>
#include <cassert>
#include <iostream>
#include <vector>
void
copyIcon(QString home, QString icon)
{
    if (!QDir(home + "/.icons").exists()) {
        QDir().mkdir(home + "/.icons");
        QFile::copy(qgetenv("APPDIR") + "/" + icon, home + "/.icons/" + icon);
    } else {
        if (!QFile::exists(home + "/.icons/" + icon)) {
            QFile::copy(qgetenv("APPDIR") + "/" + icon,
                        home + "/.icons/" + icon);
        }
        return;
    }
}
int
main(int argc, char* argv[])
{
    QApplication a(argc, argv);
    MainWindow w;

    QString home = qgetenv("HOME");

    copyIcon(home, "FitTraining.png");
    w.show();
    return a.exec();
}
