#include "ledgersummary.h"
#include "./ui_ledgersummary.h"

LedgerSummary::LedgerSummary(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::LedgerSummary)
{
    ui->setupUi(this);
}

LedgerSummary::~LedgerSummary()
{
    delete ui;
}
