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
    void saveTransactionItems();
    void saveSalesTransaction();
    void createJournalEntryForInvoice();
//    static bool reload;


    void on_CancelButton_clicked();

    void on_SaveButton_clicked();

    void on_pushButton_clicked();

private:
    Ui::CreateInvoice *ui;
};
#endif // CREATE1_H
