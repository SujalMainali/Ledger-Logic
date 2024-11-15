#include "trialbalance.h"
#include "./ui_trialbalance.h"
#include "mainwindow.h"
#include <QSqlQuery>
#include <QSqlDatabase>

TrialBalance::TrialBalance(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::TrialBalance)
{
    ui->setupUi(this);
    ui->Title->setText("TRIAL BALANCE AT " + ui->ReadDate->date().toString("yyyy-MM-dd"));
    PopulateTable();


}

TrialBalance::~TrialBalance()
{
    delete ui;
}

void TrialBalance::PopulateTable() {
    QSqlDatabase db=MainWindow::db;

    // Clear the table before populating
    ui->TrialTable->clearContents();
    ui->TrialTable->setRowCount(0);

    // Prepare SQL query to read account balances
    QSqlQuery query;
    query.prepare("SELECT a.account_id, c.account_name, a.current_balance "
                  "FROM AccountBalances a "
                  "JOIN ChartOfAccounts c ON a.account_id = c.account_id");

    if (!query.exec()) {
        qDebug() << "Failed to fetch trial balance data:" << query.lastError().text();
        return;
    }

    // Populate the table
    int row = 0;
    while (query.next()) {
        // Fetch account details
        int accountId = query.value("account_id").toInt();
        QString accountName = query.value("account_name").toString();
        double currentBalance = query.value("current_balance").toDouble();

        // Add a new row to the table
        ui->TrialTable->insertRow(row);

        // Populate columns
        ui->TrialTable->setItem(row, 0, new QTableWidgetItem(QString::number(accountId))); // Account ID
        ui->TrialTable->setItem(row, 1, new QTableWidgetItem(accountName));               // Account Name

        if (currentBalance >= 0) {
            // Debit column
            ui->TrialTable->setItem(row, 2, new QTableWidgetItem(QString::number(currentBalance, 'f', 2)));
            ui->TrialTable->setItem(row, 3, new QTableWidgetItem("")); // Credit column empty
        } else {
            // Credit column
            ui->TrialTable->setItem(row, 2, new QTableWidgetItem("")); // Debit column empty
            ui->TrialTable->setItem(row, 3, new QTableWidgetItem(QString::number(qAbs(currentBalance), 'f', 2)));
        }
        int rowHeight = 50; // Set the height for each row
        int newHeight = (row+3) * rowHeight; // Calculate new height for the table
        ui->TrialTable->setFixedHeight(newHeight);
        row++;
    }

    // Add totals as the last row
    AddTotalRow();

    // Adjust column sizes for better visibility
    ui->TrialTable->horizontalHeader()->setStretchLastSection(true);
}

void TrialBalance::AddTotalRow() {
    // Calculate totals
    double totalDebit = 0, totalCredit = 0;

    for (int i = 0; i < ui->TrialTable->rowCount(); i++) {
        // Debit column
        QString debitValue = ui->TrialTable->item(i, 2)->text();
        if (!debitValue.isEmpty()) {
            totalDebit += debitValue.toDouble();
        }

        // Credit column
        QString creditValue = ui->TrialTable->item(i, 3)->text();
        if (!creditValue.isEmpty()) {
            totalCredit += creditValue.toDouble();
        }
    }

    // Add a new row for totals
    int totalRow = ui->TrialTable->rowCount();
    ui->TrialTable->insertRow(totalRow);

    // Populate the last row with totals
    ui->TrialTable->setItem(totalRow, 0, new QTableWidgetItem("")); // Account ID column empty
    ui->TrialTable->setItem(totalRow, 1, new QTableWidgetItem("Total Amount")); // Text in Account Name column
    ui->TrialTable->setItem(totalRow, 2, new QTableWidgetItem(QString::number(totalDebit, 'f', 2))); // Debit column total
    ui->TrialTable->setItem(totalRow, 3, new QTableWidgetItem(QString::number(totalCredit, 'f', 2))); // Credit column total

    // Style the total row (optional)
    QFont font = ui->TrialTable->font();
    font.setBold(true);
    for (int col = 0; col < ui->TrialTable->columnCount(); ++col) {
        QTableWidgetItem *item = ui->TrialTable->item(totalRow, col);
        if (item) {
            item->setFont(font);
        }
    }
}

void TrialBalance::on_LogoButton_clicked()
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

