#include "readpayment.h"
#include "./ui_readpayment.h"
#include "mainwindow.h"


ReadPayment::ReadPayment(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::ReadPayment)
{
    ui->setupUi(this);
}

ReadPayment::~ReadPayment()
{
    delete ui;
}

void ReadPayment::on_pushButton_clicked()
{
    MainWindow *MainWin=new MainWindow();
    QSize currentSize = this->size();
    QPoint currentPosition = this->pos();
    MainWin->resize(currentSize);
    MainWin->move(currentPosition);
    MainWin->show();
    this->close();
}

