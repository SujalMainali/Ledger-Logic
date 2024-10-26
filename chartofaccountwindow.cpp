#include "chartofaccountwindow.h"
#include "./ui_chartofaccountwindow.h"
#include<QtSql>
#include "mainwindow.h"
#include "editwindow.h"

int16_t ChartOfAccountWindow::selectedAccountId = 0;  // Initialize the static member


ChartOfAccountWindow::ChartOfAccountWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::ChartOfAccountWindow)
{
    ui->setupUi(this);
    qDebug()<<"CHartOfAccouuntOpened";
    db=MainWindow::ConnectDatabase(); //Connecting to the database and storing the location at db
    qDebug()<<"CHartOfAccouuntDataBaseConnected";
    ui->DeleteAccountFrame->setVisible(false);
    this->displayData();

    db.close();
}

void ChartOfAccountWindow::displayData()
{
    ui->ChartOfAccount->clear();
    // Prepare query to fetch parent accounts
    QSqlQuery parentQuery;
    parentQuery.prepare("SELECT parent_id, parent_name, type FROM ParentAccounts");

    if (!parentQuery.exec()) {
        qDebug() << "Error fetching parent accounts: " << parentQuery.lastError().text();
        return;
    }


    // Loop through the parent accounts
    while (parentQuery.next()) {
        QString parentName = parentQuery.value("parent_name").toString();
        QString parentType = parentQuery.value("type").toString();
        QString parentId = parentQuery.value("parent_id").toString();

        // Create a parent item in the tree
        QTreeWidgetItem* parentItem = new QTreeWidgetItem(ui->ChartOfAccount);
        parentItem->setText(0, parentId);       // Account Code
        parentItem->setText(1, parentName);     // Account Name
        parentItem->setText(2, parentType);     // Account Type
        parentItem->setText(3, "");             // No Balance for Parent


        // Query child accounts associated with this parent
        QSqlQuery childQuery;
        childQuery.prepare("SELECT account_id, account_name, balance, type FROM ChartOfAccounts WHERE parent_header = :parent_header");
        childQuery.bindValue(":parent_header", parentName);

        if (!childQuery.exec()) {
            qDebug() << "Error fetching child accounts: " << childQuery.lastError().text();
            return;
        }

        // Loop through the child accounts and add them under the parent item
        while (childQuery.next()) {
            QString accountId = childQuery.value("account_id").toString();
            QString accountName = childQuery.value("account_name").toString();
            QString balance = QString::number(childQuery.value("balance").toDouble(), 'f', 2);  // Fixed precision
            QString accountType = childQuery.value("type").toString();

            // Create a child item under the parent
            QTreeWidgetItem* childItem = new QTreeWidgetItem(parentItem);
            childItem->setText(0, accountId);      // Account Code in the first column
            childItem->setText(1, accountName);    // Account Name in the second column
            childItem->setText(2, accountType);    // Type in the third column
            childItem->setText(3, balance);        // Balance in the fourth column
        }

        // Expand the parent item to show children
        ui->ChartOfAccount->addTopLevelItem(parentItem);
        parentItem->setExpanded(true);  // Automatically expand to show children

        // Set a different style for parent rows
        for (int i = 0; i < 4; ++i) {
            parentItem->setBackground(i, QBrush(QColor(200, 200, 200)));  // Light grey background for parent
            parentItem->setFont(i, QFont("Arial", 10, QFont::Bold));      // Bold font for parent
        }
    }

    // Style the header



}

ChartOfAccountWindow::~ChartOfAccountWindow()
{


    delete ui;

}

void ChartOfAccountWindow::OpenMainWindow(){
    MainWindow *MainWin=new MainWindow();
    QSize currentSize = this->size();
    QPoint currentPosition = this->pos();
    MainWin->resize(currentSize);
    MainWin->move(currentPosition);
    MainWin->show();
    this->close();
    delete this;
}

void ChartOfAccountWindow::OpenAddAccountWindow(){
    AddWindow* AddWin=new AddWindow();
    QSize currentSize = this->size();
    QPoint currentPosition = this->pos();
    AddWin->resize(currentSize);
    AddWin->move(currentPosition);
    AddWin->show();
    this->close();
    delete this;
}

void ChartOfAccountWindow::on_pushButton_clicked()
{
    OpenMainWindow();
}


void ChartOfAccountWindow::on_CreateAccount_clicked()
{
    ChartOfAccountWindow::OpenAddAccountWindow();

}


void ChartOfAccountWindow::on_ChartOfAccount_itemDoubleClicked(QTreeWidgetItem *item, int column)
{
        db=MainWindow::ConnectDatabase();
        ui->DeleteAccountFrame->setVisible(true);
        ChartOfAccountWindow::selectedAccountId = item->text(0).toInt();
        QString accountName = item->text(1); // Assuming the second column has the account name

        // Check if the account is a parent
        QSqlQuery query;
        query.prepare("SELECT COUNT(*) FROM ParentAccounts WHERE parent_id = :id");
        query.bindValue(":id", ChartOfAccountWindow::selectedAccountId);
        query.exec();

        if (query.next() && query.value(0).toInt() > 0) {
            isParentAccount = true; // You can add this boolean flag as a member variable of ChartOfAccountWindow
        } else {
            isParentAccount = false;
        }

        ui->DeleteLabel->setText("SELECT ACTION FOR: " + accountName + "?");
        db.close();
}


void ChartOfAccountWindow::on_Cancel_clicked()
{
    ui->DeleteAccountFrame->setVisible(false);
}


void ChartOfAccountWindow::on_Delete_clicked()
{
    db=MainWindow::ConnectDatabase();
    if (ChartOfAccountWindow::selectedAccountId <= 0) {
            qDebug() << "No account selected for deletion!";
            return;
        }

        // Prepare the SQL query to delete the account
        QSqlQuery deleteQuery;
        if(isParentAccount){
            deleteQuery.prepare("DELETE FROM ParentAccounts WHERE parent_id= :account_id");
        }
        else{
            deleteQuery.prepare("DELETE FROM ChartOfAccounts WHERE account_id = :account_id");
        }

        deleteQuery.bindValue(":account_id", ChartOfAccountWindow::selectedAccountId);

        if (!deleteQuery.exec()) {
            qDebug() << "Error deleting account: " << deleteQuery.lastError().text();
            return;
        }

        qDebug() << "Account deleted successfully!";

        // Hide the prompt frame after deletion
        ui->DeleteAccountFrame->setVisible(false);

        // Clear the selected account ID
        ChartOfAccountWindow::selectedAccountId=-1;

        // Refresh the QTreeWidget to reflect the deletion
        this->displayData();
        db.close();
}


void ChartOfAccountWindow::on_EditAccount_clicked()
{
    EditWindow * EditWin=new EditWindow();
    db=MainWindow::ConnectDatabase();

    //EditWin->setStyleSheet("background-color:black; color: white;");

    if(isParentAccount){
        EditWin->ShowParentAccountDetail(ChartOfAccountWindow::selectedAccountId);
    }
    else{
        EditWin->ShowChildAccountDetail(ChartOfAccountWindow::selectedAccountId);
    }

    QSize currentSize = this->size();
    QPoint currentPosition = this->pos();
    EditWin->resize(currentSize);
    EditWin->move(currentPosition);
    EditWin->show();
    this->close();
    delete this;
    db.close();

}

