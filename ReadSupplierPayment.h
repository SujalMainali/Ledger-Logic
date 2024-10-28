#ifndef READSUPPLIERPAYMENT_H
#define READSUPPLIERPAYMENT_H

#include <QMainWindow>
#include <QComboBox>

QT_BEGIN_NAMESPACE
namespace Ui {
class ReadSupplierPayment;
}
QT_END_NAMESPACE

class ReadSupplierPayment : public QMainWindow
{
    Q_OBJECT

public:
    ReadSupplierPayment(QWidget *parent = nullptr);
    ~ReadSupplierPayment();
    void loadDueBills();

private slots:
    void on_BillsTable_cellDoubleClicked(int row, int column);


    void on_Save_clicked();

    void on_pushButton_clicked();

    void on_Cancel_clicked();

private:
    Ui::ReadSupplierPayment *ui;
};
#endif // READSUPPLIERPAYMENT_H
