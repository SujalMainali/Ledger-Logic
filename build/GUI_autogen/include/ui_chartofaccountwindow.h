/********************************************************************************
** Form generated from reading UI file 'chartofaccountwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.4.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CHARTOFACCOUNTWINDOW_H
#define UI_CHARTOFACCOUNTWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStackedWidget>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ChartOfAccountWindow
{
public:
    QWidget *centralwidget;
    QHBoxLayout *horizontalLayout_2;
    QFrame *Container;
    QVBoxLayout *verticalLayout;
    QStackedWidget *UpperLogoBar;
    QWidget *LogoStack;
    QTextEdit *Motto;
    QPushButton *pushButton;
    QFrame *AccountWindow;
    QGridLayout *gridLayout;
    QLineEdit *BasicInfo;
    QFrame *Buttons;
    QHBoxLayout *horizontalLayout;
    QPushButton *EditAccount;
    QPushButton *CreateAccount;
    QTableWidget *ChartOfAccount;

    void setupUi(QMainWindow *ChartOfAccountWindow)
    {
        if (ChartOfAccountWindow->objectName().isEmpty())
            ChartOfAccountWindow->setObjectName("ChartOfAccountWindow");
        ChartOfAccountWindow->resize(1262, 754);
        QFont font;
        font.setFamilies({QString::fromUtf8("Arial Narrow")});
        font.setPointSize(15);
        ChartOfAccountWindow->setFont(font);
        ChartOfAccountWindow->setStyleSheet(QString::fromUtf8("\n"
"\n"
"background-color:black;\n"
"color:white;\n"
""));
        centralwidget = new QWidget(ChartOfAccountWindow);
        centralwidget->setObjectName("centralwidget");
        horizontalLayout_2 = new QHBoxLayout(centralwidget);
        horizontalLayout_2->setSpacing(0);
        horizontalLayout_2->setObjectName("horizontalLayout_2");
        horizontalLayout_2->setContentsMargins(0, 0, 0, 0);
        Container = new QFrame(centralwidget);
        Container->setObjectName("Container");
        Container->setMinimumSize(QSize(0, 500));
        Container->setStyleSheet(QString::fromUtf8(""));
        Container->setFrameShape(QFrame::StyledPanel);
        Container->setFrameShadow(QFrame::Raised);
        verticalLayout = new QVBoxLayout(Container);
        verticalLayout->setSpacing(0);
        verticalLayout->setObjectName("verticalLayout");
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        UpperLogoBar = new QStackedWidget(Container);
        UpperLogoBar->setObjectName("UpperLogoBar");
        UpperLogoBar->setMinimumSize(QSize(0, 100));
        UpperLogoBar->setMaximumSize(QSize(16777215, 100));
        UpperLogoBar->setStyleSheet(QString::fromUtf8("background-color:black;"));
        UpperLogoBar->setFrameShape(QFrame::StyledPanel);
        UpperLogoBar->setFrameShadow(QFrame::Raised);
        LogoStack = new QWidget();
        LogoStack->setObjectName("LogoStack");
        LogoStack->setMinimumSize(QSize(0, 100));
        LogoStack->setMaximumSize(QSize(16777215, 100));
        Motto = new QTextEdit(LogoStack);
        Motto->setObjectName("Motto");
        Motto->setGeometry(QRect(250, 20, 914, 80));
        Motto->viewport()->setProperty("cursor", QVariant(QCursor(Qt::IBeamCursor)));
        Motto->setStyleSheet(QString::fromUtf8("margin-bottom:3px;\n"
"color:white;"));
        Motto->setReadOnly(true);
        pushButton = new QPushButton(LogoStack);
        pushButton->setObjectName("pushButton");
        pushButton->setGeometry(QRect(0, 10, 300, 100));
        pushButton->setMinimumSize(QSize(300, 100));
        pushButton->setCursor(QCursor(Qt::PointingHandCursor));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/images/AppLogo.png"), QSize(), QIcon::Active, QIcon::On);
        pushButton->setIcon(icon);
        pushButton->setIconSize(QSize(300, 100));
        UpperLogoBar->addWidget(LogoStack);
        pushButton->raise();
        Motto->raise();

        verticalLayout->addWidget(UpperLogoBar);

        AccountWindow = new QFrame(Container);
        AccountWindow->setObjectName("AccountWindow");
        AccountWindow->setStyleSheet(QString::fromUtf8("QTableWidget {\n"
"    background-color: #2e2e2e; /* Dark background for the table */\n"
"    gridline-color: #444444; /* Darker grid lines */\n"
"    selection-background-color: #4caf50; /* Green for selected rows */\n"
"    selection-color: white; /* White text on selection */\n"
"    color: #e0e0e0; /* Light gray text for table content */\n"
"    border: 1px solid #555555; /* Dark gray border */\n"
"}\n"
"\n"
"QHeaderView::section {\n"
"    background-color: #3b3b3b; /* Darker gray for header */\n"
"    padding: 4px;\n"
"    font-weight: bold;\n"
"    color: #ffffff; /* White header text */\n"
"    border: 1px solid #555555; /* Dark gray border for header */\n"
"}\n"
"\n"
"QTableWidget::item::selected {\n"
"	background-color:white;\n"
"}"));
        AccountWindow->setFrameShape(QFrame::StyledPanel);
        AccountWindow->setFrameShadow(QFrame::Raised);
        gridLayout = new QGridLayout(AccountWindow);
        gridLayout->setObjectName("gridLayout");
        BasicInfo = new QLineEdit(AccountWindow);
        BasicInfo->setObjectName("BasicInfo");
        BasicInfo->setMinimumSize(QSize(0, 40));
        BasicInfo->setMaximumSize(QSize(300, 16777215));
        BasicInfo->setFont(font);
        BasicInfo->setReadOnly(true);

        gridLayout->addWidget(BasicInfo, 1, 0, 1, 1);

        Buttons = new QFrame(AccountWindow);
        Buttons->setObjectName("Buttons");
        Buttons->setMinimumSize(QSize(0, 80));
        Buttons->setStyleSheet(QString::fromUtf8("QPushButton{\n"
"	background-color:white;\n"
"	color:black;\n"
"	border-radius:15px;\n"
"	cursor:pointer;\n"
"}"));
        Buttons->setFrameShape(QFrame::StyledPanel);
        Buttons->setFrameShadow(QFrame::Raised);
        horizontalLayout = new QHBoxLayout(Buttons);
        horizontalLayout->setObjectName("horizontalLayout");
        EditAccount = new QPushButton(Buttons);
        EditAccount->setObjectName("EditAccount");
        EditAccount->setMinimumSize(QSize(100, 40));
        EditAccount->setCursor(QCursor(Qt::PointingHandCursor));

        horizontalLayout->addWidget(EditAccount);

        CreateAccount = new QPushButton(Buttons);
        CreateAccount->setObjectName("CreateAccount");
        CreateAccount->setMinimumSize(QSize(100, 40));
        CreateAccount->setCursor(QCursor(Qt::PointingHandCursor));

        horizontalLayout->addWidget(CreateAccount);


        gridLayout->addWidget(Buttons, 0, 0, 1, 1, Qt::AlignRight);

        ChartOfAccount = new QTableWidget(AccountWindow);
        if (ChartOfAccount->columnCount() < 4)
            ChartOfAccount->setColumnCount(4);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        ChartOfAccount->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        ChartOfAccount->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        QTableWidgetItem *__qtablewidgetitem2 = new QTableWidgetItem();
        ChartOfAccount->setHorizontalHeaderItem(2, __qtablewidgetitem2);
        QTableWidgetItem *__qtablewidgetitem3 = new QTableWidgetItem();
        ChartOfAccount->setHorizontalHeaderItem(3, __qtablewidgetitem3);
        ChartOfAccount->setObjectName("ChartOfAccount");
        ChartOfAccount->setMinimumSize(QSize(0, 0));
        ChartOfAccount->setFont(font);
        ChartOfAccount->setMouseTracking(false);
        ChartOfAccount->setAutoFillBackground(true);
        ChartOfAccount->setLineWidth(5);
        ChartOfAccount->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        ChartOfAccount->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        ChartOfAccount->setSizeAdjustPolicy(QAbstractScrollArea::AdjustToContents);
        ChartOfAccount->setEditTriggers(QAbstractItemView::NoEditTriggers);
        ChartOfAccount->setAlternatingRowColors(false);
        ChartOfAccount->setSelectionMode(QAbstractItemView::NoSelection);
        ChartOfAccount->setShowGrid(true);
        ChartOfAccount->setGridStyle(Qt::SolidLine);
        ChartOfAccount->setSortingEnabled(false);
        ChartOfAccount->setColumnCount(4);
        ChartOfAccount->horizontalHeader()->setCascadingSectionResizes(false);
        ChartOfAccount->horizontalHeader()->setDefaultSectionSize(250);
        ChartOfAccount->horizontalHeader()->setProperty("showSortIndicator", QVariant(false));
        ChartOfAccount->horizontalHeader()->setStretchLastSection(true);
        ChartOfAccount->verticalHeader()->setVisible(false);
        ChartOfAccount->verticalHeader()->setCascadingSectionResizes(false);

        gridLayout->addWidget(ChartOfAccount, 2, 0, 1, 1);


        verticalLayout->addWidget(AccountWindow);


        horizontalLayout_2->addWidget(Container);

        ChartOfAccountWindow->setCentralWidget(centralwidget);

        retranslateUi(ChartOfAccountWindow);

        QMetaObject::connectSlotsByName(ChartOfAccountWindow);
    } // setupUi

    void retranslateUi(QMainWindow *ChartOfAccountWindow)
    {
        ChartOfAccountWindow->setWindowTitle(QCoreApplication::translate("ChartOfAccountWindow", "ChartOfAccountWindow", nullptr));
        Motto->setHtml(QCoreApplication::translate("ChartOfAccountWindow", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><meta charset=\"utf-8\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"hr { height: 1px; border-width: 0; }\n"
"li.unchecked::marker { content: \"\\2610\"; }\n"
"li.checked::marker { content: \"\\2612\"; }\n"
"</style></head><body style=\" font-family:'Sans Serif'; font-size:9pt; font-weight:400; font-style:normal;\">\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><br /></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:14pt;\">ACCOUNTING MADE EASY</span></p></body></html>", nullptr));
        pushButton->setText(QCoreApplication::translate("ChartOfAccountWindow", "PushButton", nullptr));
        BasicInfo->setText(QCoreApplication::translate("ChartOfAccountWindow", "Here are your list of Accounts:", nullptr));
        EditAccount->setText(QCoreApplication::translate("ChartOfAccountWindow", "Edit Account", nullptr));
        CreateAccount->setText(QCoreApplication::translate("ChartOfAccountWindow", "Create Account", nullptr));
        QTableWidgetItem *___qtablewidgetitem = ChartOfAccount->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QCoreApplication::translate("ChartOfAccountWindow", "Code", nullptr));
        QTableWidgetItem *___qtablewidgetitem1 = ChartOfAccount->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QCoreApplication::translate("ChartOfAccountWindow", "Name", nullptr));
        QTableWidgetItem *___qtablewidgetitem2 = ChartOfAccount->horizontalHeaderItem(2);
        ___qtablewidgetitem2->setText(QCoreApplication::translate("ChartOfAccountWindow", "Type", nullptr));
        QTableWidgetItem *___qtablewidgetitem3 = ChartOfAccount->horizontalHeaderItem(3);
        ___qtablewidgetitem3->setText(QCoreApplication::translate("ChartOfAccountWindow", "Balance", nullptr));
    } // retranslateUi

};

namespace Ui {
    class ChartOfAccountWindow: public Ui_ChartOfAccountWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CHARTOFACCOUNTWINDOW_H
