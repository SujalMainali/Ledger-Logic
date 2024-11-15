#include "ReadSupplierPayment.h"
#include "ui_ReadSupplierPayment.h"
#include "mainwindow.h"
#include "invoicebillfunctions.h"
#include <QSql>
#include <QSqlError>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QDebug>
#include <QMessageBox>
#include <QComboBox>

ReadSupplierPayment::ReadSupplierPayment(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::ReadSupplierPayment)
{
    ui->setupUi(this);
    QSqlDatabase db = MainWindow::db;
    if (db.isOpen()) {
        qDebug() << "Database Opened";
        QSqlQuery Loadquery(db);  // Ensure the query is associated with the correct DB connection
        Loadquery.prepare("SELECT bill_number, supplier_name, due_date, remaining_amount FROM BillTransactions WHERE remaining_amount > 0");


        InvoiceBillFunctions::loadDueBills(ui->BillsTable, Loadquery,db);
    } else {
        QMessageBox::critical(this, "Database Error", "Failed to open database connection.");
    }
    InvoiceBillFunctions::populateComboBoxWithAccounts(ui->BankAccount,db);
    ui->ButtonsFrame->setVisible(false);

}

ReadSupplierPayment::~ReadSupplierPayment()
{
    delete ui;
}



void ReadSupplierPayment::on_BillsTable_cellDoubleClicked(int row, int column)
{
    // Check if the "Additional Payment" column already exists
    int columnCount = ui->BillsTable->columnCount();
    bool additionalPaymentColumnExists = false;

    for (int i = 0; i < columnCount; ++i) {
        if (ui->BillsTable->horizontalHeaderItem(i)->text() == "Additional Payment") {
            additionalPaymentColumnExists = true;
            break;
        }
    }

    // Add the "Additional Payment" column if it does not exist
    if (!additionalPaymentColumnExists) {
        ui->BillsTable->insertColumn(columnCount);
        ui->BillsTable->setHorizontalHeaderItem(columnCount, new QTableWidgetItem("Additional Payment"));

        // Optionally, set default values or placeholders in the new column for each row
        for (int i = 0; i < ui->BillsTable->rowCount(); ++i) {
            ui->BillsTable->setItem(i, columnCount, new QTableWidgetItem("0.00"));
        }
    }
    ui->ButtonsFrame->setVisible(true);
}


void ReadSupplierPayment::on_Save_clicked()
{
    QSqlDatabase db;
    db=MainWindow::db;
    QSqlQuery query,Loadquery;
    Loadquery.prepare("SELECT bill_number, supplier_name, due_date, remaining_amount FROM BillTransactions WHERE remaining_amount > 0");

    query.prepare("UPDATE BillTransactions SET paid_amount = paid_amount + :additionalPayment, remaining_amount = remaining_amount - :additionalPayment WHERE bill_number = :billNumber");
    InvoiceBillFunctions::saveAdditionalPaymentsToDatabase(ui->BillsTable,ui->BankAccount,query,Loadquery,db,false);

}

void ReadSupplierPayment::on_Cancel_clicked()
{
    int columnCount = ui->BillsTable->columnCount();
    bool additionalPaymentColumnExists = false;
    int additionalPaymentColumnIndex = -1;

    // Check for the "Additional Payment" column and store its index
    for (int i = 0; i < columnCount; ++i) {
        if (ui->BillsTable->horizontalHeaderItem(i)->text() == "Additional Payment") {
            additionalPaymentColumnExists = true;
            additionalPaymentColumnIndex = i;
            break;
        }
    }

    // Remove the "Additional Payment" column if it exists
    if (additionalPaymentColumnExists) {
        ui->BillsTable->removeColumn(additionalPaymentColumnIndex);
    }
    ui->ButtonsFrame->setVisible(false);
}


void ReadSupplierPayment::on_pushButton_clicked()
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



