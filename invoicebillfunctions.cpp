#include "invoicebillfunctions.h"
#include "mainwindow.h"
#include <QtWidgets>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>

InvoiceBillFunctions::InvoiceBillFunctions()
{
}

//These are the functions for Reading Payment


// Static method to load due bills
void InvoiceBillFunctions::loadDueBills(QTableWidget *Table, QSqlQuery &query, QSqlDatabase &db)
{
    // Clear the existing rows in the table
    Table->setRowCount(0);

    // Debug: Check if query is prepared correctly
    if (!query.isActive()) {
        qDebug() << "Query not active. Check if the database connection is valid.";
    }

    // Execute the query
    if (query.exec()) {
        int row = 0;
        while (query.next()) {

            // Insert a new row in the table for each result
            Table->insertRow(row);

            // Get data from query
            QString billNumber = query.value(0).toString();
            QString supplierName = query.value(1).toString();
            QString dueDate = query.value(2).toString();
            QString remainingAmount = query.value(3).toString();

            // Set data to the table cells
            Table->setItem(row, 0, new QTableWidgetItem(billNumber));
            Table->setItem(row, 1, new QTableWidgetItem(supplierName));
            Table->setItem(row, 2, new QTableWidgetItem(dueDate));
            Table->setItem(row, 3, new QTableWidgetItem(remainingAmount));
            InvoiceBillFunctions::setComboBoxInCell(Table, row, 4,db);

            row++;
        }

        // After the loop, check for errors if the query terminated unexpectedly
        if (query.lastError().isValid()) {
            qDebug() << "Query Error:" << query.lastError().text();
        }


        // Adjust the table height to fit all rows
        int newHeight = (row + 1) * 35; // Calculate new height for the table
        Table->setFixedHeight(newHeight);
    } else {
        // Handle query error
        qDebug() << "Query failed: " << query.lastError().text(); // Debug error message
        QMessageBox::critical(nullptr, "Database Error", query.lastError().text());
    }
}


// Static method to set a combo box in a table cell
void InvoiceBillFunctions::setComboBoxInCell(QTableWidget *Table, int row, int column,QSqlDatabase &db) {
    // Create a new QComboBox
    QComboBox *comboBox = new QComboBox();
    InvoiceBillFunctions::populateComboBoxWithAccounts(comboBox,db);

    comboBox->setStyleSheet("background-color:rgb(209,212,203);");
    // Set the combo box as the cell widget
    Table->setCellWidget(row, column, comboBox);
}

// Static method to populate the combo box with account names
void InvoiceBillFunctions::populateComboBoxWithAccounts(QComboBox *comboBox,QSqlDatabase &db) {
    // Prepare and execute the query

    QSqlQuery query(db);
    QString baseQuery = "SELECT account_name FROM ChartOfAccounts";
    query.prepare(baseQuery);

    if (!query.exec()) {
        qDebug() << "Failed to fetch account names:" << query.lastError().text();
        return;
    }

    // Clear existing items in the combo box (if any)
    comboBox->clear();

    // Iterate through the query result and add account names to the combo box
    while (query.next()) {
        QString accountName = query.value(0).toString();
        comboBox->addItem(accountName);
    }

    // Check if any items were added
    if (comboBox->count() == 0) {
        qDebug() << "No accounts found in the database.";
    }
}

// Static method to save additional payments to the database
void InvoiceBillFunctions::saveAdditionalPaymentsToDatabase(QTableWidget *Table,QComboBox *BankAccount, QSqlQuery &query,QSqlQuery &LoadQuery,QSqlDatabase &db,bool isINvoice)
{
    // Get the currently selected row
    int selectedRow = Table->currentRow();
    if (selectedRow == -1) {
        QMessageBox::warning(nullptr, "No Selection", "Please select a bill entry to update.");
        return;
    }

    // Retrieve the items for the selected row
    QTableWidgetItem *billNumberItem = Table->item(selectedRow, 0); // Assuming Bill Number is in column 0
    QTableWidgetItem *additionalPaymentItem = Table->item(selectedRow, Table->columnCount() - 1); // Assuming "Additional Payment" is the last column

    if (billNumberItem && additionalPaymentItem) {
        QString billNumber = billNumberItem->text();
        double additionalPayment = additionalPaymentItem->text().toDouble();

        // Check if the additional payment is valid
        if (additionalPayment <= 0) {
            QMessageBox::warning(nullptr, "Invalid Input", "Please enter a valid additional payment amount.");
            return;
        }

        // Bind values to the query passed as a parameter
        query.bindValue(":additionalPayment", additionalPayment);
        query.bindValue(":billNumber", billNumber);

        // Execute the query and check for errors
        if (!query.exec()) {
            QMessageBox::critical(nullptr, "Database Error", "Failed to update the database: " + query.lastError().text());
        } else {
            QMessageBox::information(nullptr, "Success", "Additional payment has been updated successfully.");
            InvoiceBillFunctions::createJournalEntryForPayment(BankAccount,billNumber,additionalPayment,db,isINvoice);

            // Refresh the table to reflect changes
            loadDueBills(Table, LoadQuery,db);
        }
    }
}

void InvoiceBillFunctions::createJournalEntryForPayment( QComboBox *BankAccount,const QString &invoiceNumber, double paymentAmount,QSqlDatabase &db,bool isINvoice) {



    QSqlQuery query(db);
    if(isINvoice){
        // Step 1: Fetch Customer Account ID and Customer Name from SalesTransactions
        query.prepare("SELECT customer_name, customer_account FROM SalesTransactions WHERE invoice_number = :invoice_number");
        query.bindValue(":invoice_number", invoiceNumber);
    }
    else{
        query.prepare("SELECT supplier_name, supplier_account FROM BillTransactions WHERE bill_number = :invoice_number");
        query.bindValue(":invoice_number", invoiceNumber);
    }

    QString customerName;
    QString customerAccount;
    if (query.exec() && query.next()) {
        if(isINvoice){
            customerName = query.value("customer_name").toString();
            customerAccount = query.value("customer_account").toString();  // Assuming there's a customer_account column
        }
        else{
            customerName = query.value("supplier_name").toString();
            customerAccount = query.value("supplier_account").toString();  // Assuming there's a customer_account column
        }

    } else {
        qDebug() << "Failed to fetch customer details for invoice:" << query.lastError().text();
        return;
    }

    // Step 2: Fetch Bank Account ID from ComboBox
    QString bankAccountName =BankAccount->currentText();
    int bankAccountId = ChartOfAccountWindow::getAccountIdFromAccountName(bankAccountName);

    if (bankAccountId == -1) {
        qDebug() << "Invalid bank account selected!";
        return;
    }

    // Step 3: Create a Journal Entry for the Payment
    QString journalNumber = (isINvoice)?"PAYINV" + invoiceNumber.mid(4):"PAYBILL"+invoiceNumber.mid(4); // Extracting the integer part of the invoice number
    QDate paymentDate = QDate::currentDate();
    QString journalMemo = (isINvoice)?"Payment for Invoice " + invoiceNumber:"Payment for Invoice " + invoiceNumber;

    // Insert Journal Entry into JournalEntries Table
    query.prepare("INSERT INTO JournalEntries (journal_number, date, memo) "
                  "VALUES (:journal_number, :date, :memo)");
    query.bindValue(":journal_number", journalNumber);
    query.bindValue(":date", paymentDate);
    query.bindValue(":memo", journalMemo);

    if (!query.exec()) {
        qDebug() << "Failed to insert journal entry:" << query.lastError().text();
        return;
    }

    int journalId = query.lastInsertId().toInt();

    // Step 4: Debit Bank Account with Payment Amount
    QSqlQuery lineQuery(db);
    lineQuery.prepare("INSERT INTO JournalEntryLines (journal_id, account_id, amount, is_debit) "
                      "VALUES (:journal_id, :account_id, :amount, :is_debit)");
    lineQuery.bindValue(":journal_id", journalId);
    lineQuery.bindValue(":account_id", bankAccountId);
    lineQuery.bindValue(":amount", paymentAmount);
    lineQuery.bindValue(":is_debit", isINvoice);  // Debit bank account (is_debit = true)

    if (!lineQuery.exec()) {
        qDebug() << "Failed to insert debit line for bank account:" << lineQuery.lastError().text();
        return;
    }

    // Step 5: Credit Customer Account
    // Assuming customerAccount is the account name for the customer
    int customerAccountId = ChartOfAccountWindow::getAccountIdFromAccountName(customerAccount);
    if (customerAccountId == -1) {
        qDebug() << "Failed to get customer account ID for customer:" << customerName;
        return;
    }

    QSqlQuery creditLineQuery(db);
    creditLineQuery.prepare("INSERT INTO JournalEntryLines (journal_id, account_id, amount, is_debit) "
                            "VALUES (:journal_id, :account_id, :amount, :is_debit)");
    creditLineQuery.bindValue(":journal_id", journalId);
    creditLineQuery.bindValue(":account_id", customerAccountId);
    creditLineQuery.bindValue(":amount", paymentAmount);
    creditLineQuery.bindValue(":is_debit", !isINvoice);  // Credit customer account (is_debit = false)

    if (!creditLineQuery.exec()) {
        qDebug() << "Failed to insert credit line for customer account:" << creditLineQuery.lastError().text();
        return;
    }

}




//These are the functions for Creating Bills and Invoices





void InvoiceBillFunctions::TableDataEntry(QTableWidget* Table,int row, int column, QLineEdit* Total){
    QSqlDatabase db= MainWindow::db;
    int totalColumns = Table->columnCount();

    // Check if the change is in the last row
    if (row == Table->rowCount() - 1)
    {
        // Check if all the columns in the last row up to index 4 are filled, except for column 2
        bool allFilled = true;
        for (int col = 0; col < qMin(totalColumns, 5); ++col)  // Check only the first five columns
        {
            QTableWidgetItem *item = Table->item(row, col);
            // Skip column 2 check
            if (col != 2 && (!item || item->text().trimmed().isEmpty()))
            {
                allFilled = false;
                break;
            }
        }

        // If all relevant cells in the last row are filled, add a new row
        if (allFilled)
        {
            int row = Table->rowCount();
            Table->blockSignals(true);
            InvoiceBillFunctions::updateAmountInTable(Table,row-1);
            InvoiceBillFunctions::showTotalAmount(Table,Total);
            Table->blockSignals(false);
            Table->insertRow(row);
            InvoiceBillFunctions::setComboBoxInCell(Table,row, 2,db);

            int rowHeight = 35; // Set the height for each row
            int newHeight = (row+2) * rowHeight; // Calculate new height for the table
            Table->setFixedHeight(newHeight);

        }
    }
}
void InvoiceBillFunctions::updateAmountInTable(QTableWidget *Table, int row){
    if (row < 0 || row >= Table->rowCount()) {
        return; // Invalid row
    }

    // Get the rate and units to calculate the amount
    double rate = Table->item(row, 3)->text().toDouble();
    int units = Table->item(row, 4)->text().toInt();
    double amount = rate * units;

    // Set the amount in the corresponding cell
    QTableWidgetItem *amountItem = new QTableWidgetItem(QString::number(amount, 'f', 2));
    Table->setItem(row, 5, amountItem); // Assuming amount is in column 5
}

void InvoiceBillFunctions::showTotalAmount(QTableWidget *Table,QLineEdit *Total) {
    double totalAmount = 0.0;

    // Calculate the total amount from the table
    for (int row = 0; row < Table->rowCount(); ++row) {
        totalAmount += Table->item(row, 5)->text().toDouble(); // Assuming amount is in column 5
    }

    Total->setText(QString::number(totalAmount, 'f', 2)); // Assuming you have a QLabel or QLineEdit for total amount
}






