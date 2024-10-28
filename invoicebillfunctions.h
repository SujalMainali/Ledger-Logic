#ifndef INVOICEBILLFUNCTIONS_H
#define INVOICEBILLFUNCTIONS_H
#include <QtWidgets>
#include <QSqlQuery>


class InvoiceBillFunctions
{
public:
    InvoiceBillFunctions();
    static void loadDueBills(QTableWidget *Table, QSqlQuery &query, QSqlDatabase &db);
    static void setComboBoxInCell(QTableWidget *Table, int row, int column, QSqlDatabase &db);
    static void populateComboBoxWithAccounts(QComboBox *comboBox,QSqlDatabase &db);
    static void saveAdditionalPaymentsToDatabase(QTableWidget *billsTable, QSqlQuery &query,QSqlQuery &LoadQuery,QSqlDatabase &db);
    static void TableDataEntry(QTableWidget* Table,int row, int column, QLineEdit* Total);
    static void updateAmountInTable(QTableWidget *Table, int row);
    static void showTotalAmount(QTableWidget *Table,QLineEdit *Total);
    static void saveTransaction(QTableWidget* Table, QSqlQuery& query, QSqlQuery& updateQuery,QLineEdit* BillNumber);
    static void saveTransactionItems(QTableWidget* Table,QSqlQuery& query,QLineEdit* BillNumber);
};


#endif // INVOICEBILLFUNCTIONS_H
