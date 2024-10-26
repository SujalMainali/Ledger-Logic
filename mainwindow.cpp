#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QtCharts>
#include<QtSql>
#include<QDebug>
#include<QVector>
#include<QPointF>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlError>
#include "FunctionsDefinition.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QChart *SalesChart= new QChart(); //this creates an object of Qchart class
    QLineSeries *SalesSeries=new QLineSeries(this);//This creates an object series of Qlineseries class in Global
    QChart *PurchaseChart= new QChart();
    QLineSeries *PurchaseSeries=new QLineSeries(this);


    RetrieveDataForSalesGraph(SalesSeries);


    SalesSeries->setName("August");//This gives a name to the series





    SalesChart->addSeries(SalesSeries); //this provides the series to the chart for the formation of graph
    SalesChart->legend()->show();
    SalesChart->legend()->setAlignment(Qt::AlignBottom); //the legend refers to the name of series which is now alligned at bottom
    SalesChart->legend()->setMarkerShape(QLegend::MarkerShapeStar);//This provides the symbol which is used to mark the legend
    SalesChart->setBackgroundBrush(QBrush(QColor(191, 226, 228)));



    /*chart->createDefaultAxes()*/;//this gives the x and y axis to the graph

    QValueAxis *axisX= new QValueAxis(this);//This creates an object of QCategoryAxis class used for manipulation of xAxis


    //axisX->setLabelsPosition(QCategoryAxis::AxisLabelsPositionOnValue);//Alligns the lebel in specified manner
    axisX->setRange(0,20);

    //These two codes adds the axis to graph
    SalesChart->addAxis(axisX,Qt::AlignBottom);

    SalesSeries->attachAxis(axisX); //This is important so as to show accurate data

    QValueAxis *axisY = new QValueAxis(this) ;//This is used for manipulation of Y-axis

    axisY->setRange(0,1000);

    SalesChart->setTitle("Sales Data From Last Month");

    SalesChart->addAxis(axisY,Qt::AlignLeft);
    SalesSeries->attachAxis(axisY);



    QChartView *SalesChartview = new QChartView(SalesChart);
    SalesChartview->setRenderHint(QPainter::Antialiasing);
    //this is to view the series which is converted to chart


    RetrieveDataForPurchaseGraph(PurchaseSeries);

    PurchaseSeries->setName("August");

    PurchaseChart->addSeries(PurchaseSeries);
    PurchaseChart->legend()->show();
    PurchaseChart->legend()->setAlignment(Qt::AlignBottom);
    PurchaseChart->legend()->setMarkerShape(QLegend::MarkerShapeStar);
    PurchaseChart->setBackgroundBrush(QBrush(QColor(191, 226, 228)));

    QValueAxis *axisX1= new QValueAxis(this);
    QValueAxis *axisY1 = new QValueAxis(this) ;
    axisX1->setRange(0,20);
    axisY1->setRange(0,1000);




    PurchaseChart->addAxis(axisX1, Qt::AlignBottom);
    PurchaseSeries->attachAxis(axisX1);


    PurchaseChart->setTitle("Purchase Data From Last Month");
    PurchaseChart->addAxis(axisY1, Qt::AlignLeft);
    PurchaseSeries->attachAxis(axisY1);

    QChartView *PurchaseChartView = new QChartView(PurchaseChart);
    PurchaseChartView->setRenderHint(QPainter::Antialiasing);

    ui->FirstGraph->addWidget(SalesChartview);

    ui->SecondGraph->addWidget(PurchaseChartView);

    ui->Navbar->setVisible(false);

    ui->Border->setVisible(false);
    ui->SalesOptions->setVisible(false);
    ui->BillOptions->setVisible(false);



//    delete chart;
//    delete chart1;
//    delete series;
//    delete series1;
//    delete axisX;
//    delete axisY;



}


MainWindow::~MainWindow()
{
    delete ui;

}









