#include "ledgersummary.h"
#include "./ui_ledgersummary.h"
#include "mainwindow.h"
#include "accountactivity.h"
#include <QSql>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QCoreApplication>

int LedgerSummary::AccountId = 0;
QString LedgerSummary::AccountName="";

LedgerSummary::LedgerSummary(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::LedgerSummary)
{
    ui->setupUi(this);
}

LedgerSummary::~LedgerSummary()
{
    delete ui;
}

void LedgerSummary::loadLedgerData(QDate startDate, QDate endDate) {
    // Prepare SQL query to fetch account balances and journal totals for the selected period
    QSqlDatabase db=MainWindow::db;
    QSqlQuery query(db);


    //Need to manage the time period



    query.prepare(R"(
    SELECT
        A.account_id,
        A.account_name,
        AB.opening_balance,
        COALESCE(SUM(CASE WHEN JEL.is_debit THEN JEL.amount ELSE 0 END), 0) AS debit_total,
        COALESCE(SUM(CASE WHEN NOT JEL.is_debit THEN JEL.amount ELSE 0 END), 0) AS credit_total,
        (AB.opening_balance + COALESCE(SUM(CASE WHEN JEL.is_debit THEN JEL.amount ELSE 0 END), 0)
         - COALESCE(SUM(CASE WHEN NOT JEL.is_debit THEN JEL.amount ELSE 0 END), 0)) AS current_balance
    FROM
        AccountBalances AB
    JOIN
        ChartOfAccounts A ON AB.account_id = A.account_id
    LEFT JOIN
        JournalEntryLines JEL ON A.account_id = JEL.account_id
    LEFT JOIN
        JournalEntries JE ON JEL.journal_id = JE.journal_id AND JE.date BETWEEN :start_date AND :end_date
    GROUP BY
        A.account_id, A.account_name, AB.opening_balance
    ORDER BY
        A.account_id;
    )");


    // Bind the date range to the query
    query.bindValue(":start_date", startDate.toString("yyyy-MM-dd"));
    query.bindValue(":end_date", endDate.toString("yyyy-MM-dd"));

    if (!query.exec()) {
        qDebug() << "Error fetching ledger data: " << query.lastError().text();
        return;
    }
    // Clear the table before inserting new data
    ui->LedgerTable->setRowCount(0);

    int row = 0;
    while (query.next()) {
        // Insert a new row for each account in the result
        ui->LedgerTable->insertRow(row);

        // Get data from the query result
        int accountId = query.value(0).toInt();
        QString accountName = query.value(1).toString();
        double openingBalance = query.value(2).toDouble();
        double debitTotal = query.value(3).toDouble();
        double creditTotal = query.value(4).toDouble();
        double currentBalance = query.value(5).toDouble();

        // Set data in the table
        ui->LedgerTable->setItem(row, 0, new QTableWidgetItem(QString::number(accountId)));
        ui->LedgerTable->setItem(row, 1, new QTableWidgetItem(accountName));
        ui->LedgerTable->setItem(row, 2, new QTableWidgetItem(QString::number(openingBalance, 'f', 2)));
        ui->LedgerTable->setItem(row, 3, new QTableWidgetItem(QString::number(debitTotal, 'f', 2)));
        ui->LedgerTable->setItem(row, 4, new QTableWidgetItem(QString::number(creditTotal, 'f', 2)));
        ui->LedgerTable->setItem(row, 5, new QTableWidgetItem(QString::number(currentBalance, 'f', 2)));

        row++;
    }
}



void LedgerSummary::on_pushButton_clicked()
{
    QDate startDate = ui->ReadFromDate->date();  // Get start date from the QDateEdit widget
    QDate endDate = ui->ReadToDate->date();      // Get end date from the QDateEdit widget
    loadLedgerData(startDate, endDate);
}


void LedgerSummary::on_pushButton_3_clicked()
{
    MainWindow *MainWin=new MainWindow();
    QSize currentSize = this->size();
    QPoint currentPosition = this->pos();
    MainWin->resize(currentSize);
    MainWin->move(currentPosition);
    MainWin->show();
    this->close();
    delete this;
}


void LedgerSummary::on_LedgerTable_itemDoubleClicked(QTableWidgetItem *item)
{
    AccountId=ui->LedgerTable->item(item->row(),0)->text().toInt();
    AccountName=ui->LedgerTable->item(item->row(),1)->text();
    ActivitySummary* ActivityWin=new ActivitySummary();
    QSize currentSize = this->size();
    QPoint currentPosition = this->pos();
    ActivityWin->resize(currentSize);
    ActivityWin->move(currentPosition);
    qDebug()<<"Selected Account"<<AccountId<<AccountName;
    ActivityWin->show();
    this->close();
}


