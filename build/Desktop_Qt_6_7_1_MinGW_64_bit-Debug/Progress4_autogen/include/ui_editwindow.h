/********************************************************************************
** Form generated from reading UI file 'editwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.7.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_EDITWINDOW_H
#define UI_EDITWINDOW_H

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
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_EditWindow
{
public:
    QWidget *centralwidget;
    QVBoxLayout *verticalLayout;
    QFrame *Container;
    QVBoxLayout *verticalLayout_3;
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
    QFrame *frame_9;
    QHBoxLayout *horizontalLayout;
    QPushButton *Cancel;
    QPushButton *Save;
    QFrame *frame;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *EditWindow)
    {
        if (EditWindow->objectName().isEmpty())
            EditWindow->setObjectName("EditWindow");
        EditWindow->resize(1169, 746);
        centralwidget = new QWidget(EditWindow);
        centralwidget->setObjectName("centralwidget");
        verticalLayout = new QVBoxLayout(centralwidget);
        verticalLayout->setObjectName("verticalLayout");
        Container = new QFrame(centralwidget);
        Container->setObjectName("Container");
        Container->setMinimumSize(QSize(0, 500));
        Container->setFrameShape(QFrame::StyledPanel);
        Container->setFrameShadow(QFrame::Raised);
        verticalLayout_3 = new QVBoxLayout(Container);
        verticalLayout_3->setObjectName("verticalLayout_3");
        SelectCategory = new QFrame(Container);
        SelectCategory->setObjectName("SelectCategory");
        SelectCategory->setMinimumSize(QSize(0, 100));
        SelectCategory->setMaximumSize(QSize(16777215, 100));
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
        ChildCheckbox->setCheckable(true);
        ChildCheckbox->setChecked(false);

        gridLayout->addWidget(ChildCheckbox, 0, 0, 1, 1);

        ParentCheckbox = new QCheckBox(SelectCategory);
        ParentCheckbox->setObjectName("ParentCheckbox");
        ParentCheckbox->setMinimumSize(QSize(12, 12));
        ParentCheckbox->setMaximumSize(QSize(12, 12));
        ParentCheckbox->setCursor(QCursor(Qt::PointingHandCursor));
        ParentCheckbox->setCheckable(true);

        gridLayout->addWidget(ParentCheckbox, 2, 0, 1, 1);


        verticalLayout_3->addWidget(SelectCategory, 0, Qt::AlignRight);

        InfoContainer = new QFrame(Container);
        InfoContainer->setObjectName("InfoContainer");
        InfoContainer->setMinimumSize(QSize(0, 130));
        InfoContainer->setMaximumSize(QSize(16777215, 130));
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
        QFont font;
        font.setFamilies({QString::fromUtf8("Rockwell Extra Bold")});
        font.setPointSize(15);
        font.setBold(true);
        font.setItalic(false);
        font.setUnderline(true);
        Info->setFont(font);
        Info->setStyleSheet(QString::fromUtf8("font: 800 15pt \"Rockwell Extra Bold\";\n"
"text-decoration:underline;"));

        verticalLayout_4->addWidget(Info);


        verticalLayout_3->addWidget(InfoContainer, 0, Qt::AlignHCenter);

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
        ReadName->setFrame(true);
        ReadName->setCursorMoveStyle(Qt::VisualMoveStyle);

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
        label_11->setMaximumSize(QSize(50, 16777215));
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
        label_10->setMaximumSize(QSize(110, 16777215));
        label_10->setStyleSheet(QString::fromUtf8("font: 800 10pt \"Rockwell Extra Bold\";"));

        horizontalLayout_7->addWidget(label_10);

        ReadHeader = new QComboBox(ParentFrame);
        ReadHeader->setObjectName("ReadHeader");
        ReadHeader->setMinimumSize(QSize(250, 0));

        horizontalLayout_7->addWidget(ReadHeader);


        verticalLayout_2->addWidget(ParentFrame);

        frame_9 = new QFrame(Details);
        frame_9->setObjectName("frame_9");
        frame_9->setMinimumSize(QSize(300, 40));
        frame_9->setMaximumSize(QSize(400, 50));
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


        verticalLayout_2->addWidget(frame_9, 0, Qt::AlignHCenter);


        verticalLayout_3->addWidget(Details, 0, Qt::AlignHCenter);


        verticalLayout->addWidget(Container);

        frame = new QFrame(centralwidget);
        frame->setObjectName("frame");
        frame->setMaximumSize(QSize(16777215, 300));
        frame->setFrameShape(QFrame::StyledPanel);
        frame->setFrameShadow(QFrame::Raised);

        verticalLayout->addWidget(frame);

        EditWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(EditWindow);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 1169, 22));
        EditWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(EditWindow);
        statusbar->setObjectName("statusbar");
        EditWindow->setStatusBar(statusbar);

        retranslateUi(EditWindow);

        QMetaObject::connectSlotsByName(EditWindow);
    } // setupUi

    void retranslateUi(QMainWindow *EditWindow)
    {
        EditWindow->setWindowTitle(QCoreApplication::translate("EditWindow", "EditWindow", nullptr));
        label_3->setText(QCoreApplication::translate("EditWindow", "Child Category", nullptr));
        label_2->setText(QCoreApplication::translate("EditWindow", "Header Catergory", nullptr));
        ChildCheckbox->setText(QCoreApplication::translate("EditWindow", "CheckBox", nullptr));
        ParentCheckbox->setText(QCoreApplication::translate("EditWindow", "CheckBox", nullptr));
        Image->setText(QString());
        Info->setText(QCoreApplication::translate("EditWindow", "Enter Details:", nullptr));
        label_14->setText(QCoreApplication::translate("EditWindow", "NAME:", nullptr));
        label_13->setText(QCoreApplication::translate("EditWindow", "CODE:", nullptr));
        label_11->setText(QCoreApplication::translate("EditWindow", "TYPE:", nullptr));
        ReadType->setItemText(0, QCoreApplication::translate("EditWindow", "ASSETS", nullptr));
        ReadType->setItemText(1, QCoreApplication::translate("EditWindow", "LIABILITIES", nullptr));
        ReadType->setItemText(2, QCoreApplication::translate("EditWindow", "EQUITY", nullptr));

        label_12->setText(QCoreApplication::translate("EditWindow", "OPENING BALANCE:", nullptr));
        label_10->setText(QCoreApplication::translate("EditWindow", "PARENT HEADER:", nullptr));
        Cancel->setText(QCoreApplication::translate("EditWindow", "Cancel", nullptr));
        Save->setText(QCoreApplication::translate("EditWindow", "Save", nullptr));
    } // retranslateUi

};

namespace Ui {
    class EditWindow: public Ui_EditWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_EDITWINDOW_H
