/********************************************************************************
** Form generated from reading UI file 'AddWindow.ui'
**
** Created by: Qt User Interface Compiler version 6.7.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ADDWINDOW_H
#define UI_ADDWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_AddWindow
{
public:
    QWidget *centralwidget;
    QHBoxLayout *horizontalLayout_2;
    QFrame *Container;
    QVBoxLayout *verticalLayout;
    QFrame *SelectCategory;
    QGridLayout *gridLayout;
    QLabel *label_3;
    QLabel *label_2;
    QCheckBox *ChildCheckbox;
    QCheckBox *ParentCheckbox;
    QFrame *InfoContainer;
    QVBoxLayout *verticalLayout_4;
    QLabel *Image;
    QLabel *Info;
    QFrame *Details;
    QVBoxLayout *verticalLayout_2;
    QFrame *frame_8;
    QHBoxLayout *horizontalLayout_3;
    QLabel *label_14;
    QLineEdit *ReadName;
    QFrame *frame_7;
    QHBoxLayout *horizontalLayout_4;
    QLabel *label_13;
    QLineEdit *ReadCode;
    QFrame *frame_5;
    QHBoxLayout *horizontalLayout_5;
    QLabel *label_11;
    QComboBox *ReadType;
    QFrame *BalanceFrame;
    QHBoxLayout *horizontalLayout_6;
    QLabel *label_12;
    QLineEdit *ReadBalance;
    QFrame *ParentFrame;
    QHBoxLayout *horizontalLayout_7;
    QLabel *label_10;
    QComboBox *ReadHeader;
    QFrame *Notes;
    QVBoxLayout *verticalLayout_3;
    QLabel *label_9;
    QFrame *frame;
    QHBoxLayout *horizontalLayout_8;
    QLineEdit *lineEdit_6;
    QFrame *frame_9;
    QHBoxLayout *horizontalLayout;
    QPushButton *Cancel;
    QPushButton *Save;

    void setupUi(QMainWindow *AddWindow)
    {
        if (AddWindow->objectName().isEmpty())
            AddWindow->setObjectName("AddWindow");
        AddWindow->resize(1256, 817);
        QFont font;
        font.setFamilies({QString::fromUtf8("Arial Narrow")});
        font.setPointSize(15);
        AddWindow->setFont(font);
        AddWindow->setStyleSheet(QString::fromUtf8("background-color: black;\n"
"color:white;\n"
"\n"
"border:none;"));
        centralwidget = new QWidget(AddWindow);
        centralwidget->setObjectName("centralwidget");
        horizontalLayout_2 = new QHBoxLayout(centralwidget);
        horizontalLayout_2->setObjectName("horizontalLayout_2");
        Container = new QFrame(centralwidget);
        Container->setObjectName("Container");
        Container->setFrameShape(QFrame::StyledPanel);
        Container->setFrameShadow(QFrame::Raised);
        verticalLayout = new QVBoxLayout(Container);
        verticalLayout->setObjectName("verticalLayout");
        SelectCategory = new QFrame(Container);
        SelectCategory->setObjectName("SelectCategory");
        SelectCategory->setMinimumSize(QSize(0, 100));
        SelectCategory->setCursor(QCursor(Qt::PointingHandCursor));
        SelectCategory->setMouseTracking(true);
        SelectCategory->setTabletTracking(false);
        SelectCategory->setStyleSheet(QString::fromUtf8("QCheckBox{\n"
"background-color:white;\n"
"color:black;\n"
"}"));
        SelectCategory->setFrameShape(QFrame::StyledPanel);
        SelectCategory->setFrameShadow(QFrame::Raised);
        gridLayout = new QGridLayout(SelectCategory);
        gridLayout->setObjectName("gridLayout");
        label_3 = new QLabel(SelectCategory);
        label_3->setObjectName("label_3");

        gridLayout->addWidget(label_3, 0, 1, 1, 1);

        label_2 = new QLabel(SelectCategory);
        label_2->setObjectName("label_2");

        gridLayout->addWidget(label_2, 2, 1, 1, 1);

        ChildCheckbox = new QCheckBox(SelectCategory);
        ChildCheckbox->setObjectName("ChildCheckbox");
        ChildCheckbox->setMinimumSize(QSize(12, 12));
        ChildCheckbox->setMaximumSize(QSize(12, 12));
        ChildCheckbox->setCursor(QCursor(Qt::PointingHandCursor));
        ChildCheckbox->setChecked(true);

        gridLayout->addWidget(ChildCheckbox, 0, 0, 1, 1);

        ParentCheckbox = new QCheckBox(SelectCategory);
        ParentCheckbox->setObjectName("ParentCheckbox");
        ParentCheckbox->setMinimumSize(QSize(12, 12));
        ParentCheckbox->setMaximumSize(QSize(12, 12));
        ParentCheckbox->setCursor(QCursor(Qt::PointingHandCursor));

        gridLayout->addWidget(ParentCheckbox, 2, 0, 1, 1);


        verticalLayout->addWidget(SelectCategory, 0, Qt::AlignRight|Qt::AlignVCenter);

        InfoContainer = new QFrame(Container);
        InfoContainer->setObjectName("InfoContainer");
        InfoContainer->setFrameShape(QFrame::StyledPanel);
        InfoContainer->setFrameShadow(QFrame::Raised);
        verticalLayout_4 = new QVBoxLayout(InfoContainer);
        verticalLayout_4->setObjectName("verticalLayout_4");
        Image = new QLabel(InfoContainer);
        Image->setObjectName("Image");
        Image->setMinimumSize(QSize(0, 80));
        Image->setStyleSheet(QString::fromUtf8("background-color:white;"));
        Image->setPixmap(QPixmap(QString::fromUtf8(":/images/EnterDetailImage.jpg")));
        Image->setScaledContents(true);

        verticalLayout_4->addWidget(Image);

        Info = new QLabel(InfoContainer);
        Info->setObjectName("Info");
        Info->setMinimumSize(QSize(0, 30));
        QFont font1;
        font1.setFamilies({QString::fromUtf8("Rockwell Extra Bold")});
        font1.setPointSize(15);
        font1.setBold(true);
        font1.setItalic(false);
        font1.setUnderline(true);
        Info->setFont(font1);
        Info->setStyleSheet(QString::fromUtf8("font: 800 15pt \"Rockwell Extra Bold\";\n"
"text-decoration:underline;"));

        verticalLayout_4->addWidget(Info);


        verticalLayout->addWidget(InfoContainer, 0, Qt::AlignHCenter|Qt::AlignVCenter);

        Details = new QFrame(Container);
        Details->setObjectName("Details");
        Details->setMinimumSize(QSize(0, 300));
        Details->setStyleSheet(QString::fromUtf8("QComboBox{\n"
"background-color: gray;\n"
"font: 12pt \"Maiandra GD\";\n"
"border-radius: 7px;\n"
"}"));
        Details->setFrameShape(QFrame::StyledPanel);
        Details->setFrameShadow(QFrame::Raised);
        verticalLayout_2 = new QVBoxLayout(Details);
        verticalLayout_2->setObjectName("verticalLayout_2");
        frame_8 = new QFrame(Details);
        frame_8->setObjectName("frame_8");
        frame_8->setFrameShape(QFrame::StyledPanel);
        frame_8->setFrameShadow(QFrame::Raised);
        horizontalLayout_3 = new QHBoxLayout(frame_8);
        horizontalLayout_3->setObjectName("horizontalLayout_3");
        label_14 = new QLabel(frame_8);
        label_14->setObjectName("label_14");
        label_14->setStyleSheet(QString::fromUtf8("font: 800 10pt \"Rockwell Extra Bold\";"));

        horizontalLayout_3->addWidget(label_14);

        ReadName = new QLineEdit(frame_8);
        ReadName->setObjectName("ReadName");
        ReadName->setStyleSheet(QString::fromUtf8("background-color: gray;\n"
"font: 12pt \"Maiandra GD\";\n"
"border-radius:7px;\n"
"\n"
"\n"
"\n"
"\n"
""));

        horizontalLayout_3->addWidget(ReadName);


        verticalLayout_2->addWidget(frame_8);

        frame_7 = new QFrame(Details);
        frame_7->setObjectName("frame_7");
        frame_7->setFrameShape(QFrame::StyledPanel);
        frame_7->setFrameShadow(QFrame::Raised);
        horizontalLayout_4 = new QHBoxLayout(frame_7);
        horizontalLayout_4->setObjectName("horizontalLayout_4");
        label_13 = new QLabel(frame_7);
        label_13->setObjectName("label_13");
        label_13->setStyleSheet(QString::fromUtf8("font: 800 10pt \"Rockwell Extra Bold\";"));

        horizontalLayout_4->addWidget(label_13);

        ReadCode = new QLineEdit(frame_7);
        ReadCode->setObjectName("ReadCode");
        ReadCode->setStyleSheet(QString::fromUtf8("background-color: gray;\n"
"font: 12pt \"Maiandra GD\";\n"
"border-radius: 7px;\n"
"\n"
"\n"
"\n"
""));

        horizontalLayout_4->addWidget(ReadCode);


        verticalLayout_2->addWidget(frame_7);

        frame_5 = new QFrame(Details);
        frame_5->setObjectName("frame_5");
        frame_5->setFrameShape(QFrame::StyledPanel);
        frame_5->setFrameShadow(QFrame::Raised);
        horizontalLayout_5 = new QHBoxLayout(frame_5);
        horizontalLayout_5->setObjectName("horizontalLayout_5");
        label_11 = new QLabel(frame_5);
        label_11->setObjectName("label_11");
        label_11->setStyleSheet(QString::fromUtf8("font: 800 10pt \"Rockwell Extra Bold\";"));

        horizontalLayout_5->addWidget(label_11);

        ReadType = new QComboBox(frame_5);
        ReadType->addItem(QString());
        ReadType->addItem(QString());
        ReadType->addItem(QString());
        ReadType->setObjectName("ReadType");
        ReadType->setMinimumSize(QSize(340, 0));

        horizontalLayout_5->addWidget(ReadType);


        verticalLayout_2->addWidget(frame_5);

        BalanceFrame = new QFrame(Details);
        BalanceFrame->setObjectName("BalanceFrame");
        BalanceFrame->setFrameShape(QFrame::StyledPanel);
        BalanceFrame->setFrameShadow(QFrame::Raised);
        horizontalLayout_6 = new QHBoxLayout(BalanceFrame);
        horizontalLayout_6->setObjectName("horizontalLayout_6");
        label_12 = new QLabel(BalanceFrame);
        label_12->setObjectName("label_12");
        label_12->setStyleSheet(QString::fromUtf8("font: 800 10pt \"Rockwell Extra Bold\";"));

        horizontalLayout_6->addWidget(label_12);

        ReadBalance = new QLineEdit(BalanceFrame);
        ReadBalance->setObjectName("ReadBalance");
        ReadBalance->setStyleSheet(QString::fromUtf8("background-color: gray;\n"
"font: 12pt \"Maiandra GD\";\n"
"border-radius: 7px;\n"
"\n"
"\n"
"\n"
"\n"
""));

        horizontalLayout_6->addWidget(ReadBalance);


        verticalLayout_2->addWidget(BalanceFrame);

        ParentFrame = new QFrame(Details);
        ParentFrame->setObjectName("ParentFrame");
        ParentFrame->setMinimumSize(QSize(400, 0));
        ParentFrame->setFrameShape(QFrame::StyledPanel);
        ParentFrame->setFrameShadow(QFrame::Raised);
        horizontalLayout_7 = new QHBoxLayout(ParentFrame);
        horizontalLayout_7->setObjectName("horizontalLayout_7");
        label_10 = new QLabel(ParentFrame);
        label_10->setObjectName("label_10");
        label_10->setStyleSheet(QString::fromUtf8("font: 800 10pt \"Rockwell Extra Bold\";"));

        horizontalLayout_7->addWidget(label_10);

        ReadHeader = new QComboBox(ParentFrame);
        ReadHeader->setObjectName("ReadHeader");
        ReadHeader->setMinimumSize(QSize(250, 0));

        horizontalLayout_7->addWidget(ReadHeader);


        verticalLayout_2->addWidget(ParentFrame);


        verticalLayout->addWidget(Details, 0, Qt::AlignHCenter|Qt::AlignVCenter);

        Notes = new QFrame(Container);
        Notes->setObjectName("Notes");
        Notes->setMinimumSize(QSize(0, 200));
        Notes->setStyleSheet(QString::fromUtf8("background-color:rgb(164, 170, 158)"));
        Notes->setFrameShape(QFrame::StyledPanel);
        Notes->setFrameShadow(QFrame::Raised);
        verticalLayout_3 = new QVBoxLayout(Notes);
        verticalLayout_3->setObjectName("verticalLayout_3");
        label_9 = new QLabel(Notes);
        label_9->setObjectName("label_9");
        label_9->setMinimumSize(QSize(50, 50));
        label_9->setStyleSheet(QString::fromUtf8("font: 800 15pt \"Rockwell Extra Bold\";\n"
"background-color: rgb(18, 18, 18);\n"
"padding: 15;"));

        verticalLayout_3->addWidget(label_9, 0, Qt::AlignHCenter);

        frame = new QFrame(Notes);
        frame->setObjectName("frame");
        frame->setMinimumSize(QSize(0, 100));
        frame->setFrameShape(QFrame::StyledPanel);
        frame->setFrameShadow(QFrame::Raised);
        horizontalLayout_8 = new QHBoxLayout(frame);
        horizontalLayout_8->setObjectName("horizontalLayout_8");
        lineEdit_6 = new QLineEdit(frame);
        lineEdit_6->setObjectName("lineEdit_6");
        lineEdit_6->setMinimumSize(QSize(500, 100));
        lineEdit_6->setMaximumSize(QSize(300, 16777215));
        lineEdit_6->setStyleSheet(QString::fromUtf8("background-color: gray;\n"
"\n"
"font: 13pt \"Maiandra GD\";\n"
"border-radius: 7px;\n"
"\n"
"\n"
"\n"
""));

        horizontalLayout_8->addWidget(lineEdit_6);


        verticalLayout_3->addWidget(frame);

        frame_9 = new QFrame(Notes);
        frame_9->setObjectName("frame_9");
        frame_9->setMinimumSize(QSize(300, 40));
        frame_9->setStyleSheet(QString::fromUtf8("QPushButton{\n"
"	border:2px solid black;\n"
"	border-radius:5px;\n"
"	background-color:grey;\n"
"}\n"
""));
        frame_9->setFrameShape(QFrame::StyledPanel);
        frame_9->setFrameShadow(QFrame::Raised);
        horizontalLayout = new QHBoxLayout(frame_9);
        horizontalLayout->setObjectName("horizontalLayout");
        Cancel = new QPushButton(frame_9);
        Cancel->setObjectName("Cancel");
        Cancel->setMinimumSize(QSize(0, 30));
        Cancel->setStyleSheet(QString::fromUtf8("font: 800 10pt \"Rockwell Extra Bold\";\n"
""));

        horizontalLayout->addWidget(Cancel);

        Save = new QPushButton(frame_9);
        Save->setObjectName("Save");
        Save->setMinimumSize(QSize(0, 30));
        Save->setStyleSheet(QString::fromUtf8("font: 800 10pt \"Rockwell Extra Bold\";"));

        horizontalLayout->addWidget(Save);


        verticalLayout_3->addWidget(frame_9, 0, Qt::AlignHCenter);


        verticalLayout->addWidget(Notes);


        horizontalLayout_2->addWidget(Container);

        AddWindow->setCentralWidget(centralwidget);

        retranslateUi(AddWindow);

        QMetaObject::connectSlotsByName(AddWindow);
    } // setupUi

    void retranslateUi(QMainWindow *AddWindow)
    {
        AddWindow->setWindowTitle(QCoreApplication::translate("AddWindow", "MainWindow1", nullptr));
        label_3->setText(QCoreApplication::translate("AddWindow", "Child Category", nullptr));
        label_2->setText(QCoreApplication::translate("AddWindow", "Header Catergory", nullptr));
        ChildCheckbox->setText(QCoreApplication::translate("AddWindow", "CheckBox", nullptr));
        ParentCheckbox->setText(QCoreApplication::translate("AddWindow", "CheckBox", nullptr));
        Image->setText(QString());
        Info->setText(QCoreApplication::translate("AddWindow", "Enter Details:", nullptr));
        label_14->setText(QCoreApplication::translate("AddWindow", "NAME:", nullptr));
        label_13->setText(QCoreApplication::translate("AddWindow", "CODE:", nullptr));
        label_11->setText(QCoreApplication::translate("AddWindow", "TYPE:", nullptr));
        ReadType->setItemText(0, QCoreApplication::translate("AddWindow", "ASSETS", nullptr));
        ReadType->setItemText(1, QCoreApplication::translate("AddWindow", "LIABILITIES", nullptr));
        ReadType->setItemText(2, QCoreApplication::translate("AddWindow", "EQUITY", nullptr));

        label_12->setText(QCoreApplication::translate("AddWindow", "OPENING BALANCE:", nullptr));
        label_10->setText(QCoreApplication::translate("AddWindow", "PARENT HEADER:", nullptr));
        label_9->setText(QCoreApplication::translate("AddWindow", "NOTES:", nullptr));
        Cancel->setText(QCoreApplication::translate("AddWindow", "Cancel", nullptr));
        Save->setText(QCoreApplication::translate("AddWindow", "Save", nullptr));
    } // retranslateUi

};

namespace Ui {
    class AddWindow: public Ui_AddWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ADDWINDOW_H
