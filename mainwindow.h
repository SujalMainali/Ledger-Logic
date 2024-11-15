#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QVector>
#include <QtCharts>
#include<QtSql>
#include "chartofaccountwindow.h"


QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    static QSqlDatabase db;
    void RetrieveDataForSalesGraph(QLineSeries *series);
    void RetrieveDataForPurchaseGraph(QLineSeries *series);

    static void ConnectDatabase();

    void OpenChartOfAccountsWindow();



private slots:
    void on_Accounting_clicked();


    void on_Sales_clicked();

    void on_CreateInvoice_clicked();

    void on_RecordPayment_clicked();

    void on_Purchase_clicked();

    void on_CreateBill_clicked();

    void on_RecordBillPayment_clicked();

    void on_NavButton_clicked();

    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_Reporting_clicked();

    void on_TrialBalance_clicked();

    void on_PLReport_clicked();

    void on_BalanceSheet_clicked();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
