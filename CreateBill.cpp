#include "CreateBill.h"
#include "mainwindow.h"
#include "chartofaccountwindow.h"
#include "./ui_CreateBill.h"
#include <QSql>
#include <QSqlDatabase>
#include <QSqlQuery>

CreateBill::CreateBill(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::CreateBill)
{
    ui->setupUi(this);
    setComboBoxInCell(0, 2);
    populateComboBoxWithAccounts(ui->ShowAccounts);
}

CreateBill::~CreateBill()
{
    delete ui;
}

void CreateBill::on_ItemsTable_cellChanged(int row, int column)
{
    // Get the total number of columns in the table
        int totalColumns = ui->ItemsTable->columnCount();

        // Check if the change is in the last row
        if (row == ui->ItemsTable->rowCount() - 1)
        {
            // Check if all the columns in the last row up to index 4 are filled, except for column 2
            bool allFilled = true;
            for (int col = 0; col < qMin(totalColumns, 5); ++col)  // Check only the first five columns
            {
                QTableWidgetItem *item = ui->ItemsTable->item(row, col);
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
                int row = ui->ItemsTable->rowCount();
                ui->ItemsTable->blockSignals(true);
                updateAmountInTable(row-1);
                showTotalAmount();
                ui->ItemsTable->blockSignals(false);
                ui->ItemsTable->insertRow(row);
                setComboBoxInCell(row, 2);
                //ui->ItemsTable->resizeRowsToContents();

                int rowHeight = 35; // Set the height for each row
                int newHeight = (row+2) * rowHeight; // Calculate new height for the table
                ui->ItemsTable->setFixedHeight(newHeight);

            }
        }
}

void CreateBill::setComboBoxInCell(int row, int column) {
    // Create a new QComboBox
    QComboBox *comboBox = new QComboBox(this);
    populateComboBoxWithAccounts(comboBox);

    comboBox->setStyleSheet("background-color:rgb(209,212,203);");
    // Set the combo box as the cell widget
    ui->ItemsTable->setCellWidget(row, column, comboBox);
}

void CreateBill::updateAmountInTable(int row) {
    if (row < 0 || row >= ui->ItemsTable->rowCount()) {
        return; // Invalid row
    }

    // Get the rate and units to calculate the amount
    double rate = ui->ItemsTable->item(row, 3)->text().toDouble();
    int units = ui->ItemsTable->item(row, 4)->text().toInt();
    double amount = rate * units;

    // Set the amount in the corresponding cell
    QTableWidgetItem *amountItem = new QTableWidgetItem(QString::number(amount, 'f', 2));
    ui->ItemsTable->setItem(row, 5, amountItem); // Assuming amount is in column 5
}

void CreateBill::showTotalAmount() {
    double totalAmount = 0.0;

    // Calculate the total amount from the table
    for (int row = 0; row < ui->ItemsTable->rowCount(); ++row) {
        totalAmount += ui->ItemsTable->item(row, 5)->text().toDouble(); // Assuming amount is in column 5
    }

    ui->Total->setText(QString::number(totalAmount, 'f', 2)); // Assuming you have a QLabel or QLineEdit for total amount
}

void CreateBill::populateComboBoxWithAccounts(QComboBox *comboBox) {
    QSqlDatabase db = MainWindow::ConnectDatabase();
    if (!db.isOpen()) {
        qDebug() << "Failed to open the database!";
        return;
    }

    // Prepare and execute the query
    QSqlQuery query;
    query.prepare("SELECT account_name FROM ChartOfAccounts");

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

    db.close();
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

    // Connect to the database
    QSqlDatabase db = MainWindow::ConnectDatabase();
    if (!db.isOpen()) {
        qDebug() << "Failed to open the database!";
        return;
    }

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

    // Close the database connection
    db.close();
}

void CreateBill::saveBillTransactionItems() {
    QString billNumber = ui->ReadBillNumber->text();

    if (billNumber.isEmpty()) {
        QMessageBox::warning(this, "Input Error", "Please enter a bill number.");
        return;
    }

    QSqlDatabase db = MainWindow::ConnectDatabase();
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
    db.close();
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
    MainWindow *MainWin=new MainWindow();
    QSize currentSize = this->size();
    QPoint currentPosition = this->pos();
    MainWin->resize(currentSize);
    MainWin->move(currentPosition);
    MainWin->show();
    this->close();
    delete this;
}

