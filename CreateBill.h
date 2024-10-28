#ifndef CREATEBILL_H
#define CREATEBILL_H

#include <QMainWindow>
#include <QComboBox>

QT_BEGIN_NAMESPACE
namespace Ui {
class CreateBill;
}
QT_END_NAMESPACE

class CreateBill : public QMainWindow
{
    Q_OBJECT

public:
    CreateBill(QWidget *parent = nullptr);
    void saveBillTransactionItems();
    void saveBillTransaction();
    ~CreateBill();

private slots:
    void on_ItemsTable_cellChanged(int row, int column);

    void on_Cancel_clicked();

    void on_Save_clicked();

private:
    Ui::CreateBill *ui;
};
#endif // CREATEBILL_H
