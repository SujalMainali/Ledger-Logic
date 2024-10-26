/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.7.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QScrollArea>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QGridLayout *gridLayout_3;
    QFrame *Container;
    QVBoxLayout *verticalLayout;
    QFrame *UpperLogoBar;
    QLabel *AppLogo;
    QTextEdit *Motto;
    QFrame *Window;
    QHBoxLayout *horizontalLayout_3;
    QWidget *Navbar;
    QGridLayout *gridLayout_2;
    QSpacerItem *verticalSpacer_3;
    QSpacerItem *verticalSpacer_7;
    QPushButton *Sales;
    QPushButton *Reporting;
    QSpacerItem *verticalSpacer_5;
    QSpacerItem *verticalSpacer_8;
    QPushButton *Purchase;
    QSpacerItem *verticalSpacer_6;
    QPushButton *Accounting;
    QSpacerItem *verticalSpacer_4;
    QSpacerItem *verticalSpacer_9;
    QSpacerItem *verticalSpacer_2;
    QSpacerItem *verticalSpacer;
    QWidget *Border;
    QScrollArea *Background;
    QWidget *scrollAreaWidgetContents_2;
    QGridLayout *gridLayout;
    QFrame *frame_3;
    QGridLayout *gridLayout_5;
    QLineEdit *ContextOfGraph;
    QFrame *frame;
    QGridLayout *gridLayout_6;
    QHBoxLayout *SecondGraph;
    QHBoxLayout *FirstGraph;
    QPushButton *pushButton;
    QFrame *frame_2;
    QGridLayout *gridLayout_4;
    QTextEdit *WelcomeMessage;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(1260, 690);
        MainWindow->setAutoFillBackground(false);
        MainWindow->setStyleSheet(QString::fromUtf8(" background-color:black;"));
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        gridLayout_3 = new QGridLayout(centralwidget);
        gridLayout_3->setObjectName("gridLayout_3");
        Container = new QFrame(centralwidget);
        Container->setObjectName("Container");
        Container->setMinimumSize(QSize(0, 100));
        Container->setFrameShape(QFrame::StyledPanel);
        Container->setFrameShadow(QFrame::Raised);
        verticalLayout = new QVBoxLayout(Container);
        verticalLayout->setSpacing(0);
        verticalLayout->setObjectName("verticalLayout");
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        UpperLogoBar = new QFrame(Container);
        UpperLogoBar->setObjectName("UpperLogoBar");
        UpperLogoBar->setMinimumSize(QSize(0, 100));
        UpperLogoBar->setStyleSheet(QString::fromUtf8(""));
        UpperLogoBar->setFrameShape(QFrame::StyledPanel);
        UpperLogoBar->setFrameShadow(QFrame::Raised);
        AppLogo = new QLabel(UpperLogoBar);
        AppLogo->setObjectName("AppLogo");
        AppLogo->setGeometry(QRect(10, 10, 300, 80));
        AppLogo->setMinimumSize(QSize(300, 0));
        AppLogo->setMaximumSize(QSize(300, 16777215));
        AppLogo->setPixmap(QPixmap(QString::fromUtf8(":/images/AppLogo.png")));
        Motto = new QTextEdit(UpperLogoBar);
        Motto->setObjectName("Motto");
        Motto->setGeometry(QRect(290, 10, 914, 80));
        Motto->viewport()->setProperty("cursor", QVariant(QCursor(Qt::IBeamCursor)));
        Motto->setStyleSheet(QString::fromUtf8("margin-bottom:3px;\n"
"color:white;"));
        Motto->setReadOnly(true);

        verticalLayout->addWidget(UpperLogoBar);

        Window = new QFrame(Container);
        Window->setObjectName("Window");
        Window->setMinimumSize(QSize(1000, 0));
        Window->setStyleSheet(QString::fromUtf8("\n"
"border-color:rgb(103, 163, 202);\n"
"border-color:rgb(189, 219, 240);;\n"
"color:white;\n"
""));
        Window->setFrameShape(QFrame::StyledPanel);
        Window->setFrameShadow(QFrame::Raised);
        horizontalLayout_3 = new QHBoxLayout(Window);
        horizontalLayout_3->setSpacing(0);
        horizontalLayout_3->setObjectName("horizontalLayout_3");
        horizontalLayout_3->setContentsMargins(0, 0, 0, 0);
        Navbar = new QWidget(Window);
        Navbar->setObjectName("Navbar");
        Navbar->setEnabled(true);
        QSizePolicy sizePolicy(QSizePolicy::Policy::Preferred, QSizePolicy::Policy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(30);
        sizePolicy.setHeightForWidth(Navbar->sizePolicy().hasHeightForWidth());
        Navbar->setSizePolicy(sizePolicy);
        Navbar->setMinimumSize(QSize(200, 0));
        Navbar->setMaximumSize(QSize(200, 16777215));
        Navbar->setLayoutDirection(Qt::LeftToRight);
        Navbar->setStyleSheet(QString::fromUtf8("margin:15px;\n"
"\n"
"\n"
""));
        gridLayout_2 = new QGridLayout(Navbar);
        gridLayout_2->setObjectName("gridLayout_2");
        gridLayout_2->setHorizontalSpacing(0);
        gridLayout_2->setContentsMargins(0, 30, 0, -1);
        verticalSpacer_3 = new QSpacerItem(20, 40, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        gridLayout_2->addItem(verticalSpacer_3, 10, 0, 1, 1);

        verticalSpacer_7 = new QSpacerItem(20, 40, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        gridLayout_2->addItem(verticalSpacer_7, 14, 0, 1, 1);

        Sales = new QPushButton(Navbar);
        Sales->setObjectName("Sales");
        Sales->setMinimumSize(QSize(0, 60));
        Sales->setCursor(QCursor(Qt::PointingHandCursor));
        Sales->setStyleSheet(QString::fromUtf8("background-color:rgb(191, 226, 228);;\n"
"color:black;\n"
"border-radius:7px;"));

        gridLayout_2->addWidget(Sales, 2, 0, 1, 1);

        Reporting = new QPushButton(Navbar);
        Reporting->setObjectName("Reporting");
        Reporting->setMinimumSize(QSize(0, 60));
        Reporting->setCursor(QCursor(Qt::PointingHandCursor));
        Reporting->setStyleSheet(QString::fromUtf8("background-color:rgb(191, 226, 228);;\n"
"color:black;\n"
"border-radius:7px;"));

        gridLayout_2->addWidget(Reporting, 6, 0, 1, 1);

        verticalSpacer_5 = new QSpacerItem(20, 40, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        gridLayout_2->addItem(verticalSpacer_5, 12, 0, 1, 1);

        verticalSpacer_8 = new QSpacerItem(20, 40, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        gridLayout_2->addItem(verticalSpacer_8, 15, 0, 1, 1);

        Purchase = new QPushButton(Navbar);
        Purchase->setObjectName("Purchase");
        Purchase->setMinimumSize(QSize(0, 60));
        Purchase->setCursor(QCursor(Qt::PointingHandCursor));
        Purchase->setStyleSheet(QString::fromUtf8("background-color:rgb(191, 226, 228);;\n"
"color:black;\n"
"border-radius:7px;"));

        gridLayout_2->addWidget(Purchase, 0, 0, 1, 1);

        verticalSpacer_6 = new QSpacerItem(20, 40, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        gridLayout_2->addItem(verticalSpacer_6, 13, 0, 1, 1);

        Accounting = new QPushButton(Navbar);
        Accounting->setObjectName("Accounting");
        Accounting->setMinimumSize(QSize(0, 60));
        Accounting->setCursor(QCursor(Qt::PointingHandCursor));
        Accounting->setStyleSheet(QString::fromUtf8("background-color:rgb(191, 226, 228);;\n"
"color:black;\n"
"border-radius:7px;"));

        gridLayout_2->addWidget(Accounting, 5, 0, 1, 1);

        verticalSpacer_4 = new QSpacerItem(20, 40, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        gridLayout_2->addItem(verticalSpacer_4, 11, 0, 1, 1);

        verticalSpacer_9 = new QSpacerItem(20, 40, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        gridLayout_2->addItem(verticalSpacer_9, 16, 0, 1, 1);

        verticalSpacer_2 = new QSpacerItem(20, 40, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        gridLayout_2->addItem(verticalSpacer_2, 9, 0, 1, 1);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        gridLayout_2->addItem(verticalSpacer, 8, 0, 1, 1);


        horizontalLayout_3->addWidget(Navbar);

        Border = new QWidget(Window);
        Border->setObjectName("Border");
        Border->setMinimumSize(QSize(10, 0));
        Border->setStyleSheet(QString::fromUtf8("background-color:#8db1d4;"));

        horizontalLayout_3->addWidget(Border);

        Background = new QScrollArea(Window);
        Background->setObjectName("Background");
        QSizePolicy sizePolicy1(QSizePolicy::Policy::Maximum, QSizePolicy::Policy::Expanding);
        sizePolicy1.setHorizontalStretch(30);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(Background->sizePolicy().hasHeightForWidth());
        Background->setSizePolicy(sizePolicy1);
        Background->setMinimumSize(QSize(1000, 0));
        Background->setMaximumSize(QSize(2000, 16777215));
        Background->viewport()->setProperty("cursor", QVariant(QCursor(Qt::ArrowCursor)));
        Background->setStyleSheet(QString::fromUtf8("\n"
"	border:none;\n"
" padding-top:10px;\n"
"\n"
""));
        Background->setWidgetResizable(true);
        scrollAreaWidgetContents_2 = new QWidget();
        scrollAreaWidgetContents_2->setObjectName("scrollAreaWidgetContents_2");
        scrollAreaWidgetContents_2->setGeometry(QRect(0, 0, 1008, 548));
        QSizePolicy sizePolicy2(QSizePolicy::Policy::Preferred, QSizePolicy::Policy::Preferred);
        sizePolicy2.setHorizontalStretch(30);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(scrollAreaWidgetContents_2->sizePolicy().hasHeightForWidth());
        scrollAreaWidgetContents_2->setSizePolicy(sizePolicy2);
        gridLayout = new QGridLayout(scrollAreaWidgetContents_2);
        gridLayout->setObjectName("gridLayout");
        frame_3 = new QFrame(scrollAreaWidgetContents_2);
        frame_3->setObjectName("frame_3");
        frame_3->setMaximumSize(QSize(2000, 100));
        frame_3->setStyleSheet(QString::fromUtf8(""));
        frame_3->setFrameShape(QFrame::StyledPanel);
        frame_3->setFrameShadow(QFrame::Raised);
        gridLayout_5 = new QGridLayout(frame_3);
        gridLayout_5->setObjectName("gridLayout_5");
        ContextOfGraph = new QLineEdit(frame_3);
        ContextOfGraph->setObjectName("ContextOfGraph");
        ContextOfGraph->setMinimumSize(QSize(600, 40));
        ContextOfGraph->setMaximumSize(QSize(600, 40));
        QFont font;
        font.setFamilies({QString::fromUtf8("Sitka Heading")});
        font.setPointSize(12);
        font.setBold(true);
        font.setItalic(true);
        ContextOfGraph->setFont(font);
        ContextOfGraph->setStyleSheet(QString::fromUtf8("padding-left:15px;\n"
"\n"
"font: 700 italic 12pt \"Sitka Heading\";"));
        ContextOfGraph->setReadOnly(true);

        gridLayout_5->addWidget(ContextOfGraph, 0, 0, 1, 1);


        gridLayout->addWidget(frame_3, 2, 0, 1, 1, Qt::AlignLeft|Qt::AlignVCenter);

        frame = new QFrame(scrollAreaWidgetContents_2);
        frame->setObjectName("frame");
        frame->setMaximumSize(QSize(2000, 500));
        frame->setStyleSheet(QString::fromUtf8("background-color: rgb 54,15,1;\n"
""));
        frame->setFrameShape(QFrame::StyledPanel);
        frame->setFrameShadow(QFrame::Raised);
        gridLayout_6 = new QGridLayout(frame);
        gridLayout_6->setObjectName("gridLayout_6");
        SecondGraph = new QHBoxLayout();
        SecondGraph->setObjectName("SecondGraph");

        gridLayout_6->addLayout(SecondGraph, 0, 0, 1, 1);

        FirstGraph = new QHBoxLayout();
        FirstGraph->setObjectName("FirstGraph");

        gridLayout_6->addLayout(FirstGraph, 0, 1, 1, 1);


        gridLayout->addWidget(frame, 4, 0, 1, 1);

        pushButton = new QPushButton(scrollAreaWidgetContents_2);
        pushButton->setObjectName("pushButton");
        pushButton->setMaximumSize(QSize(50, 60));
        pushButton->setCursor(QCursor(Qt::PointingHandCursor));
        pushButton->setAutoFillBackground(false);
        pushButton->setStyleSheet(QString::fromUtf8(""));
        QIcon icon;
        QString iconThemeName = QString::fromUtf8("battery");
        if (QIcon::hasThemeIcon(iconThemeName)) {
            icon = QIcon::fromTheme(iconThemeName);
        } else {
            icon.addFile(QString::fromUtf8(":/images/NavbarLogo1.png"), QSize(), QIcon::Active, QIcon::On);
        }
        pushButton->setIcon(icon);
        pushButton->setIconSize(QSize(70, 60));

        gridLayout->addWidget(pushButton, 1, 0, 1, 1);

        frame_2 = new QFrame(scrollAreaWidgetContents_2);
        frame_2->setObjectName("frame_2");
        frame_2->setMaximumSize(QSize(2000, 100));
        frame_2->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255)"));
        frame_2->setFrameShape(QFrame::StyledPanel);
        frame_2->setFrameShadow(QFrame::Raised);
        gridLayout_4 = new QGridLayout(frame_2);
        gridLayout_4->setObjectName("gridLayout_4");
        WelcomeMessage = new QTextEdit(frame_2);
        WelcomeMessage->setObjectName("WelcomeMessage");
        WelcomeMessage->setMinimumSize(QSize(0, 100));
        WelcomeMessage->setMaximumSize(QSize(400, 80));
        QFont font1;
        font1.setFamilies({QString::fromUtf8("Arial Narrow")});
        font1.setPointSize(15);
        WelcomeMessage->setFont(font1);
        WelcomeMessage->setStyleSheet(QString::fromUtf8("color:black;"));
        WelcomeMessage->setReadOnly(true);

        gridLayout_4->addWidget(WelcomeMessage, 1, 0, 1, 1);


        gridLayout->addWidget(frame_2, 0, 0, 1, 1);

        Background->setWidget(scrollAreaWidgetContents_2);

        horizontalLayout_3->addWidget(Background);


        verticalLayout->addWidget(Window);


        gridLayout_3->addWidget(Container, 0, 0, 1, 1);

        MainWindow->setCentralWidget(centralwidget);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        AppLogo->setText(QString());
        Motto->setHtml(QCoreApplication::translate("MainWindow", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><meta charset=\"utf-8\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"hr { height: 1px; border-width: 0; }\n"
"li.unchecked::marker { content: \"\\2610\"; }\n"
"li.checked::marker { content: \"\\2612\"; }\n"
"</style></head><body style=\" font-family:'Sans Serif'; font-size:9pt; font-weight:400; font-style:normal;\">\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><br /></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:14pt;\">ACCOUNTING MADE EASY</span></p></body></html>", nullptr));
        Sales->setText(QCoreApplication::translate("MainWindow", "Sales", nullptr));
        Reporting->setText(QCoreApplication::translate("MainWindow", "Reporting", nullptr));
        Purchase->setText(QCoreApplication::translate("MainWindow", "Purchases", nullptr));
        Accounting->setText(QCoreApplication::translate("MainWindow", "Accounting", nullptr));
        ContextOfGraph->setText(QCoreApplication::translate("MainWindow", "Here are some graphs that we have prepared for you:", nullptr));
        pushButton->setText(QString());
        WelcomeMessage->setHtml(QCoreApplication::translate("MainWindow", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><meta charset=\"utf-8\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"hr { height: 1px; border-width: 0; }\n"
"li.unchecked::marker { content: \"\\2610\"; }\n"
"li.checked::marker { content: \"\\2612\"; }\n"
"</style></head><body style=\" font-family:'Arial Narrow'; font-size:15pt; font-weight:400; font-style:normal;\">\n"
"<p align=\"center\" style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-family:'Sans Serif'; font-size:20pt;\">Welcome Back!</span></p>\n"
"<p align=\"center\" style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-family:'Sans Serif'; font-size:16pt;\">Your Business is Waiting For You!</span></p></body></html>", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
