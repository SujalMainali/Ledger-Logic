#include "CreateJournal.h"
#include "./ui_CreateJournal.h"
#include "mainwindow.h"
#include "invoicebillfunctions.h"
#include <QSql>

CreateJournal::CreateJournal(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::CreateJournal)
{
    ui->setupUi(this);
    QSqlDatabase db= MainWindow::ConnectDatabase();
    InvoiceBillFunctions::setComboBoxInCell(ui->JournalTable,0,0,db);
    InvoiceBillFunctions::setComboBoxInCell(ui->JournalTable,1,0,db);
    db.close();
}

CreateJournal::~CreateJournal()
{
    delete ui;
}
void CreateJournal::UpdateAccountBalances(int accountId, double amount, bool isDebit, QSqlDatabase &db){
    if (!db.isOpen()) {
        qDebug() << "Error: Could not open the database.";
        return;
    }

    // Select the current debit_total, credit_total, and opening_balance from AccountBalances
    QSqlQuery query;
    query.prepare("SELECT opening_balance, debit_total, credit_total FROM AccountBalances WHERE account_id = :accountId");
    query.bindValue(":accountId", accountId);

    if (!query.exec() || !query.next()) {
        qDebug() << "Error retrieving account balance for account ID" << accountId << ":" << query.lastError().text();
        return;
    }

    double openingBalance = query.value("opening_balance").toDouble();
    double debitTotal = query.value("debit_total").toDouble();
    double creditTotal = query.value("credit_total").toDouble();

    // Update debit or credit totals based on the isDebit flag
    if (isDebit) {
        debitTotal += amount;
    } else {
        creditTotal += amount;
    }

    // Calculate the current balance
    double currentBalance = openingBalance + debitTotal - creditTotal;

    // Update the AccountBalances table
    QSqlQuery updateQuery;
    updateQuery.prepare("UPDATE AccountBalances SET debit_total = :debitTotal, credit_total = :creditTotal, current_balance = :currentBalance WHERE account_id = :accountId");
    updateQuery.bindValue(":debitTotal", debitTotal);
    updateQuery.bindValue(":creditTotal", creditTotal);
    updateQuery.bindValue(":currentBalance", currentBalance);
    updateQuery.bindValue(":accountId", accountId);

    if (!updateQuery.exec()) {
        qDebug() << "Error updating account balance:" << updateQuery.lastError().text();
    }

}


void CreateJournal::on_Save_clicked()
{
    QString journalNo = ui->ReadJournalNo->text();
    QString date = ui->ReadDate->text();
    QString memo = ui->ReadDescription->toPlainText();

    // Check if any required fields are empty
    if (journalNo.isEmpty() || date.isEmpty() || memo.isEmpty()) {
        QMessageBox::warning(this, "Input Error", "Please fill in all required fields before saving.");
        return; // Exit the function if any of the required fields are empty
    }

    // Connect to the database
    QSqlDatabase db = MainWindow::ConnectDatabase();
    if (!db.isOpen()) {
        qDebug() << "Error: Could not open the database.";
        return;
    }

    // Insert the journal entry into the JournalEntries table
    QSqlQuery journalQuery;
    journalQuery.prepare("INSERT INTO JournalEntries (journal_number, date, memo) VALUES (:journalNo, :date, :memo)");
    journalQuery.bindValue(":journalNo", journalNo);
    journalQuery.bindValue(":date", date);
    journalQuery.bindValue(":memo", memo);

    if (!journalQuery.exec()) {
        qDebug() << "Error inserting journal entry:" << journalQuery.lastError().text();
        return;
    }

    // Retrieve the journal_id of the newly inserted journal entry
    int journalId = journalQuery.lastInsertId().toInt();

    QComboBox *comboBox;
    // Insert each line from the journalTableWidget into JournalEntryLines
    for (int row = 0; row < ui->JournalTable->rowCount(); ++row) {
        comboBox = qobject_cast<QComboBox*>(ui->JournalTable->cellWidget(row, 0));
        QString accountName = comboBox->currentText();
        QString debitStr = ui->JournalTable->item(row, 1)->text();
        QString creditStr = ui->JournalTable->item(row, 2)->text();

        // Check if any of the required cells are empty or contain invalid values
        if (accountName.isEmpty() || debitStr.isEmpty() || creditStr.isEmpty()) {
            QMessageBox::warning(this, "Input Error", "Please fill in all fields in the journal table. Enter 0 in either the debit or credit field.");
            return; // Exit the function if any fields are empty
        }

        double amount = 0.0;
        bool isDebit = false;

        // Check if the debit or credit is zero instead of empty
        if (debitStr.toDouble() != 0.0) {
            amount = debitStr.toDouble();
            isDebit = true;
        } else if (creditStr.toDouble() != 0.0) {
            amount = creditStr.toDouble();
            isDebit = false;
        }

        QSqlQuery accountQuery;
        accountQuery.prepare("SELECT account_id FROM ChartOfAccounts WHERE account_name = :accountName");
        accountQuery.bindValue(":accountName", accountName);

        if (!accountQuery.exec() || !accountQuery.next()) {
            qDebug() << "Error retrieving account ID for account name" << accountName << ":" << accountQuery.lastError().text();
            continue;
        }

        int accountId = accountQuery.value(0).toInt();

        // Insert the journal entry line into the JournalEntryLines table
        QSqlQuery lineQuery;
        lineQuery.prepare("INSERT INTO JournalEntryLines (journal_id, account_id, amount, is_debit) "
                          "VALUES (:journalId, :accountId, :amount, :isDebit)");
        lineQuery.bindValue(":journalId", journalId);
        lineQuery.bindValue(":accountId", accountId);
        lineQuery.bindValue(":amount", amount);
        lineQuery.bindValue(":isDebit", isDebit);

        if (!lineQuery.exec()) {
            qDebug() << "Error inserting journal entry line:" << lineQuery.lastError().text();
        }

        UpdateAccountBalances(accountId, amount, isDebit, db);
    }

    db.close();
    qDebug() << "Journal entry and lines saved successfully!";
}




void CreateJournal::on_Cancel_clicked()
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


void CreateJournal::on_AddRow_clicked()
{
    int rowCount=ui->JournalTable->rowCount();
    QTableWidgetItem *debitItem = new QTableWidgetItem("0.0");
    QTableWidgetItem *creditItem = new QTableWidgetItem("0.0");
    ui->JournalTable->insertRow(rowCount);
    ui->JournalTable->setItem(rowCount,1,debitItem);
    ui->JournalTable->setItem(rowCount, 2, creditItem);
    QSqlDatabase db= MainWindow::ConnectDatabase();
    InvoiceBillFunctions::setComboBoxInCell(ui->JournalTable,rowCount,0,db);
    db.close();
 }

