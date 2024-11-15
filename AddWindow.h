#ifndef ADDWINDOW_H
#define ADDWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui {
class AddWindow;
}
QT_END_NAMESPACE

class AddWindow : public QMainWindow
{
    Q_OBJECT

public:
    AddWindow(QWidget *parent = nullptr);
    ~AddWindow();
    void AddChildToDatabase();
    void AddParentToDatabase();
    void AddAccountToBalanceTable(int accountId, double openingBalance);
    void PopulateSelectHeader();
    int16_t GetTypeIdFromType(QString type);

private slots:
    void on_Save_clicked();

    void on_Cancel_clicked();

    void on_ChildCheckbox_stateChanged(int arg1);

    void on_ParentCheckbox_stateChanged(int arg1);

private:
    Ui::AddWindow *ui;
};
#endif // MAINWINDOW1_H
