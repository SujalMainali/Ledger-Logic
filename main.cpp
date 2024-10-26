#include "mainwindow.h"

#include <QApplication>
#include<QtSql>
#include <QDebug>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow * w= new MainWindow();
    w->showMaximized();
    return a.exec();
}
