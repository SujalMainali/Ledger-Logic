#include "readpayment.h"
#include "./ui_readpayment.h"
#include "mainwindow.h"
#include "invoicebillfunctions.h"


ReadPayment::ReadPayment(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::ReadPayment)
{
    ui->setupUi(this);
    QSqlDatabase db=MainWindow::db;
    QSqlQuery loadQuery(db);
    loadQuery.prepare("SELECT invoice_number, customer_name, due_date, remaining_amount FROM SalesTransactions WHERE remaining_amount > 0");
    InvoiceBillFunctions::loadDueBills(ui->InvoiceTable,loadQuery,db);
    InvoiceBillFunctions::populateComboBoxWithAccounts(ui->ReadBankAccount,db);
    ui->ButtonFrame->setVisible(false);

}

ReadPayment::~ReadPayment()
{
    delete ui;
}

void ReadPayment::on_pushButton_clicked()
{
    MainWindow *MainWin=new MainWindow();
    QSize currentSize = this->size();
    QPoint currentPosition = this->pos();
    MainWin->resize(currentSize);
    MainWin->move(currentPosition);
    MainWin->show();
    this->close();
}


void ReadPayment::on_InvoiceTable_cellDoubleClicked(int row, int column)
{
    // Check if the "Additional Payment" column already exists
    int columnCount = ui->InvoiceTable->columnCount();
    bool additionalPaymentColumnExists = false;

    for (int i = 0; i < columnCount; ++i) {
        if (ui->InvoiceTable->horizontalHeaderItem(i)->text() == "Additional Payment") {
            additionalPaymentColumnExists = true;
            break;
        }
    }

    // Add the "Additional Payment" column if it does not exist
    if (!additionalPaymentColumnExists) {
        ui->InvoiceTable->insertColumn(columnCount);
        ui->InvoiceTable->setHorizontalHeaderItem(columnCount, new QTableWidgetItem("Additional Payment"));

        // Optionally, set default values or placeholders in the new column for each row
        for (int i = 0; i < ui->InvoiceTable->rowCount(); ++i) {
            ui->InvoiceTable->setItem(i, columnCount, new QTableWidgetItem("0.00"));
        }
    }
    ui->ButtonFrame->setVisible(true);
}



void ReadPayment::on_Save_clicked()
{
    try{
        QSqlDatabase db;
        db = MainWindow::db;
        QSqlQuery query, Loadquery;

        // Load query to fetch the sales transactions where payments are due
        Loadquery.prepare("SELECT invoice_number, customer_name, due_date, remaining_amount FROM SalesTransactions WHERE remaining_amount > 0");

        // Update query to record additional payments made against an invoice
        query.prepare("UPDATE SalesTransactions SET received_amount = received_amount + :additionalPayment, remaining_amount = remaining_amount - :additionalPayment WHERE invoice_number = :billNumber");

        InvoiceBillFunctions::saveAdditionalPaymentsToDatabase(ui->InvoiceTable,ui->ReadBankAccount, query, Loadquery,db,true);
    }
    catch (const std::exception &e) {
        QMessageBox *msgBox=MainWindow::createStyledMessageBox("Error","An error occurred while saving:",e.what());
        msgBox->exec();
    }
    catch (...) {
        QMessageBox *msgBox=MainWindow::createStyledMessageBox("Error","UnknownErrorOccured","");;
        msgBox->exec();
    }

}


void ReadPayment::on_Cancel_clicked()
{
    int columnCount = ui->InvoiceTable->columnCount();
    bool additionalPaymentColumnExists = false;
    int additionalPaymentColumnIndex = -1;

    // Check for the "Additional Payment" column and store its index
    for (int i = 0; i < columnCount; ++i) {
        if (ui->InvoiceTable->horizontalHeaderItem(i)->text() == "Additional Payment") {
            additionalPaymentColumnExists = true;
            additionalPaymentColumnIndex = i;
            break;
        }
    }

    // Remove the "Additional Payment" column if it exists
    if (additionalPaymentColumnExists) {
        ui->InvoiceTable->removeColumn(additionalPaymentColumnIndex);
    }
    ui->ButtonFrame->setVisible(false);
}

