#ifndef TRIALBALANCE_H
#define TRIALBALANCE_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class TrialBalance; }
QT_END_NAMESPACE

class TrialBalance : public QMainWindow
{
    Q_OBJECT

public:
    TrialBalance(QWidget *parent = nullptr);
    void PopulateTable();
    void AddTotalRow();
    ~TrialBalance();

private slots:
    void on_LogoButton_clicked();

private:
    Ui::TrialBalance *ui;
};
#endif // TRIALBALANCE_H
