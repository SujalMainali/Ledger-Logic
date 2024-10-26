#include "ReadSupplierPayment.h"
#include "ui_ReadSupplierPayment.h"

ReadSupplierPayment::ReadSupplierPayment(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::ReadSupplierPayment)
{
    ui->setupUi(this);
}

ReadSupplierPayment::~ReadSupplierPayment()
{
    delete ui;
}
