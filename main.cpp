#include "mainwindow.h"

#include <QApplication>
#include<QtSql>
#include <QDebug>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    MainWindow w;
    w.show();

    int result = a.exec();

    // Close the database after the event loop ends
    if (MainWindow::db.isOpen()) {
        MainWindow::db.close();
        qDebug() << "Database connection closed in main.";
    }
    QSqlDatabase::removeDatabase(QSqlDatabase::defaultConnection);

    return result;
}
