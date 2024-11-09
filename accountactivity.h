#ifndef ACCOUNTACTIVITY_H
#define ACCOUNTACTIVITY_H

#include <QMainWindow>
#include <QSqlDatabase>

QT_BEGIN_NAMESPACE
namespace Ui {
class ActivitySummary;
}
QT_END_NAMESPACE

class ActivitySummary : public QMainWindow
{
    Q_OBJECT

public:
    ActivitySummary(QWidget *parent = nullptr);
    double fetchOpeningBalance(int accountId,QSqlDatabase &db);
    void loadLedgerData(int accountId);
    ~ActivitySummary();

private slots:

    void on_MainWindow_clicked();

    void on_pushButton_clicked();

private:
    Ui::ActivitySummary *ui;
};
#endif // ACCOUNTACTIVITY_H
