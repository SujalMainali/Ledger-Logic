#ifndef CREATEINVOICE_H
#define CREATEINVOICE_H

#include <QMainWindow>
#include <QComboBox>

QT_BEGIN_NAMESPACE
namespace Ui {
class CreateInvoice;
}
QT_END_NAMESPACE

class CreateInvoice : public QMainWindow
{
    Q_OBJECT

public:
    CreateInvoice(QWidget *parent = nullptr);
    ~CreateInvoice();

private slots:
    void on_ItemsTable_cellChanged(int row, int column);

    void on_pushButton_clicked();
    void populateComboBoxWithAccounts(QComboBox *comboBox);
    void saveTransactionItems();
    void saveSalesTransaction();
    int getAccountIdFromAccountName(const QString &accountName);
    void setComboBoxInCell(int row, int column);
    void updateAmountInTable(int row);
    void showTotalAmount();
//    static bool reload;

private:
    Ui::CreateInvoice *ui;
};
#endif // CREATE1_H
