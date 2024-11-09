#ifndef LEDGERSUMMARY_H
#define LEDGERSUMMARY_H

#include <QMainWindow>

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
    ~LedgerSummary();

private:
    Ui::LedgerSummary *ui;
};
#endif // LEDGERSUMMARY_H
