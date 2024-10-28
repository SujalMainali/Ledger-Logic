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
            qDebug() << "Fetched row:" << query.value(0).toString(); // Debug output

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
void InvoiceBillFunctions::saveAdditionalPaymentsToDatabase(QTableWidget *Table, QSqlQuery &query,QSqlQuery &LoadQuery,QSqlDatabase &db)
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

            // Refresh the table to reflect changes
            loadDueBills(Table, LoadQuery,db);
        }
    }
}





//These are the functions for Creating Bills and Invoices





void InvoiceBillFunctions::TableDataEntry(QTableWidget* Table,int row, int column, QLineEdit* Total){
    QSqlDatabase db= MainWindow::ConnectDatabase();
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
    db.close();
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






