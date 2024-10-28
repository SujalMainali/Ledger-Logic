#include "create1.h"
#include "./ui_create1.h"
#include "mainwindow.h"
#include "chartofaccountwindow.h"
#include "invoicebillfunctions.h"
#include <QSql>
#include <QDebug>

CreateInvoice::CreateInvoice(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::CreateInvoice)
{
    ui->setupUi(this);
    QSqlDatabase db=MainWindow::ConnectDatabase();
    InvoiceBillFunctions::populateComboBoxWithAccounts(ui->ShowAccounts,db);
    InvoiceBillFunctions::setComboBoxInCell(ui->ItemsTable,0, 2,db);
}

CreateInvoice::~CreateInvoice()
{
    delete ui;
}

void CreateInvoice::on_ItemsTable_cellChanged(int row, int column)
{
    InvoiceBillFunctions::TableDataEntry(ui->ItemsTable,row,column,ui->TotalAmount);
}


void CreateInvoice::saveTransactionItems() {
    QString invoiceNumber = ui->ReadInvoiceNo->text();

    if (invoiceNumber.isEmpty()) {
        QMessageBox::warning(this, "Input Error", "Please enter an invoice number.");
        return;
    }

    QSqlDatabase db = MainWindow::ConnectDatabase();
    if (!db.isOpen()) {
        qDebug() << "Failed to open the database!";
        return;
    }

    QSqlQuery query(db);
    query.prepare("INSERT INTO SalesTransactionItems (invoice_number, product_name, rate, units, amount, account_name) "
                  "VALUES (:invoice_number, :product_name, :rate, :units, :amount, :account_name)");

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
        query.bindValue(":invoice_number", invoiceNumber);
        query.bindValue(":product_name", productName);
        query.bindValue(":rate", rate);
        query.bindValue(":units", units);
        query.bindValue(":amount", amount);
        query.bindValue(":account_name", accountName); // Bind account name

        // Execute the query
        if (!query.exec()) {
            qDebug() << "Failed to insert sales transaction item:" << query.lastError().text();
        } else {
            qDebug() << "Inserted row for product:" << productName;
        }
    }
    db.close();
}


void CreateInvoice::saveSalesTransaction() {
    // Get the invoice number from QLineEdit
    QString invoiceNumber = ui->ReadInvoiceNo->text();

    if (invoiceNumber.isEmpty()) {
        QMessageBox::warning(this, "Input Error", "Please enter an invoice number.");
        return;
    }

    // Get customer details from the UI
    QString customerName = ui->ReadCustomerName->text(); // Replace with your actual UI element
    QString customerAccount = ui->ShowAccounts->currentText();
    QDate issueDate = ui->ReadIssueDate->date(); // Assuming a QDateEdit for issue date
    QDate dueDate = ui->ReadDueDate->date(); // Assuming a QDateEdit for due date
    QString totalAmount = ui->TotalAmount->text(); // Initialize total amount
    QString receivedAmount = "0.00"; // Set initial received amount to 0, adjust if you have a UI for this

    // Get account ID based on the customer account (replace with actual retrieval logic)
    int accountId = ChartOfAccountWindow::getAccountIdFromAccountName(customerAccount); // Define this method to fetch the account ID

    // Connect to the database
    QSqlDatabase db = MainWindow::ConnectDatabase();
    if (!db.isOpen()) {
        qDebug() << "Failed to open the database!";
        return;
    }

    // Prepare SQL query for inserting the sales transaction
    QSqlQuery query(db);
    query.prepare("INSERT INTO SalesTransactions (invoice_number, customer_name, customer_account, "
                  "issue_date, due_date, total_amount, received_amount, remaining_amount, account_id) "
                  "VALUES (:invoice_number, :customer_name, :customer_account, "
                  ":issue_date, :due_date, :total_amount, :received_amount, :remaining_amount, :account_id)");

    // Bind values
    query.bindValue(":invoice_number", invoiceNumber);
    query.bindValue(":customer_name", customerName);
    query.bindValue(":customer_account", customerAccount);
    query.bindValue(":issue_date", issueDate);
    query.bindValue(":due_date", dueDate);
    query.bindValue(":total_amount", totalAmount.toDouble());
    query.bindValue(":received_amount", receivedAmount.toDouble());
    query.bindValue(":remaining_amount", totalAmount.toDouble() - receivedAmount.toDouble());
    query.bindValue(":account_id", accountId);

    // Execute the query for inserting the sales transaction
    if (!query.exec()) {
        qDebug() << "Failed to insert sales transaction:" << query.lastError().text();
    } else {
        qDebug() << "Inserted sales transaction for invoice:" << invoiceNumber;

        // Now update the remaining_amount if necessary (although this is done in the insert above)
        QSqlQuery updateQuery(db);
        updateQuery.prepare("UPDATE SalesTransactions "
                            "SET remaining_amount = total_amount - received_amount "
                            "WHERE invoice_number = :invoice_number");
        updateQuery.bindValue(":invoice_number", invoiceNumber);

        // Execute the update query
        if (!updateQuery.exec()) {
            qDebug() << "Failed to update remaining amount for invoice:" << query.lastError().text();
        } else {
            qDebug() << "Updated remaining amount for invoice:" << invoiceNumber;
        }
    }

    // Close the database connection
    db.close();
}



void CreateInvoice::on_CancelButton_clicked()
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




void CreateInvoice::on_SaveButton_clicked()
{
    saveSalesTransaction();
    saveTransactionItems();
    MainWindow *MainWin=new MainWindow();
    QSize currentSize = this->size();
    QPoint currentPosition = this->pos();
    MainWin->resize(currentSize);
    MainWin->move(currentPosition);
    MainWin->show();
    this->close();
    delete this;
}

