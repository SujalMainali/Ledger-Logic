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
    if (!db.isOpen()) {
        qDebug() << "Database connection is not open!";
        return;
    }

    QSqlQuery query("SELECT coa.account_name, ABS(ab.current_balance) AS absolute_balance, coa.type "
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
        double currentBalance = query.value(1).toDouble(); // Now an absolute value
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
    QSqlQuery expenseQuery("SELECT coa.account_name, ABS(ab.current_balance) AS absolute_balance "
                           "FROM ChartOfAccounts coa "
                           "JOIN AccountBalances ab ON coa.account_id = ab.account_id "
                           "WHERE coa.type = 'EXPENSES' ORDER BY coa.account_name");

    QStandardItem *expenseItem = new QStandardItem("Expenses");
    model->appendRow(expenseItem);
    double totalExpenses = 0.0;

    while (expenseQuery.next()) {
        QString accountName = expenseQuery.value(0).toString();
        double currentBalance = expenseQuery.value(1).toDouble(); // Now an absolute value
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

    // Expand all rows
    for (int row = 0; row < model->rowCount(); ++row) {
        QModelIndex index = model->index(row, 0); // Column 0 is where the item is located
        ui->PLTable->expand(index);  // Expand the row
    }
}

double PLAccount::calculateNetProfitOrLoss() {
    QSqlDatabase db = MainWindow::db;
    if (!db.isOpen()) {
        qDebug() << "Database connection is not open!";
        return 0.0;
    }

    double totalIncome = 0.0;
    double totalExpenses = 0.0;

    // Query to calculate total income
    QSqlQuery incomeQuery("SELECT SUM(ABS(ab.current_balance)) AS total_income "
                          "FROM ChartOfAccounts coa "
                          "JOIN AccountBalances ab ON coa.account_id = ab.account_id "
                          "WHERE coa.type = 'INCOME'");
    if (incomeQuery.next()) {
        totalIncome = incomeQuery.value(0).toDouble();
    } else {
        qDebug() << "Failed to fetch total income:" << incomeQuery.lastError().text();
    }

    // Query to calculate total expenses
    QSqlQuery expenseQuery("SELECT SUM(ABS(ab.current_balance)) AS total_expenses "
                           "FROM ChartOfAccounts coa "
                           "JOIN AccountBalances ab ON coa.account_id = ab.account_id "
                           "WHERE coa.type = 'EXPENSES'");
    if (expenseQuery.next()) {
        totalExpenses = expenseQuery.value(0).toDouble();
    } else {
        qDebug() << "Failed to fetch total expenses:" << expenseQuery.lastError().text();
    }

    // Calculate Net Profit/Loss
    double netProfitLoss = totalIncome - totalExpenses;
    return netProfitLoss;
}




PLAccount::~PLAccount()
{
    delete ui;
}



void PLAccount::on_LogoButton_clicked()
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

