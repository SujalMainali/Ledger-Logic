#ifndef BALANCESHEET_H
#define BALANCESHEET_H

#include <QMainWindow>
#include <QStandardItemModel>

QT_BEGIN_NAMESPACE
namespace Ui { class BalanceSheet; }
QT_END_NAMESPACE

class BalanceSheet : public QMainWindow
{
    Q_OBJECT

public:
    BalanceSheet(QWidget *parent = nullptr);
    QStandardItemModel *model;
    void fetchBalanceSheetData();
    ~BalanceSheet();

private slots:
    void on_LogoButton_clicked();

private:
    Ui::BalanceSheet *ui;
};
#endif // BALANCESHEET_H
