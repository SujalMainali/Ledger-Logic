#ifndef FUNCTIONSDEFINITION_H
#define FUNCTIONSDEFINITION_H
#include "mainwindow.h"
#include <QVector>
#include <QtCharts>
#include<QtSql>
#include "chartofaccountwindow.h"
#include<QDebug>
#include "readpayment.h"
#include "create1.h"




void MainWindow::RetrieveDataForSalesGraph(QLineSeries *series) {
    QVector<QPointF> data;  // Vector to store (x, y) data

    QSqlDatabase db;
    db=ConnectDatabase();
    // Ensure the query is valid and can execute
    QSqlQuery query("SELECT transaction_date, total_amount FROM SalesTransactions");
    if (!query.exec()) {
        qDebug() << "Error: failed to execute query";
        db.close();
        return;
    }
    else{
        qDebug()<<"DatabaseConnectionOpened";
    }


    // Process the query results
    while (query.next()) {  // Iterate through the query results
        QDateTime dateTime = query.value(0).toDateTime();  // Retrieve data in DateTime format
        double money = query.value(1).toDouble();          // Retrieve amount in double

        // Append current entry (day and money) directly to the series
        series->append(dateTime.date().day(), money);  // Append to the series directly
    }

    // Close the SQLite connection after use
    db.close();
    qDebug()<<"DatabaseConnectionClosed";
}

void MainWindow::RetrieveDataForPurchaseGraph(QLineSeries *series) {
    QVector<QPointF> data;  // Vector to store (x, y) data

    QSqlDatabase db;
    db=ConnectDatabase();
    QSqlQuery query("SELECT transaction_date, total_amount FROM BillTransactions");
    if (!query.exec()) {
        qDebug() << "Error: failed to execute Purchase query";
        db.close();
        return;
    }
    else{
        qDebug()<<"DatabaseConnectionOpened";
    }


    // Process the query results
    while (query.next()) {  // Iterate through the query results
        QDateTime dateTime = query.value(0).toDateTime();  // Retrieve data in DateTime format
        double money = query.value(1).toDouble();          // Retrieve amount in double

        // Append current entry (day and money) directly to the series
        series->append(dateTime.date().day(), money);  // Append to the series directly
    }

    // Close the SQLite connection after use
    db.close();
    qDebug()<<"DatabaseConnectionClosed";
}


QSqlDatabase MainWindow::ConnectDatabase(){
    QString databasepath = QCoreApplication::applicationDirPath() + "/database/AccountingDetails.db";
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");  // SQLite database connection
    db.setDatabaseName(databasepath);  // Set the database file path

        if (!db.open()) {  // False if the database doesn't open
            qDebug() << "Error: unable to connect to database.";
            qDebug() << "Database error:" << db.lastError().text();
            return db;  // Exit if connection fails
        }
        else{
            qDebug()<<"Database Opened!";
        }

    return db;
}

void MainWindow::OpenChartOfAccountsWindow(){
    ChartOfAccountWindow *ChartOfAccountWin=new ChartOfAccountWindow();
    QSize currentSize = this->size();
    QPoint currentPosition = this->pos();
    ChartOfAccountWin->resize(currentSize);
    ChartOfAccountWin->move(currentPosition);
    ChartOfAccountWin->show();

    this->close();
    delete this;
}
void MainWindow::on_Accounting_clicked()
{
    OpenChartOfAccountsWindow();
}


void MainWindow::on_pushButton_clicked()
{
    ui->Navbar->setVisible(!ui->Navbar->isVisible());
    ui->SalesOptions->setVisible(false);
}




void MainWindow::on_Sales_clicked()
{
    ui->SalesOptions->setVisible(true);
}


void MainWindow::on_CreateInvoice_clicked()
{
    CreateInvoice* CreateWin= new CreateInvoice();
    QSize currentSize = this->size();
    QPoint currentPosition = this->pos();
    CreateWin->resize(currentSize);
    CreateWin->move(currentPosition);
    CreateWin->show();
    this->close();
    delete this;
}


void MainWindow::on_RecordPayment_clicked()
{
    ReadPayment* ReadWin=new ReadPayment();
    QSize currentSize = this->size();
    QPoint currentPosition = this->pos();
    ReadWin->resize(currentSize);
    ReadWin->move(currentPosition);
    ReadWin->show();
    this->close();
    delete this;
}


#endif // FUNCTIONSDEFINITION_H
