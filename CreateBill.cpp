#include "CreateBill.h"
#include "mainwindow.h"
#include "chartofaccountwindow.h"
#include "invoicebillfunctions.h"
#include "./ui_CreateBill.h"
#include <QSql>
#include <QSqlDatabase>
#include <QSqlQuery>

CreateBill::CreateBill(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::CreateBill)
{
    ui->setupUi(this);
    QSqlDatabase db=MainWindow::db;
    InvoiceBillFunctions::setComboBoxInCell(ui->ItemsTable,0, 2,db);
    InvoiceBillFunctions::populateComboBoxWithAccounts(ui->ShowAccounts,db);
}

CreateBill::~CreateBill()
{
    delete ui;
}

void CreateBill::on_ItemsTable_cellChanged(int row, int column)
{
    InvoiceBillFunctions::TableDataEntry(ui->ItemsTable,row,column,ui->Total);
}


void CreateBill::saveBillTransaction() {
    // Get the bill number from QLineEdit
    QString billNumber = ui->ReadBillNumber->text();

    if (billNumber.isEmpty()) {
        QMessageBox::warning(this, "Input Error", "Please enter a bill number.");
        return;
    }

    // Get supplier details from the UI
    QString supplierName = ui->ReadSupplierName->text(); // Replace with your actual UI element
    QString supplierAccount = ui->ShowAccounts->currentText();
    QDate transactionDate = ui->ReadIssueDate->date(); // Assuming a QDateEdit for transaction date
    QDate dueDate = ui->ReadDueDate->date(); // Assuming a QDateEdit for due date
    QString totalAmount = ui->Total->text(); // Initialize total amount
    QString paidAmount = "0.00"; // Set initial paid amount to 0, adjust if you have a UI for this

    // Get account ID based on the supplier account (replace with actual retrieval logic)
    int accountId = ChartOfAccountWindow::getAccountIdFromAccountName(supplierAccount); // Define this method to fetch the account ID

    QSqlDatabase db= MainWindow::db;

    // Prepare SQL query for inserting the bill transaction
    QSqlQuery query(db);
    query.prepare("INSERT INTO BillTransactions (bill_number, supplier_name, supplier_account, "
                  "transaction_date, due_date, total_amount, paid_amount, remaining_amount, account_id) "
                  "VALUES (:bill_number, :supplier_name, :supplier_account, "
                  ":transaction_date, :due_date, :total_amount, :paid_amount, :remaining_amount, :account_id)");

    // Bind values
    query.bindValue(":bill_number", billNumber);
    query.bindValue(":supplier_name", supplierName);
    query.bindValue(":supplier_account", supplierAccount);
    query.bindValue(":transaction_date", transactionDate);
    query.bindValue(":due_date", dueDate);
    query.bindValue(":total_amount", totalAmount.toDouble());
    query.bindValue(":paid_amount", paidAmount.toDouble());
    query.bindValue(":remaining_amount", totalAmount.toDouble() - paidAmount.toDouble());
    query.bindValue(":account_id", accountId);

    // Execute the query for inserting the bill transaction
    if (!query.exec()) {
        qDebug() << "Failed to insert bill transaction:" << query.lastError().text();
    } else {
        qDebug() << "Inserted bill transaction for bill number:" << billNumber;

        // Now update the remaining_amount if necessary (although this is done in the insert above)
        QSqlQuery updateQuery(db);
        updateQuery.prepare("UPDATE BillTransactions "
                            "SET remaining_amount = total_amount - paid_amount "
                            "WHERE bill_number = :bill_number");
        updateQuery.bindValue(":bill_number", billNumber);

        // Execute the update query
        if (!updateQuery.exec()) {
            qDebug() << "Failed to update remaining amount for bill:" << query.lastError().text();
        } else {
            qDebug() << "Updated remaining amount for bill:" << billNumber;
        }
    }

}

void CreateBill::saveBillTransactionItems() {
    QString billNumber = ui->ReadBillNumber->text();

    if (billNumber.isEmpty()) {
        QMessageBox::warning(this, "Input Error", "Please enter a bill number.");
        return;
    }

    QSqlDatabase db = MainWindow::db;
    if (!db.isOpen()) {
        qDebug() << "Failed to open the database!";
        return;
    }

    QSqlQuery query(db);
    query.prepare("INSERT INTO BillTransactionItems (bill_number, product_name, rate, units, amount, account_name) "
                  "VALUES (:bill_number, :product_name, :rate, :units, :amount, :account_name)");

    // Loop through each row in the table to read the product details
    int rowCount = ui->ItemsTable->rowCount();
    for (int row = 0; row < rowCount; ++row) {
        // Read product details from the QTableWidget/QTableView
        QString productName = ui->ItemsTable->item(row, 0) ? ui->ItemsTable->item(row, 0)->text() : QString();
        double rate = ui->ItemsTable->item(row, 3) ? ui->ItemsTable->item(row, 3)->text().toDouble() : 0.0;
        int units = ui->ItemsTable->item(row, 4) ? ui->ItemsTable->item(row, 4)->text().toInt() : 0;
        double amount = ui->ItemsTable->item(row, 5) ? ui->ItemsTable->item(row, 5)->text().toDouble() : 0.0;

        // Retrieve the QComboBox from the table cell
        QComboBox *comboBox = qobject_cast<QComboBox*>(ui->ItemsTable->cellWidget(row, 2)); // Assuming account name is in column 2
        QString accountName;
        if (comboBox) {
            accountName = comboBox->currentText(); // Get the selected account name
        } else {
            qDebug() << "No combo box found at row" << row << "column 2";
            continue; // Skip this iteration if no combo box is found
        }

        // Bind values
        query.bindValue(":bill_number", billNumber);
        query.bindValue(":product_name", productName);
        query.bindValue(":rate", rate);
        query.bindValue(":units", units);
        query.bindValue(":amount", amount);
        query.bindValue(":account_name", accountName); // Bind account name

        // Execute the query
        if (!query.exec()) {
            qDebug() << "Failed to insert bill transaction item:" << query.lastError().text();
        } else {
            qDebug() << "Inserted row for product:" << productName;
        }
    }
}
void CreateBill::createJournalEntryForBill() {

    QString billNumber = ui->ReadBillNumber->text();
    QString supplierAccountName = ui->ShowAccounts->currentText();
    int supplierAccountId = ChartOfAccountWindow::getAccountIdFromAccountName(supplierAccountName);

    QSqlDatabase db = MainWindow::db;
    if (!db.isOpen()) {
        qDebug() << "Failed to open the database!";
        return;
    }

    QSqlQuery query(db);

    // Step 1: Fetch Bill Date and Total Amount
    query.prepare("SELECT transaction_date, total_amount FROM BillTransactions WHERE bill_number = :bill_number");
    query.bindValue(":bill_number", billNumber);

    QDate billDate;
    double totalAmount = 0.0;
    if (query.exec() && query.next()) {
        billDate = query.value("transaction_date").toDate();
        totalAmount = query.value("total_amount").toDouble();
    } else {
        qDebug() << "Failed to fetch bill details:" << query.lastError().text();
        return;
    }

    // Step 2: Extract integer part from Bill Number to form Journal Number
    QString billNumberIntPart = billNumber;
    billNumberIntPart.remove(0, 3);  // Remove 'BILL' prefix to get the integer part
    QString journalNumber = "BILLGJ" + billNumberIntPart;

    // Step 3: Create a new Journal Entry in JournalEntries
    QString journalMemo = "Bill " + billNumber + " Posting";

    query.prepare("INSERT INTO JournalEntries (journal_number, date, memo) "
                  "VALUES (:journal_number, :date, :memo)");
    query.bindValue(":journal_number", journalNumber);
    query.bindValue(":date", billDate);
    query.bindValue(":memo", journalMemo);

    if (!query.exec()) {
        qDebug() << "Failed to insert journal entry:" << query.lastError().text();
        return;
    }

    int journalId = query.lastInsertId().toInt();

    // Step 4: Credit Supplier Account with Total Amount
    QSqlQuery lineQuery(db);
    lineQuery.prepare("INSERT INTO JournalEntryLines (journal_id, account_id, amount, is_debit) "
                      "VALUES (:journal_id, :account_id, :amount, :is_debit)");
    lineQuery.bindValue(":journal_id", journalId);
    lineQuery.bindValue(":account_id", supplierAccountId);
    lineQuery.bindValue(":amount", totalAmount);
    lineQuery.bindValue(":is_debit", false);  // Credit supplier account (is_debit = false)

    if (!lineQuery.exec()) {
        qDebug() << "Failed to insert credit line for supplier:" << lineQuery.lastError().text();
        return;
    }

    // Step 5: Debit Accounts based on UI Table Data
    int rowCount = ui->ItemsTable->rowCount();
    for (int row = 0; row < rowCount-1; ++row) {
        // Get the amount from the UI table
        double amount = ui->ItemsTable->item(row, 5) ? ui->ItemsTable->item(row, 5)->text().toDouble() : 0.0;

        // Retrieve the QComboBox from the table cell for the account name
        QComboBox *comboBox = qobject_cast<QComboBox*>(ui->ItemsTable->cellWidget(row, 2)); // Assuming account name is in column 2
        QString accountName;
        if (comboBox) {
            accountName = comboBox->currentText();
        } else {
            qDebug() << "No combo box found at row" << row << "column 2";
            continue; // Skip this iteration if no combo box is found
        }

        // Get the account ID for the selected account
        int accountId = ChartOfAccountWindow::getAccountIdFromAccountName(accountName);
        if (accountId == -1) {
            qDebug() << "Failed to find account ID for account name:" << accountName;
            continue;
        }

        // Directly construct the SQL query string with the values
        QSqlQuery debitLineQuery;
        QString queryString = QString("INSERT INTO JournalEntryLines (journal_id, account_id, amount, is_debit) "
                                      "VALUES (%1, %2, %3, %4)")
                                      .arg(journalId)
                                      .arg(accountId)
                                      .arg(amount)
                                      .arg(true); // `true` is 1 in SQL, indicating a debit

        if (!debitLineQuery.exec(queryString)) {
            qDebug() << "Failed to insert debit line for account:"
                     << accountName << "with error:" << debitLineQuery.lastError().text();
        }
    }

}


void CreateBill::on_Cancel_clicked()
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




void CreateBill::on_Save_clicked()
{
    saveBillTransaction();
    saveBillTransactionItems();
    createJournalEntryForBill();
    MainWindow *MainWin=new MainWindow();
    QSize currentSize = this->size();
    QPoint currentPosition = this->pos();
    MainWin->resize(currentSize);
    MainWin->move(currentPosition);
    MainWin->show();
    this->close();
    delete this;
}

