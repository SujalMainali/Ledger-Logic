#ifndef CREATEJOURNAL_H
#define CREATEJOURNAL_H

#include <QMainWindow>
#include <QSqlDatabase>

QT_BEGIN_NAMESPACE
namespace Ui {
class CreateJournal;
}
QT_END_NAMESPACE

class CreateJournal : public QMainWindow
{
    Q_OBJECT

public:
    CreateJournal(QWidget *parent = nullptr);
    static void UpdateAccountBalances(int accountId, double amount, bool isDebit, QSqlDatabase &db);
    ~CreateJournal();

private slots:
    void on_Save_clicked();

    void on_Cancel_clicked();

    void on_AddRow_clicked();

private:
    Ui::CreateJournal *ui;
};
#endif // MAINWINDOW_H
