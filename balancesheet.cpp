#include "balancesheet.h"
#include "./ui_balancesheet.h"
#include "mainwindow.h"
#include <QtSql>

BalanceSheet::BalanceSheet(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::BalanceSheet)
{
    ui->setupUi(this);
    ui->Title->setText("BALANCE SHEET At "+ ui->ReadDate->date().toString("yyyy-MM-dd"));
    model= new QStandardItemModel();
    model = new QStandardItemModel(this);
    model->setHorizontalHeaderLabels({"Account", "Amount"});
    ui->BalanceSheetTable->setModel(model);
    ui->BalanceSheetTable->expandAll();
    fetchBalanceSheetData();

}

void BalanceSheet::fetchBalanceSheetData()
{
    QSqlDatabase db = MainWindow::db;
    if (!db.isOpen()) {
        qWarning() << "Database is not open!";
        return;
    }

    // Add top-level items
    QStandardItem *assetsItem = new QStandardItem("Assets");
    QStandardItem *liabilitiesItem = new QStandardItem("Liabilities");
    QStandardItem *equityItem = new QStandardItem("Equity");

    model->appendRow(assetsItem);
    model->appendRow(liabilitiesItem);
    model->appendRow(equityItem);

    QFont boldFont;
    boldFont.setBold(true); // Define a bold font

    // Query and populate Assets
    QSqlQuery assetsQuery("SELECT coa.account_name, ab.current_balance "
                          "FROM ChartOfAccounts coa "
                          "JOIN AccountBalances ab ON coa.account_id = ab.account_id "
                          "WHERE coa.type = 'ASSETS'");
    double totalAssets = 0.0;
    while (assetsQuery.next()) {
        QString accountName = assetsQuery.value(0).toString();
        double balance = qAbs(assetsQuery.value(1).toDouble()); // Always positive

        assetsItem->appendRow({new QStandardItem(accountName), new QStandardItem(QString::number(balance, 'f', 2))});
        totalAssets += balance;
    }

    // Add Total Assets row and set font
    QStandardItem *totalAssetsLabel = new QStandardItem("Total Assets");
    totalAssetsLabel->setFont(boldFont);
    QStandardItem *totalAssetsValue = new QStandardItem(QString::number(totalAssets, 'f', 2));
    totalAssetsValue->setFont(boldFont);
    assetsItem->appendRow({totalAssetsLabel, totalAssetsValue});

    // Query and populate Liabilities
    QSqlQuery liabilitiesQuery("SELECT coa.account_name, ab.current_balance "
                               "FROM ChartOfAccounts coa "
                               "JOIN AccountBalances ab ON coa.account_id = ab.account_id "
                               "WHERE coa.type = 'LIABILITIES'");
    double totalLiabilities = 0.0;
    while (liabilitiesQuery.next()) {
        QString accountName = liabilitiesQuery.value(0).toString();
        double balance = qAbs(liabilitiesQuery.value(1).toDouble()); // Always positive

        liabilitiesItem->appendRow({new QStandardItem(accountName), new QStandardItem(QString::number(balance, 'f', 2))});
        totalLiabilities += balance;
    }

    // Add Total Liabilities row and set font
    QStandardItem *totalLiabilitiesLabel = new QStandardItem("Total Liabilities");
    totalLiabilitiesLabel->setFont(boldFont);
    QStandardItem *totalLiabilitiesValue = new QStandardItem(QString::number(totalLiabilities, 'f', 2));
    totalLiabilitiesValue->setFont(boldFont);
    liabilitiesItem->appendRow({totalLiabilitiesLabel, totalLiabilitiesValue});

    // Query and populate Equity
    QSqlQuery equityQuery("SELECT coa.account_name, ab.current_balance "
                          "FROM ChartOfAccounts coa "
                          "JOIN AccountBalances ab ON coa.account_id = ab.account_id "
                          "WHERE coa.type = 'EQUITY'");
    double totalEquity = 0.0;
    while (equityQuery.next()) {
        QString accountName = equityQuery.value(0).toString();
        double balance = qAbs(equityQuery.value(1).toDouble()); // Always positive

        equityItem->appendRow({new QStandardItem(accountName), new QStandardItem(QString::number(balance, 'f', 2))});
        totalEquity += balance;
    }

    // Add Total Equity row and set font
    QStandardItem *totalEquityLabel = new QStandardItem("Total Equity");
    totalEquityLabel->setFont(boldFont);
    QStandardItem *totalEquityValue = new QStandardItem(QString::number(totalEquity, 'f', 2));
    totalEquityValue->setFont(boldFont);
    equityItem->appendRow({totalEquityLabel, totalEquityValue});

    // Calculate Net Worth
    double netWorth = totalAssets - totalLiabilities;

    // Validate that Net Worth matches Total Equity
    QString validationMessage;
    if (qFuzzyCompare(netWorth + 1, totalEquity + 1)) {
        validationMessage = QString("Net Worth and Equity are balanced: %1").arg(netWorth, 0, 'f', 2);
    } else {
        validationMessage = QString("Mismatch: Net Worth = %1, Equity = %2")
                                .arg(netWorth, 0, 'f', 2)
                                .arg(totalEquity, 0, 'f', 2);
    }

    QStandardItem *netWorthItem = new QStandardItem("Net Worth");
    netWorthItem->appendRow({new QStandardItem(validationMessage), new QStandardItem(QString::number(netWorth, 'f', 2))});

    model->appendRow(netWorthItem);

    // Expand all rows by default
    ui->BalanceSheetTable->expandAll();
}

BalanceSheet::~BalanceSheet()
{
    delete ui;
}


void BalanceSheet::on_LogoButton_clicked()
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

