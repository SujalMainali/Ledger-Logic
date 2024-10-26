#include "create1.h"
#include "./ui_create1.h"
#include "mainwindow.h"
#include <QSql>
#include <QDebug>

CreateInvoice::CreateInvoice(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::CreateInvoice)
{
    ui->setupUi(this);
    populateComboBoxWithAccounts(ui->ShowAccounts);
    setComboBoxInCell(0,2);
}

CreateInvoice::~CreateInvoice()
{
    delete ui;
}

void CreateInvoice::on_ItemsTable_cellChanged(int row, int column)
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
//           updateAmountInTable(ui->ItemsTable->rowCount() - 1);
//            showTotalAmount();
            ui->ItemsTable->insertRow(ui->ItemsTable->rowCount());
            setComboBoxInCell(ui->ItemsTable->rowCount() - 1, 2);

        }
    }
}



void CreateInvoice::saveTransactionItems() {
    // Get the invoice number from QLineEdit
    QString invoiceNumber = ui->ReadInvoiceNo->text();

    if (invoiceNumber.isEmpty()) {
        QMessageBox::warning(this, "Input Error", "Please enter an invoice number.");
        return;
    }

    // Connect to the database
    QSqlDatabase db = MainWindow::ConnectDatabase();
    if (!db.isOpen()) {
        qDebug() << "Failed to open the database!";
        return;
    }

    // Prepare SQL query
    QSqlQuery query(db);
    query.prepare("INSERT INTO SalesTransactionItems (invoice_number, product_name, rate, units, amount, account_name) "
                  "VALUES (:invoice_number, :product_name, :rate, :units, :amount, :account_name)");

    // Loop through each row in the table to read the product details
    int rowCount = ui->ItemsTable->rowCount();
    for (int row = 0; row < rowCount; ++row) {
        // Read product details from the QTableWidget/QTableView
        QString productName = ui->ItemsTable->item(row, 0)->text(); // Assuming first column is product name
        double rate = ui->ItemsTable->item(row, 3)->text().toDouble(); // Assuming second column is rate
        int units = ui->ItemsTable->item(row, 4)->text().toInt(); // Assuming third column is units
        double amount = ui->ItemsTable->item(row, 5)->text().toDouble(); // Assuming fourth column is amount

        // Retrieve the QComboBox from the table cell
        QComboBox *comboBox = qobject_cast<QComboBox*>(ui->ItemsTable->cellWidget(row, 2)); // Assuming the account name is in column 2
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

    // Close the database connection
    db.close();
}


void CreateInvoice::setComboBoxInCell(int row, int column) {
    // Create a new QComboBox
    QComboBox *comboBox = new QComboBox(this);
    populateComboBoxWithAccounts(comboBox);

    comboBox->setStyleSheet("background-color:rgb(209,212,203);");
    // Set the combo box as the cell widget
    ui->ItemsTable->setCellWidget(row, column, comboBox);

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


    // Get account ID based on the customer account (replace with actual retrieval logic)
    int accountId = getAccountIdFromAccountName(customerAccount); // Define this method to fetch the account ID

    // Connect to the database
    QSqlDatabase db = MainWindow::ConnectDatabase();
    if (!db.isOpen()) {
        qDebug() << "Failed to open the database!";
        return;
    }

    // Prepare SQL query
    QSqlQuery query(db);
    query.prepare("INSERT INTO SalesTransactions (invoice_number, customer_name, customer_account, "
                  "issue_date, due_date, total_amount, account_id) "
                  "VALUES (:invoice_number, :customer_name, :customer_account, "
                  ":issue_date, :due_date, :total_amount, :account_id)");

    // Bind values
    query.bindValue(":invoice_number", invoiceNumber);
    query.bindValue(":customer_name", customerName);
    query.bindValue(":customer_account", customerAccount);
    query.bindValue(":issue_date", issueDate);
    query.bindValue(":due_date", dueDate);
    query.bindValue(":total_amount", totalAmount.toDouble());
    query.bindValue(":account_id", accountId);

    // Execute the query
    if (!query.exec()) {
        qDebug() << "Failed to insert sales transaction:" << query.lastError().text();
    } else {
        qDebug() << "Inserted sales transaction for invoice:" << invoiceNumber;
    }

    // Close the database connection
    db.close();
}

// Helper function to get account ID based on account name
int CreateInvoice::getAccountIdFromAccountName(const QString &accountName) {
    int accountId = -1; // Default to -1 if not found
    QSqlDatabase db = MainWindow::ConnectDatabase();
    if (!db.isOpen()) {
        qDebug() << "Failed to open the database for account retrieval!";
        return accountId;
    }

    QSqlQuery query(db);
    query.prepare("SELECT account_id FROM ChartOfAccounts WHERE account_name = :account_name");
    query.bindValue(":account_name", accountName);

    if (query.exec() && query.next()) {
        accountId = query.value(0).toInt(); // Retrieve the account ID
    } else {
        qDebug() << "Failed to retrieve account ID:" << query.lastError().text();
    }

    db.close();
    return accountId;
}

void CreateInvoice::populateComboBoxWithAccounts(QComboBox *comboBox) {
    QSqlDatabase db= MainWindow::ConnectDatabase();
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
        qDebug() << "No accounts found in the ChartOfAccounts table.";
    }
    db.close();
}

void CreateInvoice::updateAmountInTable(int row) {
    // Check if the row is valid
    qDebug() << "Inside the function.";
    if (row < 0 || row >= ui->ItemsTable->rowCount()) {
        qDebug() << "Invalid row index.";
        return;
    }

    // Retrieve rate and units from the corresponding cells
    QTableWidgetItem *rateItem = ui->ItemsTable->item(row, 3);
    QTableWidgetItem *unitsItem = ui->ItemsTable->item(row, 4);
    qDebug() << "Created the items.";

    if (!rateItem || !unitsItem) {
        qDebug() << "Rate or units item is null.";
        return;
    }

    double rate = rateItem->text().toDouble(); // Assuming the rate is in column 3
    int units = unitsItem->text().toInt(); // Assuming units are in column 4

    // Calculate the amount
    double amount = rate * units;

    // Update the amount in the corresponding cell (assuming amount is in column 5)
    QTableWidgetItem *amountItem = new QTableWidgetItem(QString::number(amount, 'f', 2)); // 2 decimal places
    ui->ItemsTable->setItem(row, 5, amountItem); // Set the calculated amount in the amount column
}


void CreateInvoice::showTotalAmount() {
    double totalAmount = 0.0;

    // Loop through each row in the table to read the product details
    int rowCount = ui->ItemsTable->rowCount();
    for (int row = 0; row < rowCount; ++row) {
        // Get the amount from the table
        double amount = ui->ItemsTable->item(row, 5)->text().toDouble(); // Assuming fourth column is amount

        // Accumulate the total amount
        totalAmount += amount; // Ensure that amount is properly calculated
    }

    ui->TotalAmount->setText(QString::number(totalAmount, 'f', 2));
}




void CreateInvoice::on_pushButton_clicked()
{
    MainWindow *MainWin=new MainWindow();
    QSize currentSize = this->size();
    QPoint currentPosition = this->pos();
    MainWin->resize(currentSize);
    MainWin->move(currentPosition);
    MainWin->show();
    this->close();
}

