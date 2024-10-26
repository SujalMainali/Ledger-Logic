/********************************************************************************
** Form generated from reading UI file 'chartofaccountwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.7.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CHARTOFACCOUNTWINDOW_H
#define UI_CHARTOFACCOUNTWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QFrame>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStackedWidget>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QTreeWidget>
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
    QStackedWidget *AccountWindow;
    QWidget *AccountWindowStacked;
    QVBoxLayout *verticalLayout_2;
    QFrame *Buttons;
    QHBoxLayout *horizontalLayout;
    QPushButton *CreateAccount;
    QLineEdit *BasicInfo;
    QFrame *ChartOfAccountFrame;
    QVBoxLayout *verticalLayout_3;
    QFrame *DeleteAccountFrame;
    QVBoxLayout *verticalLayout_4;
    QLineEdit *DeleteLabel;
    QFrame *frame_2;
    QHBoxLayout *horizontalLayout_3;
    QPushButton *Cancel;
    QPushButton *EditAccount;
    QPushButton *Delete;
    QTreeWidget *ChartOfAccount;

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
"background-color:rbg 54,15,1;\n"
"color:black;\n"
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
        Container->setStyleSheet(QString::fromUtf8("QPushButton{\n"
"	border-radius:10px;\n"
"	background-color:grey;\n"
"	color:white;\n"
"}"));
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

        AccountWindow = new QStackedWidget(Container);
        AccountWindow->setObjectName("AccountWindow");
        AccountWindow->setFont(font);
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
        AccountWindowStacked = new QWidget();
        AccountWindowStacked->setObjectName("AccountWindowStacked");
        verticalLayout_2 = new QVBoxLayout(AccountWindowStacked);
        verticalLayout_2->setObjectName("verticalLayout_2");
        Buttons = new QFrame(AccountWindowStacked);
        Buttons->setObjectName("Buttons");
        Buttons->setMinimumSize(QSize(0, 80));
        Buttons->setStyleSheet(QString::fromUtf8(""));
        Buttons->setFrameShape(QFrame::StyledPanel);
        Buttons->setFrameShadow(QFrame::Raised);
        horizontalLayout = new QHBoxLayout(Buttons);
        horizontalLayout->setObjectName("horizontalLayout");
        CreateAccount = new QPushButton(Buttons);
        CreateAccount->setObjectName("CreateAccount");
        CreateAccount->setMinimumSize(QSize(100, 40));
        CreateAccount->setCursor(QCursor(Qt::PointingHandCursor));
        CreateAccount->setStyleSheet(QString::fromUtf8("padding: 5"));

        horizontalLayout->addWidget(CreateAccount);


        verticalLayout_2->addWidget(Buttons, 0, Qt::AlignRight);

        BasicInfo = new QLineEdit(AccountWindowStacked);
        BasicInfo->setObjectName("BasicInfo");
        BasicInfo->setMinimumSize(QSize(0, 40));
        BasicInfo->setMaximumSize(QSize(300, 16777215));
        BasicInfo->setFont(font);
        BasicInfo->setReadOnly(true);

        verticalLayout_2->addWidget(BasicInfo);

        ChartOfAccountFrame = new QFrame(AccountWindowStacked);
        ChartOfAccountFrame->setObjectName("ChartOfAccountFrame");
        ChartOfAccountFrame->setMinimumSize(QSize(100, 400));
        ChartOfAccountFrame->setFrameShape(QFrame::StyledPanel);
        ChartOfAccountFrame->setFrameShadow(QFrame::Raised);
        verticalLayout_3 = new QVBoxLayout(ChartOfAccountFrame);
        verticalLayout_3->setSpacing(0);
        verticalLayout_3->setObjectName("verticalLayout_3");
        verticalLayout_3->setContentsMargins(0, 0, 0, 0);
        DeleteAccountFrame = new QFrame(ChartOfAccountFrame);
        DeleteAccountFrame->setObjectName("DeleteAccountFrame");
        DeleteAccountFrame->setMinimumSize(QSize(0, 100));
        DeleteAccountFrame->setFrameShape(QFrame::StyledPanel);
        DeleteAccountFrame->setFrameShadow(QFrame::Raised);
        verticalLayout_4 = new QVBoxLayout(DeleteAccountFrame);
        verticalLayout_4->setObjectName("verticalLayout_4");
        DeleteLabel = new QLineEdit(DeleteAccountFrame);
        DeleteLabel->setObjectName("DeleteLabel");
        DeleteLabel->setMinimumSize(QSize(500, 0));
        DeleteLabel->setFont(font);
        DeleteLabel->setAlignment(Qt::AlignCenter);

        verticalLayout_4->addWidget(DeleteLabel);

        frame_2 = new QFrame(DeleteAccountFrame);
        frame_2->setObjectName("frame_2");
        frame_2->setStyleSheet(QString::fromUtf8(""));
        frame_2->setFrameShape(QFrame::StyledPanel);
        frame_2->setFrameShadow(QFrame::Raised);
        horizontalLayout_3 = new QHBoxLayout(frame_2);
        horizontalLayout_3->setObjectName("horizontalLayout_3");
        Cancel = new QPushButton(frame_2);
        Cancel->setObjectName("Cancel");
        Cancel->setMinimumSize(QSize(80, 40));
        Cancel->setMaximumSize(QSize(80, 16777215));

        horizontalLayout_3->addWidget(Cancel);

        EditAccount = new QPushButton(frame_2);
        EditAccount->setObjectName("EditAccount");
        EditAccount->setMinimumSize(QSize(100, 40));
        EditAccount->setMaximumSize(QSize(130, 16777215));
        EditAccount->setCursor(QCursor(Qt::PointingHandCursor));
        EditAccount->setStyleSheet(QString::fromUtf8("padding:5;\n"
""));

        horizontalLayout_3->addWidget(EditAccount);

        Delete = new QPushButton(frame_2);
        Delete->setObjectName("Delete");
        Delete->setMinimumSize(QSize(80, 40));
        Delete->setMaximumSize(QSize(80, 16777215));
        Delete->setStyleSheet(QString::fromUtf8("background-color:grey;\n"
"color:white;"));

        horizontalLayout_3->addWidget(Delete);


        verticalLayout_4->addWidget(frame_2);


        verticalLayout_3->addWidget(DeleteAccountFrame, 0, Qt::AlignHCenter);

        ChartOfAccount = new QTreeWidget(ChartOfAccountFrame);
        ChartOfAccount->setObjectName("ChartOfAccount");
        ChartOfAccount->setMinimumSize(QSize(0, 0));
        ChartOfAccount->setFont(font);
        ChartOfAccount->setMouseTracking(false);
        ChartOfAccount->setAutoFillBackground(true);
        ChartOfAccount->setStyleSheet(QString::fromUtf8("background-color:black;\n"
"color:white;\n"
""));
        ChartOfAccount->setLineWidth(5);
        ChartOfAccount->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        ChartOfAccount->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        ChartOfAccount->setSizeAdjustPolicy(QAbstractScrollArea::AdjustToContents);
        ChartOfAccount->setEditTriggers(QAbstractItemView::NoEditTriggers);
        ChartOfAccount->setAlternatingRowColors(false);
        ChartOfAccount->setSelectionMode(QAbstractItemView::NoSelection);
        ChartOfAccount->header()->setDefaultSectionSize(300);

        verticalLayout_3->addWidget(ChartOfAccount);


        verticalLayout_2->addWidget(ChartOfAccountFrame);

        AccountWindow->addWidget(AccountWindowStacked);

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
"</style></head><body style=\" font-family:'Segoe UI'; font-size:9pt; font-weight:400; font-style:normal;\">\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px; font-family:'Sans Serif';\"><br /></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-family:'Sans Serif'; font-size:14pt;\">ACCOUNTING MADE EASY</span></p></body></html>", nullptr));
        pushButton->setText(QCoreApplication::translate("ChartOfAccountWindow", "PushButton", nullptr));
        CreateAccount->setText(QCoreApplication::translate("ChartOfAccountWindow", "Create Account", nullptr));
        BasicInfo->setText(QCoreApplication::translate("ChartOfAccountWindow", "Here are your list of Accounts:", nullptr));
        DeleteLabel->setText(QCoreApplication::translate("ChartOfAccountWindow", "Selected Account", nullptr));
        Cancel->setText(QCoreApplication::translate("ChartOfAccountWindow", "CANCEL", nullptr));
        EditAccount->setText(QCoreApplication::translate("ChartOfAccountWindow", "Edit Account", nullptr));
        Delete->setText(QCoreApplication::translate("ChartOfAccountWindow", "DELETE", nullptr));
        QTreeWidgetItem *___qtreewidgetitem = ChartOfAccount->headerItem();
        ___qtreewidgetitem->setText(3, QCoreApplication::translate("ChartOfAccountWindow", "BALANCE", nullptr));
        ___qtreewidgetitem->setText(2, QCoreApplication::translate("ChartOfAccountWindow", "TYPE", nullptr));
        ___qtreewidgetitem->setText(1, QCoreApplication::translate("ChartOfAccountWindow", "Name", nullptr));
        ___qtreewidgetitem->setText(0, QCoreApplication::translate("ChartOfAccountWindow", "Code", nullptr));
    } // retranslateUi

};

namespace Ui {
    class ChartOfAccountWindow: public Ui_ChartOfAccountWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CHARTOFACCOUNTWINDOW_H
