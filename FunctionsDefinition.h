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
#include "CreateBill.h"
#include "ReadSupplierPayment.h"
#include "CreateJournal.h"
#include "ledgersummary.h"
#include "trialbalance.h"
#include "placcount.h"
#include "balancesheet.h"




void MainWindow::RetrieveDataForSalesGraph(QLineSeries *series) {
    QVector<QPointF> data;  // Vector to store (x, y) data

    QSqlDatabase db;
    db = MainWindow::db;

    // Ensure the query is valid and can execute, ordering by issue_date in ascending order
    QSqlQuery query("SELECT issue_date, total_amount FROM SalesTransactions ORDER BY issue_date ASC");
    if (!query.exec()) {
        qDebug() << "Error: failed to execute Sales query";
        return;
    }

    // Process the query results
    while (query.next()) {  // Iterate through the query results
        QDateTime dateTime = query.value(0).toDateTime();  // Retrieve data in DateTime format
        double money = query.value(1).toDouble();          // Retrieve amount in double

        // Append current entry (day and money) directly to the series
        series->append(dateTime.date().day(), money);  // Append to the series directly
    }
}

void MainWindow::RetrieveDataForPurchaseGraph(QLineSeries *series) {
    QVector<QPointF> data;  // Vector to store (x, y) data

    QSqlDatabase db;
    db = MainWindow::db;

    // Ensure the query is valid and can execute, ordering by transaction_date in ascending order
    QSqlQuery query("SELECT transaction_date, total_amount FROM BillTransactions ORDER BY transaction_date ASC");
    if (!query.exec()) {
        qDebug() << "Error: failed to execute Purchase query";
        return;
    }

    // Process the query results
    while (query.next()) {  // Iterate through the query results
        QDateTime dateTime = query.value(0).toDateTime();  // Retrieve data in DateTime format
        double money = query.value(1).toDouble();          // Retrieve amount in double

        // Append current entry (day and money) directly to the series
        series->append(dateTime.date().day(), money);  // Append to the series directly
    }
}





void MainWindow::ConnectDatabase() {
    // Check if the database is already valid and open
    if (db.isValid() && db.isOpen()) {
        qDebug() << "Database connection is already open.";
        return;
    }

    // Initialize the connection only if it hasn't been initialized
    if (!db.isValid()) {
        const QString connectionName = "qt_sql_default_connection";
        if (QSqlDatabase::contains(connectionName)) {
            db = QSqlDatabase::database(connectionName);
        } else {
            db = QSqlDatabase::addDatabase("QSQLITE", connectionName);
            db.setDatabaseName(QCoreApplication::applicationDirPath() + "/database/AccountingDetails.db");
        }
    }

    // Attempt to open the database if it’s not open
    if (!db.isOpen() && !db.open()) {
        qDebug() << "Error: Unable to open database connection.";
        qDebug() << "Database error:" << db.lastError().text();
    } else {
        qDebug() << "Database Opened!";
    }
}

QMessageBox* MainWindow::createStyledMessageBox(const QString& title, const QString& text, const QString& informativeText) {
    // Create a new QMessageBox
    QMessageBox* msgBox = new QMessageBox();
    msgBox->setIcon(QMessageBox::Critical);
    msgBox->setWindowTitle(title);
    msgBox->setText(text);
    msgBox->setInformativeText(informativeText);

    // Apply custom dark theme style
    QString styleSheet = R"(
        QMessageBox {
            background-color: #2E2E2E; /* Dark background */
            color: #E0E0E0; /* Light text */
            border-radius: 5px;
            font-family: Arial, sans-serif;
            font-size: 14px;
        }
        QMessageBox QLabel {
            color: #E0E0E0; /* Light text color for the label */
        }
        QMessageBox QPushButton {
            background-color: #444444; /* Dark button background */
            color: #E0E0E0; /* Light text on buttons */
            border: 1px solid #555555; /* Button border color */
            border-radius: 3px;
            padding: 5px 10px;
        }
        QMessageBox QPushButton:hover {
            background-color: #666666; /* Button hover effect */
        }
        QMessageBox QPushButton:pressed {
            background-color: #888888; /* Button pressed effect */
        }
    )";

    msgBox->setStyleSheet(styleSheet);

    return msgBox;
}




void MainWindow::OpenChartOfAccountsWindow(){
    ChartOfAccountWindow *ChartOfAccountWin=new ChartOfAccountWindow();
    QSize currentSize = this->size();
    QPoint currentPosition = this->pos();
    ChartOfAccountWin->resize(currentSize);
    ChartOfAccountWin->move(currentPosition);
    ChartOfAccountWin->show();

    this->close();
}
void MainWindow::on_Accounting_clicked()
{
    OpenChartOfAccountsWindow();
}


void MainWindow::on_NavButton_clicked()
{
    ui->Navbar->setVisible(!ui->Navbar->isVisible());
    ui->InvoiceOptionsFrame ->setVisible(false);
    ui->BillOptionsFrame->setVisible(false);
    ui->ReportingOptionsFrame->setVisible(false);
}



void MainWindow::on_Sales_clicked()
{
    ui->InvoiceOptionsFrame->setVisible(true);
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
}
void MainWindow::on_Purchase_clicked()
{
    ui->BillOptionsFrame->setVisible(true);
}


void MainWindow::on_CreateBill_clicked()
{
    CreateBill* CreateBillWin= new CreateBill();
    QSize currentSize = this->size();
    QPoint currentPosition = this->pos();
    CreateBillWin->resize(currentSize);
    CreateBillWin->move(currentPosition);
    CreateBillWin->show();
    this->close();
}


void MainWindow::on_RecordBillPayment_clicked()
{
    ReadSupplierPayment* ReadSupplierWin= new ReadSupplierPayment();
    QSize currentSize = this->size();
    QPoint currentPosition = this->pos();
    ReadSupplierWin->resize(currentSize);
    ReadSupplierWin->move(currentPosition);
    ReadSupplierWin->show();
    this->close();
}

void MainWindow::on_pushButton_clicked()
{
    CreateJournal* JournalWin=new CreateJournal();
    QSize currentSize = this->size();
    QPoint currentPosition = this->pos();
    JournalWin->resize(currentSize);
    JournalWin->move(currentPosition);
    JournalWin->show();
    this->close();

}
void MainWindow::on_pushButton_2_clicked()
{
    LedgerSummary *LedgerSummaryWin=new LedgerSummary();
    QSize currentSize = this->size();
    QPoint currentPosition = this->pos();
    LedgerSummaryWin->resize(currentSize);
    LedgerSummaryWin->move(currentPosition);
    LedgerSummaryWin->show();
    this->close();
}

void MainWindow::on_TrialBalance_clicked()
{
    TrialBalance *TrialBalanceWin=new TrialBalance();
    QSize currentSize = this->size();
    QPoint currentPosition = this->pos();
    TrialBalanceWin->resize(currentSize);
    TrialBalanceWin->move(currentPosition);
    TrialBalanceWin->show();
    this->close();
}

void MainWindow::on_PLReport_clicked()
{
    PLAccount *PLAccountWin=new PLAccount();
    QSize currentSize = this->size();
    QPoint currentPosition = this->pos();
    PLAccountWin->resize(currentSize);
    PLAccountWin->move(currentPosition);
    PLAccountWin->show();
    this->close();
}

void MainWindow::on_BalanceSheet_clicked()
{
    BalanceSheet *BalanceSheetWin=new BalanceSheet();
        QSize currentSize = this->size();
        QPoint currentPosition = this->pos();
        BalanceSheetWin->resize(currentSize);
        BalanceSheetWin->move(currentPosition);
        BalanceSheetWin->show();
        this->close();
}

#endif // FUNCTIONSDEFINITION_H
