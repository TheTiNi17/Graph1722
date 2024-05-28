/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.15.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGraphicsView>
#include <QtWidgets/QGroupBox>
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

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QVBoxLayout *verticalLayout_2;
    QGroupBox *groupBox;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout;
    QPushButton *AddNodeButton;
    QLabel *label_8;
    QLineEdit *NameAddLine;
    QLabel *label_9;
    QLineEdit *DescriptionAddLine;
    QHBoxLayout *horizontalLayout_2;
    QPushButton *DelNodeButton;
    QLabel *label_10;
    QLineEdit *NameDelLine;
    QHBoxLayout *horizontalLayout_3;
    QPushButton *ChangeNodeButton;
    QLabel *label_11;
    QLineEdit *OldNameChangeLine;
    QLabel *label_12;
    QLineEdit *NewNameChangeLine;
    QLabel *label_13;
    QLineEdit *NewDescriptionChangeLine;
    QGroupBox *groupBox_2;
    QVBoxLayout *verticalLayout_4;
    QVBoxLayout *verticalLayout_3;
    QHBoxLayout *horizontalLayout_4;
    QPushButton *AddEdgeButton;
    QLabel *label;
    QLineEdit *Name1AddEdgeLine;
    QLabel *label_2;
    QLineEdit *Name2AddEdgeLine;
    QLabel *label_3;
    QLineEdit *WeightAddEdgeLine;
    QHBoxLayout *horizontalLayout_5;
    QPushButton *DelEdgeButton;
    QLabel *label_4;
    QLineEdit *Name1DelEdgeLine;
    QLabel *label_5;
    QLineEdit *Name2DelEdgeLine;
    QGroupBox *groupBox_3;
    QHBoxLayout *horizontalLayout_9;
    QHBoxLayout *horizontalLayout_8;
    QHBoxLayout *horizontalLayout_6;
    QPushButton *DelGraphButton;
    QPushButton *SaveGraphButton;
    QPushButton *LoadGraphButton;
    QLabel *label_6;
    QLineEdit *FileNameLine;
    QHBoxLayout *horizontalLayout_7;
    QGroupBox *groupBox_4;
    QHBoxLayout *horizontalLayout_10;
    QGraphicsView *graphicsView;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(1081, 608);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        verticalLayout_2 = new QVBoxLayout(centralwidget);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        groupBox = new QGroupBox(centralwidget);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        verticalLayout = new QVBoxLayout(groupBox);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        AddNodeButton = new QPushButton(groupBox);
        AddNodeButton->setObjectName(QString::fromUtf8("AddNodeButton"));
        QSizePolicy sizePolicy(QSizePolicy::Minimum, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(AddNodeButton->sizePolicy().hasHeightForWidth());
        AddNodeButton->setSizePolicy(sizePolicy);
        AddNodeButton->setMinimumSize(QSize(200, 0));
        AddNodeButton->setMaximumSize(QSize(16777215, 16777215));
        AddNodeButton->setBaseSize(QSize(0, 0));
        AddNodeButton->setAutoFillBackground(false);
        AddNodeButton->setStyleSheet(QString::fromUtf8("QPushButton\n"
"{\n"
"	background-color: rgb(0, 230, 0);\n"
"}\n"
"\n"
"QPushButton:pressed\n"
"{\n"
"	background-color: rgb(0, 100, 0);\n"
"}"));

        horizontalLayout->addWidget(AddNodeButton);

        label_8 = new QLabel(groupBox);
        label_8->setObjectName(QString::fromUtf8("label_8"));
        label_8->setFrameShape(QFrame::Box);
        label_8->setFrameShadow(QFrame::Sunken);

        horizontalLayout->addWidget(label_8);

        NameAddLine = new QLineEdit(groupBox);
        NameAddLine->setObjectName(QString::fromUtf8("NameAddLine"));
        QSizePolicy sizePolicy1(QSizePolicy::Expanding, QSizePolicy::Minimum);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(NameAddLine->sizePolicy().hasHeightForWidth());
        NameAddLine->setSizePolicy(sizePolicy1);
        NameAddLine->setMinimumSize(QSize(0, 35));

        horizontalLayout->addWidget(NameAddLine);

        label_9 = new QLabel(groupBox);
        label_9->setObjectName(QString::fromUtf8("label_9"));
        label_9->setFrameShape(QFrame::Box);
        label_9->setFrameShadow(QFrame::Sunken);

        horizontalLayout->addWidget(label_9);

        DescriptionAddLine = new QLineEdit(groupBox);
        DescriptionAddLine->setObjectName(QString::fromUtf8("DescriptionAddLine"));
        sizePolicy1.setHeightForWidth(DescriptionAddLine->sizePolicy().hasHeightForWidth());
        DescriptionAddLine->setSizePolicy(sizePolicy1);
        DescriptionAddLine->setMinimumSize(QSize(0, 35));

        horizontalLayout->addWidget(DescriptionAddLine);


        verticalLayout->addLayout(horizontalLayout);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        DelNodeButton = new QPushButton(groupBox);
        DelNodeButton->setObjectName(QString::fromUtf8("DelNodeButton"));
        DelNodeButton->setMinimumSize(QSize(200, 0));
#if QT_CONFIG(tooltip)
        DelNodeButton->setToolTip(QString::fromUtf8("\320\225\321\201\320\273\320\270 \320\262\321\213 \321\205\320\276\321\202\320\270\321\202\320\265 \321\203\320\264\320\260\320\273\320\270\321\202\321\214 \320\275\320\265\321\201\320\272\320\276\320\273\321\214\320\272\320\276, \321\202\320\276 \320\267\320\260\320\277\320\270\321\210\320\270\321\202\320\265 \320\270\321\205 \321\207\320\265\321\200\320\265\320\267 \320\267\320\260\320\277\321\217\321\202\321\203\321\216 \320\261\320\265\320\267 \320\277\321\200\320\276\320\261\320\265\320\273\320\276\320\262"));
#endif // QT_CONFIG(tooltip)
        DelNodeButton->setStyleSheet(QString::fromUtf8("QPushButton\n"
"{\n"
"	background-color: rgb(230, 0, 0);\n"
"}\n"
"\n"
"QPushButton:pressed\n"
"{\n"
"	background-color: rgb(100, 0, 0);\n"
"}"));

        horizontalLayout_2->addWidget(DelNodeButton);

        label_10 = new QLabel(groupBox);
        label_10->setObjectName(QString::fromUtf8("label_10"));
        label_10->setFrameShape(QFrame::Box);
        label_10->setFrameShadow(QFrame::Sunken);

        horizontalLayout_2->addWidget(label_10);

        NameDelLine = new QLineEdit(groupBox);
        NameDelLine->setObjectName(QString::fromUtf8("NameDelLine"));
        sizePolicy1.setHeightForWidth(NameDelLine->sizePolicy().hasHeightForWidth());
        NameDelLine->setSizePolicy(sizePolicy1);
        NameDelLine->setMinimumSize(QSize(0, 35));

        horizontalLayout_2->addWidget(NameDelLine);


        verticalLayout->addLayout(horizontalLayout_2);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        ChangeNodeButton = new QPushButton(groupBox);
        ChangeNodeButton->setObjectName(QString::fromUtf8("ChangeNodeButton"));
        ChangeNodeButton->setMinimumSize(QSize(200, 0));
        ChangeNodeButton->setStyleSheet(QString::fromUtf8("QPushButton\n"
"{\n"
"	background-color: rgb(230, 230, 0);\n"
"}\n"
"\n"
"QPushButton:pressed\n"
"{\n"
"	background-color:rgb(147, 147, 0) ;\n"
"}"));

        horizontalLayout_3->addWidget(ChangeNodeButton);

        label_11 = new QLabel(groupBox);
        label_11->setObjectName(QString::fromUtf8("label_11"));
        label_11->setFrameShape(QFrame::Box);
        label_11->setFrameShadow(QFrame::Sunken);

        horizontalLayout_3->addWidget(label_11);

        OldNameChangeLine = new QLineEdit(groupBox);
        OldNameChangeLine->setObjectName(QString::fromUtf8("OldNameChangeLine"));
        sizePolicy1.setHeightForWidth(OldNameChangeLine->sizePolicy().hasHeightForWidth());
        OldNameChangeLine->setSizePolicy(sizePolicy1);
        OldNameChangeLine->setMinimumSize(QSize(0, 35));

        horizontalLayout_3->addWidget(OldNameChangeLine);

        label_12 = new QLabel(groupBox);
        label_12->setObjectName(QString::fromUtf8("label_12"));
        label_12->setFrameShape(QFrame::Box);
        label_12->setFrameShadow(QFrame::Sunken);

        horizontalLayout_3->addWidget(label_12);

        NewNameChangeLine = new QLineEdit(groupBox);
        NewNameChangeLine->setObjectName(QString::fromUtf8("NewNameChangeLine"));
        sizePolicy1.setHeightForWidth(NewNameChangeLine->sizePolicy().hasHeightForWidth());
        NewNameChangeLine->setSizePolicy(sizePolicy1);

        horizontalLayout_3->addWidget(NewNameChangeLine);

        label_13 = new QLabel(groupBox);
        label_13->setObjectName(QString::fromUtf8("label_13"));
        label_13->setFrameShape(QFrame::Box);
        label_13->setFrameShadow(QFrame::Sunken);

        horizontalLayout_3->addWidget(label_13);

        NewDescriptionChangeLine = new QLineEdit(groupBox);
        NewDescriptionChangeLine->setObjectName(QString::fromUtf8("NewDescriptionChangeLine"));
        sizePolicy1.setHeightForWidth(NewDescriptionChangeLine->sizePolicy().hasHeightForWidth());
        NewDescriptionChangeLine->setSizePolicy(sizePolicy1);

        horizontalLayout_3->addWidget(NewDescriptionChangeLine);


        verticalLayout->addLayout(horizontalLayout_3);


        verticalLayout_2->addWidget(groupBox);

        groupBox_2 = new QGroupBox(centralwidget);
        groupBox_2->setObjectName(QString::fromUtf8("groupBox_2"));
        verticalLayout_4 = new QVBoxLayout(groupBox_2);
        verticalLayout_4->setObjectName(QString::fromUtf8("verticalLayout_4"));
        verticalLayout_3 = new QVBoxLayout();
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));
        AddEdgeButton = new QPushButton(groupBox_2);
        AddEdgeButton->setObjectName(QString::fromUtf8("AddEdgeButton"));
        sizePolicy.setHeightForWidth(AddEdgeButton->sizePolicy().hasHeightForWidth());
        AddEdgeButton->setSizePolicy(sizePolicy);
        AddEdgeButton->setMinimumSize(QSize(320, 0));
        AddEdgeButton->setBaseSize(QSize(400, 0));
        AddEdgeButton->setStyleSheet(QString::fromUtf8("QPushButton\n"
"{\n"
"	background-color: rgb(0, 230, 0);\n"
"}\n"
"\n"
"QPushButton:pressed\n"
"{\n"
"	background-color: rgb(0, 100, 0);\n"
"}"));

        horizontalLayout_4->addWidget(AddEdgeButton);

        label = new QLabel(groupBox_2);
        label->setObjectName(QString::fromUtf8("label"));
        label->setFrameShape(QFrame::Box);
        label->setFrameShadow(QFrame::Sunken);

        horizontalLayout_4->addWidget(label);

        Name1AddEdgeLine = new QLineEdit(groupBox_2);
        Name1AddEdgeLine->setObjectName(QString::fromUtf8("Name1AddEdgeLine"));
        sizePolicy1.setHeightForWidth(Name1AddEdgeLine->sizePolicy().hasHeightForWidth());
        Name1AddEdgeLine->setSizePolicy(sizePolicy1);
        Name1AddEdgeLine->setMinimumSize(QSize(0, 35));

        horizontalLayout_4->addWidget(Name1AddEdgeLine);

        label_2 = new QLabel(groupBox_2);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setFrameShape(QFrame::Box);
        label_2->setFrameShadow(QFrame::Sunken);

        horizontalLayout_4->addWidget(label_2);

        Name2AddEdgeLine = new QLineEdit(groupBox_2);
        Name2AddEdgeLine->setObjectName(QString::fromUtf8("Name2AddEdgeLine"));
        sizePolicy1.setHeightForWidth(Name2AddEdgeLine->sizePolicy().hasHeightForWidth());
        Name2AddEdgeLine->setSizePolicy(sizePolicy1);

        horizontalLayout_4->addWidget(Name2AddEdgeLine);

        label_3 = new QLabel(groupBox_2);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setFrameShape(QFrame::Box);
        label_3->setFrameShadow(QFrame::Sunken);

        horizontalLayout_4->addWidget(label_3);

        WeightAddEdgeLine = new QLineEdit(groupBox_2);
        WeightAddEdgeLine->setObjectName(QString::fromUtf8("WeightAddEdgeLine"));
        sizePolicy1.setHeightForWidth(WeightAddEdgeLine->sizePolicy().hasHeightForWidth());
        WeightAddEdgeLine->setSizePolicy(sizePolicy1);

        horizontalLayout_4->addWidget(WeightAddEdgeLine);


        verticalLayout_3->addLayout(horizontalLayout_4);

        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setObjectName(QString::fromUtf8("horizontalLayout_5"));
        DelEdgeButton = new QPushButton(groupBox_2);
        DelEdgeButton->setObjectName(QString::fromUtf8("DelEdgeButton"));
        DelEdgeButton->setMinimumSize(QSize(320, 0));
        DelEdgeButton->setStyleSheet(QString::fromUtf8("QPushButton\n"
"{\n"
"	background-color: rgb(230, 0, 0);\n"
"}\n"
"\n"
"QPushButton:pressed\n"
"{\n"
"	background-color: rgb(100, 0, 0);\n"
"}"));

        horizontalLayout_5->addWidget(DelEdgeButton);

        label_4 = new QLabel(groupBox_2);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        label_4->setFrameShape(QFrame::Box);
        label_4->setFrameShadow(QFrame::Sunken);

        horizontalLayout_5->addWidget(label_4);

        Name1DelEdgeLine = new QLineEdit(groupBox_2);
        Name1DelEdgeLine->setObjectName(QString::fromUtf8("Name1DelEdgeLine"));
        sizePolicy1.setHeightForWidth(Name1DelEdgeLine->sizePolicy().hasHeightForWidth());
        Name1DelEdgeLine->setSizePolicy(sizePolicy1);
        Name1DelEdgeLine->setMinimumSize(QSize(0, 35));

        horizontalLayout_5->addWidget(Name1DelEdgeLine);

        label_5 = new QLabel(groupBox_2);
        label_5->setObjectName(QString::fromUtf8("label_5"));
        label_5->setFrameShape(QFrame::Box);
        label_5->setFrameShadow(QFrame::Sunken);

        horizontalLayout_5->addWidget(label_5);

        Name2DelEdgeLine = new QLineEdit(groupBox_2);
        Name2DelEdgeLine->setObjectName(QString::fromUtf8("Name2DelEdgeLine"));
        sizePolicy1.setHeightForWidth(Name2DelEdgeLine->sizePolicy().hasHeightForWidth());
        Name2DelEdgeLine->setSizePolicy(sizePolicy1);

        horizontalLayout_5->addWidget(Name2DelEdgeLine);


        verticalLayout_3->addLayout(horizontalLayout_5);


        verticalLayout_4->addLayout(verticalLayout_3);


        verticalLayout_2->addWidget(groupBox_2);

        groupBox_3 = new QGroupBox(centralwidget);
        groupBox_3->setObjectName(QString::fromUtf8("groupBox_3"));
        horizontalLayout_9 = new QHBoxLayout(groupBox_3);
        horizontalLayout_9->setObjectName(QString::fromUtf8("horizontalLayout_9"));
        horizontalLayout_8 = new QHBoxLayout();
        horizontalLayout_8->setObjectName(QString::fromUtf8("horizontalLayout_8"));
        horizontalLayout_6 = new QHBoxLayout();
        horizontalLayout_6->setObjectName(QString::fromUtf8("horizontalLayout_6"));
        DelGraphButton = new QPushButton(groupBox_3);
        DelGraphButton->setObjectName(QString::fromUtf8("DelGraphButton"));
        DelGraphButton->setStyleSheet(QString::fromUtf8("QPushButton\n"
"{\n"
"	background-color: rgb(230, 0, 0);\n"
"}\n"
"\n"
"QPushButton:pressed\n"
"{\n"
"	background-color: rgb(100, 0, 0);\n"
"}"));

        horizontalLayout_6->addWidget(DelGraphButton);

        SaveGraphButton = new QPushButton(groupBox_3);
        SaveGraphButton->setObjectName(QString::fromUtf8("SaveGraphButton"));
        SaveGraphButton->setMinimumSize(QSize(200, 0));
        SaveGraphButton->setStyleSheet(QString::fromUtf8("QPushButton\n"
"{\n"
"	background-color: rgb(0, 230, 0);\n"
"}\n"
"\n"
"QPushButton:pressed\n"
"{\n"
"	background-color: rgb(0, 100, 0);\n"
"}"));

        horizontalLayout_6->addWidget(SaveGraphButton);

        LoadGraphButton = new QPushButton(groupBox_3);
        LoadGraphButton->setObjectName(QString::fromUtf8("LoadGraphButton"));
        LoadGraphButton->setMinimumSize(QSize(200, 0));
        LoadGraphButton->setStyleSheet(QString::fromUtf8("QPushButton\n"
"{\n"
"	background-color: rgb(230, 230, 0);\n"
"}\n"
"\n"
"QPushButton:pressed\n"
"{\n"
"	background-color:rgb(147, 147, 0) ;\n"
"}"));

        horizontalLayout_6->addWidget(LoadGraphButton);

        label_6 = new QLabel(groupBox_3);
        label_6->setObjectName(QString::fromUtf8("label_6"));
        label_6->setFrameShape(QFrame::Box);
        label_6->setFrameShadow(QFrame::Sunken);

        horizontalLayout_6->addWidget(label_6);

        FileNameLine = new QLineEdit(groupBox_3);
        FileNameLine->setObjectName(QString::fromUtf8("FileNameLine"));
        sizePolicy1.setHeightForWidth(FileNameLine->sizePolicy().hasHeightForWidth());
        FileNameLine->setSizePolicy(sizePolicy1);
        FileNameLine->setMinimumSize(QSize(0, 35));

        horizontalLayout_6->addWidget(FileNameLine);


        horizontalLayout_8->addLayout(horizontalLayout_6);

        horizontalLayout_7 = new QHBoxLayout();
        horizontalLayout_7->setObjectName(QString::fromUtf8("horizontalLayout_7"));

        horizontalLayout_8->addLayout(horizontalLayout_7);


        horizontalLayout_9->addLayout(horizontalLayout_8);


        verticalLayout_2->addWidget(groupBox_3);

        groupBox_4 = new QGroupBox(centralwidget);
        groupBox_4->setObjectName(QString::fromUtf8("groupBox_4"));
        horizontalLayout_10 = new QHBoxLayout(groupBox_4);
        horizontalLayout_10->setObjectName(QString::fromUtf8("horizontalLayout_10"));
        graphicsView = new QGraphicsView(groupBox_4);
        graphicsView->setObjectName(QString::fromUtf8("graphicsView"));

        horizontalLayout_10->addWidget(graphicsView);


        verticalLayout_2->addWidget(groupBox_4);

        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 1081, 21));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "\320\222\320\270\320\267\321\203\320\260\320\273\320\270\320\267\320\260\321\206\320\270\321\217 \320\223\321\200\320\260\321\204\320\260", nullptr));
        groupBox->setTitle(QCoreApplication::translate("MainWindow", "\320\240\320\260\320\261\320\276\321\202\320\260 \321\201 \320\243\320\267\320\273\320\260\320\274\320\270 \320\223\321\200\320\260\321\204\320\260", nullptr));
        AddNodeButton->setText(QCoreApplication::translate("MainWindow", "\320\224\320\276\320\261\320\260\320\262\320\270\321\202\321\214 \320\243\320\267\320\265\320\273", nullptr));
        label_8->setText(QCoreApplication::translate("MainWindow", "\320\235\320\260\320\267\320\262\320\260\320\275\320\270\320\265", nullptr));
        label_9->setText(QCoreApplication::translate("MainWindow", "\320\236\320\277\320\270\321\201\320\260\320\275\320\270\320\265", nullptr));
        DescriptionAddLine->setText(QString());
        DelNodeButton->setText(QCoreApplication::translate("MainWindow", "\320\243\320\264\320\260\320\273\320\270\321\202\321\214 \320\243\320\267\320\265\320\273", nullptr));
        label_10->setText(QCoreApplication::translate("MainWindow", "\320\235\320\260\320\267\320\262\320\260\320\275\320\270\320\265", nullptr));
        ChangeNodeButton->setText(QCoreApplication::translate("MainWindow", "\320\230\320\267\320\274\320\265\320\275\320\270\321\202\321\214 \320\235\320\260\320\267\320\262\320\260\320\275\320\270\320\265 \320\270\320\273\320\270 \320\236\320\277\320\270\321\201\320\260\320\275\320\270\320\265 \320\243\320\267\320\273\320\260", nullptr));
        label_11->setText(QCoreApplication::translate("MainWindow", "\320\241\321\202\320\260\321\200\320\276\320\265 \320\235\320\260\320\267\320\262\320\260\320\275\320\270\320\265", nullptr));
        label_12->setText(QCoreApplication::translate("MainWindow", "\320\235\320\276\320\262\320\276\320\265 \320\235\320\260\320\267\320\262\320\260\320\275\320\270\320\265", nullptr));
        label_13->setText(QCoreApplication::translate("MainWindow", "\320\235\320\276\320\262\320\276\320\265 \320\236\320\277\320\270\321\201\320\260\320\275\320\270\320\265", nullptr));
        groupBox_2->setTitle(QCoreApplication::translate("MainWindow", "\320\240\320\260\320\261\320\276\321\202\320\260 \321\201 \320\240\320\265\320\261\321\200\320\260\320\274\320\270 \320\223\321\200\320\260\321\204\320\260", nullptr));
        AddEdgeButton->setText(QCoreApplication::translate("MainWindow", "\320\224\320\276\320\261\320\260\320\262\320\270\321\202\321\214 \320\270\320\273\320\270 \320\230\320\267\320\274\320\265\320\275\320\270\321\202\321\214 \320\240\320\265\320\261\321\200\320\276", nullptr));
        label->setText(QCoreApplication::translate("MainWindow", "\320\235\320\260\320\267\320\262\320\260\320\275\320\270\320\265 \320\243\320\267\320\273\320\260 \320\220", nullptr));
        Name1AddEdgeLine->setText(QString());
        label_2->setText(QCoreApplication::translate("MainWindow", "\320\235\320\260\320\267\320\262\320\260\320\275\320\270\320\265 \320\243\320\267\320\273\320\260 B", nullptr));
        label_3->setText(QCoreApplication::translate("MainWindow", "\320\222\320\265\321\201", nullptr));
        DelEdgeButton->setText(QCoreApplication::translate("MainWindow", "\320\243\320\264\320\260\320\273\320\270\321\202\321\214 \320\240\320\265\320\261\321\200\320\276", nullptr));
        label_4->setText(QCoreApplication::translate("MainWindow", "\320\235\320\260\320\267\320\262\320\260\320\275\320\270\320\265 \320\243\320\267\320\273\320\260 \320\220", nullptr));
        label_5->setText(QCoreApplication::translate("MainWindow", "\320\235\320\260\320\267\320\262\320\260\320\275\320\270\320\265 \320\243\320\267\320\273\320\260 \320\222", nullptr));
        groupBox_3->setTitle(QCoreApplication::translate("MainWindow", "\320\240\320\260\320\261\320\276\321\202\320\260 \321\201 \320\244\320\260\320\271\320\273\320\260\320\274\320\270 \320\270 \320\277\321\200\320\276\321\207\320\265\320\265", nullptr));
        DelGraphButton->setText(QCoreApplication::translate("MainWindow", "\320\236\321\207\320\270\321\201\321\202\320\270\321\202\321\214 \320\223\321\200\320\260\321\204", nullptr));
        SaveGraphButton->setText(QCoreApplication::translate("MainWindow", "\320\241\320\276\321\205\321\200\320\260\320\275\320\270\321\202\321\214", nullptr));
        LoadGraphButton->setText(QCoreApplication::translate("MainWindow", "\320\227\320\260\320\263\321\200\321\203\320\267\320\270\321\202\321\214", nullptr));
        label_6->setText(QCoreApplication::translate("MainWindow", "\320\230\320\274\321\217 \320\244\320\260\320\271\320\273\320\260", nullptr));
        groupBox_4->setTitle(QCoreApplication::translate("MainWindow", "\320\223\321\200\320\260\321\204", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
