#include "placcount.h"
#include "./ui_placcount.h"
#include <QStandardItemModel>
#include<QtSql>
#include "mainwindow.h"

PLAccount::PLAccount(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::PLAccount)
{
    ui->setupUi(this);
    model = new QStandardItemModel(this);
    model->setHorizontalHeaderLabels({"Account", "Amount"});
    ui->Title->setText("PROFIT AND LOSS ACCOUNT FROM " +
                           ui->ReadFromDate->date().toString("yyyy-MM-dd") + " TO " +
                           ui->ReadToDate->date().toString("yyyy-MM-dd"));
    ui->PLTable->setModel(model);
    fetchProfitAndLossData();
}

void PLAccount::fetchProfitAndLossData() {
    QSqlDatabase db = MainWindow::db;
    QSqlQuery query("SELECT coa.account_name, ab.current_balance, coa.type "
                    "FROM ChartOfAccounts coa "
                    "JOIN AccountBalances ab ON coa.account_id = ab.account_id "
                    "WHERE coa.type IN ('INCOME', 'EXPENSES') "
                    "ORDER BY coa.type DESC, coa.account_name");

    // Income Section
    QStandardItem *incomeItem = new QStandardItem("Income");
    model->appendRow(incomeItem);
    double totalIncome = 0.0;

    while (query.next()) {
        QString accountName = query.value(0).toString();
        double currentBalance = query.value(1).toDouble();
        QString accountType = query.value(2).toString();

        if (accountType == "INCOME") {
            incomeItem->appendRow({new QStandardItem(accountName), new QStandardItem(QString::number(currentBalance))});
            totalIncome += currentBalance;
        }
    }

    // Add Total Income with bold font
    QStandardItem *totalIncomeItem = new QStandardItem("Total Income");
    totalIncomeItem->setFont(QFont("Arial", 10, QFont::Bold));
    incomeItem->appendRow({totalIncomeItem, new QStandardItem(QString::number(totalIncome))});

    // Expenses Section
    QSqlQuery expenseQuery("SELECT coa.account_name, ab.current_balance "
                           "FROM ChartOfAccounts coa "
                           "JOIN AccountBalances ab ON coa.account_id = ab.account_id "
                           "WHERE coa.type = 'EXPENSES' ORDER BY coa.account_name");

    QStandardItem *expenseItem = new QStandardItem("Expenses");
    model->appendRow(expenseItem);
    double totalExpenses = 0.0;

    while (expenseQuery.next()) {
        QString accountName = expenseQuery.value(0).toString();
        double currentBalance = expenseQuery.value(1).toDouble();
        expenseItem->appendRow({new QStandardItem(accountName), new QStandardItem(QString::number(currentBalance))});
        totalExpenses += currentBalance;
    }

    // Add Total Expenses with bold font
    QStandardItem *totalExpensesItem = new QStandardItem("Total Expenses");
    totalExpensesItem->setFont(QFont("Arial", 10, QFont::Bold));
    expenseItem->appendRow({totalExpensesItem, new QStandardItem(QString::number(totalExpenses))});


    // Add Net Profit/Loss
    QStandardItem *netProfitItem = new QStandardItem("Net Profit/Loss");
    model->appendRow(netProfitItem);
    double netProfitLoss = totalIncome - totalExpenses;
    QStandardItem *netProfitLossAmountItem = new QStandardItem(QString::number(netProfitLoss));
    netProfitLossAmountItem->setFont(QFont("Arial", 10, QFont::Bold));  // Make amount bold
    netProfitItem->appendRow({new QStandardItem("Net Profit/Loss"), netProfitLossAmountItem});

    for (int row = 0; row < model->rowCount(); ++row) {
            QModelIndex index = model->index(row, 0); // Column 0 is where the item is located
            ui->PLTable->expand(index);  // Expand the row
        }
}



PLAccount::~PLAccount()
{
    delete ui;
}


