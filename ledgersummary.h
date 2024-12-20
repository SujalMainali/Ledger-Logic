#ifndef LEDGERSUMMARY_H
#define LEDGERSUMMARY_H

#include <QMainWindow>
#include <QTableWidgetItem>

QT_BEGIN_NAMESPACE
namespace Ui {
class LedgerSummary;
}
QT_END_NAMESPACE

class LedgerSummary : public QMainWindow
{
    Q_OBJECT

public:
    LedgerSummary(QWidget *parent = nullptr);
    void loadLedgerData(QDate startDate, QDate endDate) ;
    static int AccountId;
    static QString AccountName;
    ~LedgerSummary();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_3_clicked();

    void on_LedgerTable_itemDoubleClicked(QTableWidgetItem *item);

private:
    Ui::LedgerSummary *ui;

};
#endif // LEDGERSUMMARY_H
