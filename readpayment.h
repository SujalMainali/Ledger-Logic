#ifndef READPAYMENT_H
#define READPAYMENT_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui {
class ReadPayment;
}
QT_END_NAMESPACE

class ReadPayment : public QMainWindow
{
    Q_OBJECT

public:
    ReadPayment(QWidget *parent = nullptr);
    ~ReadPayment();

private slots:
    void on_pushButton_clicked();

private:
    Ui::ReadPayment *ui;
};
#endif // READPAYMENT_H
