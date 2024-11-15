#ifndef PLACCOUNT_H
#define PLACCOUNT_H

#include <QMainWindow>
#include <QStandardItemModel>

QT_BEGIN_NAMESPACE
namespace Ui { class PLAccount; }
QT_END_NAMESPACE

class PLAccount : public QMainWindow
{
    Q_OBJECT

public:
    PLAccount(QWidget *parent = nullptr);
    void fetchProfitAndLossData();
    QStandardItemModel *model;
    ~PLAccount();

private slots:
    void on_LogoButton_clicked();

private:
    Ui::PLAccount *ui;
};
#endif // PLACCOUNT_H
