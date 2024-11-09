#include "accountactivity.h"
#include "./ui_accountactivity.h"
#include "mainwindow.h"
#include "ledgersummary.h"
#include <QSql>
#include <QSqlQuery>

ActivitySummary::ActivitySummary(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::ActivitySummary)
{
    ui->setupUi(this);
    loadLedgerData(LedgerSummary::AccountId);
    ui->LabelAccount->setText("Here is the Activity for Account:"+LedgerSummary::AccountName);
}

ActivitySummary::~ActivitySummary()
{
    delete ui;
}

double ActivitySummary::fetchOpeningBalance(int accountId,QSqlDatabase &db) {
    QSqlQuery query(db);
    query.prepare("SELECT opening_balance FROM AccountBalances WHERE account_id = :accountId");
    query.bindValue(":accountId", accountId);
    if (query.exec() && query.next()) {
        return query.value(0).toDouble();
    } else {
        qDebug() << "Error fetching opening balance:" << query.lastError();
        return 0.0;
    }
}

void ActivitySummary::loadLedgerData(int accountId) {
    QSqlDatabase db = QSqlDatabase::database();
    if (!db.isOpen()) {
        qDebug() << "Database is not open";
        return;
    }

    double openingBalance = fetchOpeningBalance(accountId,db);
    double runningBalance = openingBalance;

    ui->ReadOpeningBalance->setText(QString::number(openingBalance, 'f', 2));

    //Remember to fix the time period issue


    QSqlQuery query;
    query.prepare("SELECT je.date, je.journal_number, "
                  "CASE WHEN jel.is_debit THEN coa_credit.account_name ELSE coa_debit.account_name END AS by_account, "
                  "jel.amount, jel.is_debit "
                  "FROM JournalEntries je "
                  "JOIN JournalEntryLines jel ON je.journal_id = jel.journal_id "
                  "JOIN ChartOfAccounts coa_credit ON jel.account_id = coa_credit.account_id "
                  "LEFT JOIN JournalEntryLines jel_opposite ON jel_opposite.journal_id = jel.journal_id "
                  "AND jel_opposite.entry_line_id != jel.entry_line_id "
                  "LEFT JOIN ChartOfAccounts coa_debit ON jel_opposite.account_id = coa_debit.account_id "
                  "WHERE jel.account_id = :accountId "
                  "ORDER BY je.date");
    query.bindValue(":accountId", accountId);

    if (!query.exec()) {
        qDebug() << "Error fetching ledger data:" << query.lastError();
        return;
    }

    int row = 0;
    while (query.next()) {
        ui->ActivityTable->insertRow(row);
        QDate date = query.value("date").toDate();
        QString journalNumber = query.value("journal_number").toString();
        QString byAccount = query.value("by_account").toString();
        double amount = query.value("amount").toDouble();
        bool isDebit = query.value("is_debit").toBool();

        double beginningBalance = runningBalance;
        double debit = isDebit ? amount : 0.0;
        double credit = isDebit ? 0.0 : amount;

        runningBalance += debit - credit;

        ui->ActivityTable->setItem(row, 0, new QTableWidgetItem(date.toString("yyyy-MM-dd")));
        ui->ActivityTable->setItem(row, 1, new QTableWidgetItem(journalNumber));
        ui->ActivityTable->setItem(row, 2, new QTableWidgetItem(byAccount));
        ui->ActivityTable->setItem(row, 3, new QTableWidgetItem(QString::number(beginningBalance, 'f', 2)));
        ui->ActivityTable->setItem(row, 4, new QTableWidgetItem(QString::number(debit, 'f', 2)));
        ui->ActivityTable->setItem(row, 5, new QTableWidgetItem(QString::number(credit, 'f', 2)));
        ui->ActivityTable->setItem(row, 6, new QTableWidgetItem(QString::number(runningBalance, 'f', 2)));

        row++;
    }
    ui->ReadClosingBalance->setText(QString::number(runningBalance, 'f', 2));
    db.close();
}


void ActivitySummary::on_MainWindow_clicked()
{
    MainWindow* MainWin =new MainWindow();
        QSize currentSize = this->size();
        QPoint currentPosition = this->pos();
        MainWin->resize(currentSize);
        MainWin->move(currentPosition);
        MainWin->show();
        this->close();
        delete this;
}


void ActivitySummary::on_pushButton_clicked()
{

}

