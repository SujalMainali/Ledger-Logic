#ifndef READSUPPLIERPAYMENT_H
#define READSUPPLIERPAYMENT_H

#include <QMainWindow>

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

private:
    Ui::ReadSupplierPayment *ui;
};
#endif // READSUPPLIERPAYMENT_H
