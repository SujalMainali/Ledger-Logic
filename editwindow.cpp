#include "editwindow.h"
#include "./ui_editwindow.h"
#include<QtSql>
#include "mainwindow.h"
#include "chartofaccountwindow.h"
#include "CreateJournal.h"



EditWindow::EditWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::EditWindow)
{
    ui->setupUi(this);
}

EditWindow::~EditWindow()
{
    delete ui;
}

int16_t EditWindow::GetTypeIdFromType(QString type){
        if(type=="ASSETS") return 1;
        else if(type=="LIABILITIES") return 2;
        else if(type=="EQUITY") return 3;
        else return -1;
    }


void EditWindow::ShowChildAccountDetail(int16_t currentAccountId){
        PopulateSelectHeader();

        QSqlQuery query;
        query.prepare("SELECT account_id, account_name, balance, type, parent_header FROM ChartOfAccounts WHERE account_id = :account_id");
        query.bindValue(":account_id", currentAccountId);

        if (query.exec() && query.next()) {
            // Set the line edits with account details
            ui->ReadName->setText(query.value("account_name").toString());
            ui->ReadCode->setText(query.value("account_id").toString());
            ui->ReadBalance->setText(QString::number(query.value("balance").toDouble(), 'f', 2));

            // Set the combo box selection for type and parent header
            QString accountType = query.value("type").toString();
            QString parentHeader = query.value("parent_header").toString();

            int typeIndex = ui->ReadType->findText(accountType);
            if (typeIndex != -1) {
                ui->ReadType->setCurrentIndex(typeIndex);
            }

            int headerIndex = ui->ReadHeader->findText(parentHeader);
            if (headerIndex != -1) {
                ui->ReadHeader->setCurrentIndex(headerIndex);
            }

            // Pre-select checkboxes based on type
            if (parentHeader.isEmpty()) {
                ui->ParentCheckbox->setChecked(true);
                ui->ChildCheckbox->setChecked(false);
            } else {
                ui->ChildCheckbox->setChecked(true);
                ui->ParentCheckbox->setChecked(false);
            }
        } else {
            qDebug() << "Failed to load account details:" << query.lastError().text();
        }
}

void EditWindow::ShowParentAccountDetail(int8_t currentAccountId){
    PopulateSelectHeader();
    QSqlQuery query;
    query.prepare("SELECT parent_id, parent_name, type, type_id FROM ParentAccounts WHERE parent_id = :parent_id");
    query.bindValue(":parent_id", currentAccountId);

    if (query.exec() && query.next()) {
        ui->ReadName->setText(query.value("parent_name").toString());
        ui->ReadCode->setText(query.value("parent_id").toString());

        // Set the combo box selection for type
        QString accountType = query.value("type").toString();
        int typeIndex = ui->ReadType->findText(accountType);
        if (typeIndex != -1) {
            ui->ReadType->setCurrentIndex(typeIndex);
        }



        // Pre-select the parent checkbox
        ui->ParentCheckbox->setChecked(true);
        ui->ChildCheckbox->setChecked(false);

        // Hide any fields or frames that are specific to child accounts if needed
        ui->BalanceFrame->setVisible(false);
        ui->ParentFrame->setVisible(false);
    } else {
        qDebug() << "Failed to load parent account details:" << query.lastError().text();
    }
}





void EditWindow::PopulateSelectHeader(){
        ui->ReadHeader->clear();
       // Prepare and execute the query to fetch parent headers
       QSqlQuery query;
       query.prepare("SELECT parent_name FROM ParentAccounts");

       if (!query.exec()) {
           qDebug() << "Error fetching parent headers: " << query.lastError().text();
           return;
       }

       // Add each parent header to the combo box
       while (query.next()) {
           QString parentName = query.value("parent_name").toString();
           ui->ReadHeader->addItem(parentName);
       }
}


void EditWindow::on_Cancel_clicked()
{
    ChartOfAccountWindow * ChartOfAccountWin= new ChartOfAccountWindow();
    QSize currentSize = this->size();
    QPoint currentPosition = this->pos();
    ChartOfAccountWin->resize(currentSize);
    ChartOfAccountWin->move(currentPosition);
    ChartOfAccountWin->show();
    this->close();
    delete this;
}


void EditWindow::on_Save_clicked() {
    bool isParentAccount = ui->ParentCheckbox->isChecked(); // Check if the parent checkbox is checked
    int16_t currentaccountId = ChartOfAccountWindow::selectedAccountId;

    // Connect to the database
    QSqlDatabase db = MainWindow::db;
    if (!db.isOpen()) {
        qDebug() << "Database connection failed!";
        return;
    }

    // Enable foreign key constraints
    QSqlQuery pragmaQuery;
    if (!pragmaQuery.exec("PRAGMA foreign_keys = ON;")) {
        qDebug() << "Failed to enable foreign keys:" << pragmaQuery.lastError().text();
        return;
    }

    QSqlQuery query;
    // Remove the old data
    if (isParentAccount) {
        qDebug() << "Parent Account";
        query.prepare("UPDATE ParentAccounts SET parent_name = :parent_name WHERE parent_id = :parent_id");
        query.bindValue(":parent_id", currentaccountId);
        query.bindValue(":parent_name", ui->ReadName->text());
    } else {
        query.prepare("UPDATE ChartOfAccounts SET account_name = :account_name, balance = :balance, type = :type, type_id = :type_id, parent_header = :parent_header WHERE account_id = :account_id");
        query.bindValue(":account_id", currentaccountId);
        query.bindValue(":account_name", ui->ReadName->text());
        query.bindValue(":balance", ui->ReadBalance->text().toDouble());
        query.bindValue(":type", ui->ReadType->currentText());
        query.bindValue(":type_id", GetTypeIdFromType(ui->ReadType->currentText()));
        query.bindValue(":parent_header", ui->ReadHeader->currentText());
        qDebug() << "Child Account";
    }

    if (!query.exec()) {
        qDebug() << "Failed to update account details:" << query.lastError().text();
        return;
    } else {
        qDebug() << "Account details updated successfully.";
    }

    if (!isParentAccount) {
        QSqlQuery balanceQuery;
        balanceQuery.prepare("INSERT INTO AccountBalances (account_id, opening_balance) "
                             "VALUES (:account_id, :opening_balance) "
                             "ON CONFLICT(account_id) DO UPDATE SET opening_balance = :opening_balance");
        balanceQuery.bindValue(":account_id", currentaccountId);
        balanceQuery.bindValue(":opening_balance", ui->ReadBalance->text().toDouble());

        if (!balanceQuery.exec()) {
            qDebug() << "Failed to update opening balance in AccountBalances:" << balanceQuery.lastError().text();
            return;
        } else {
            qDebug() << "Opening balance updated successfully in AccountBalances table.";
        }
    }

    // Close the database connection

    ChartOfAccountWindow* ChartWin = new ChartOfAccountWindow();
    QSize currentSize = this->size();
    QPoint currentPosition = this->pos();
    ChartWin->resize(currentSize);
    ChartWin->move(currentPosition);
    ChartWin->show();
    this->close();
    delete this;
}




