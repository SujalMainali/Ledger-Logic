#include "CreateBill.h"
#include "./ui_CreateBill.h"

CreateBill::CreateBill(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::CreateBill)
{
    ui->setupUi(this);
}

CreateBill::~CreateBill()
{
    delete ui;
}
