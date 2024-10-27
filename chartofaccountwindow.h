#ifndef CHARTOFACCOUNTWINDOW_H
#define CHARTOFACCOUNTWINDOW_H

#include <QMainWindow>
#include<QtSql>
#include "AddWindow.h"
#include <QTreeWidgetItem>


QT_BEGIN_NAMESPACE
namespace Ui {
class ChartOfAccountWindow;
}
QT_END_NAMESPACE

class ChartOfAccountWindow : public QMainWindow
{
    Q_OBJECT

public:
    ChartOfAccountWindow(QWidget *parent = nullptr);
    ~ChartOfAccountWindow();
    void displayData();
    void OpenMainWindow();
    void OpenAddAccountWindow();

    QSqlDatabase db;
    static int16_t selectedAccountId;
    bool isParentAccount;
    static int getAccountIdFromAccountName(const QString &accountName);

private slots:
    void on_pushButton_clicked();

    void on_CreateAccount_clicked();

    void on_ChartOfAccount_itemDoubleClicked(QTreeWidgetItem *item, int column);

    void on_Cancel_clicked();

    void on_Delete_clicked();

    void on_EditAccount_clicked();


private:
    Ui::ChartOfAccountWindow *ui;
};
#endif // CHARTOFACCOUNTWINDOW_H
