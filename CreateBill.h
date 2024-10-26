#ifndef CREATEBILL_H
#define CREATEBILL_H

#include <QMainWindow>

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
    ~CreateBill();

private:
    Ui::CreateBill *ui;
};
#endif // CREATEBILL_H
