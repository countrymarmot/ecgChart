/********************************************************************************
** Form generated from reading UI file 'QtApp.ui'
**
** Created by: Qt User Interface Compiler version 5.12.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_QTAPP_H
#define UI_QTAPP_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTextBrowser>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_QtAppClass
{
public:
    QWidget *centralWidget;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout_2;
    QGroupBox *COMGroupBox;
    QVBoxLayout *verticalLayout_2;
    QComboBox *COMComboBox;
    QPushButton *COMOPushButton;
    QCheckBox *checkBoxBoth;
    QCheckBox *checkBoxLeft;
    QCheckBox *checkBoxRight;
    QGroupBox *StatusGroupBox;
    QGridLayout *gridLayout;
    QLabel *TiredLabel;
    QTextBrowser *textBrowser;
    QLineEdit *TiredLineEdit;
    QLabel *BreathLabel;
    QLineEdit *BreathLineEdit;
    QLabel *HandsStatusLabel;
    QLineEdit *HRStatusLineEdit;
    QLabel *LogoLabel;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *QtAppClass)
    {
        if (QtAppClass->objectName().isEmpty())
            QtAppClass->setObjectName(QString::fromUtf8("QtAppClass"));
        QtAppClass->resize(906, 659);
        centralWidget = new QWidget(QtAppClass);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        verticalLayout = new QVBoxLayout(centralWidget);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        COMGroupBox = new QGroupBox(centralWidget);
        COMGroupBox->setObjectName(QString::fromUtf8("COMGroupBox"));
        verticalLayout_2 = new QVBoxLayout(COMGroupBox);
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setContentsMargins(11, 11, 11, 11);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        COMComboBox = new QComboBox(COMGroupBox);
        COMComboBox->setObjectName(QString::fromUtf8("COMComboBox"));

        verticalLayout_2->addWidget(COMComboBox);

        COMOPushButton = new QPushButton(COMGroupBox);
        COMOPushButton->setObjectName(QString::fromUtf8("COMOPushButton"));

        verticalLayout_2->addWidget(COMOPushButton);

        checkBoxBoth = new QCheckBox(COMGroupBox);
        checkBoxBoth->setObjectName(QString::fromUtf8("checkBoxBoth"));

        verticalLayout_2->addWidget(checkBoxBoth);

        checkBoxLeft = new QCheckBox(COMGroupBox);
        checkBoxLeft->setObjectName(QString::fromUtf8("checkBoxLeft"));

        verticalLayout_2->addWidget(checkBoxLeft);

        checkBoxRight = new QCheckBox(COMGroupBox);
        checkBoxRight->setObjectName(QString::fromUtf8("checkBoxRight"));

        verticalLayout_2->addWidget(checkBoxRight);


        horizontalLayout_2->addWidget(COMGroupBox);

        StatusGroupBox = new QGroupBox(centralWidget);
        StatusGroupBox->setObjectName(QString::fromUtf8("StatusGroupBox"));
        gridLayout = new QGridLayout(StatusGroupBox);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        TiredLabel = new QLabel(StatusGroupBox);
        TiredLabel->setObjectName(QString::fromUtf8("TiredLabel"));

        gridLayout->addWidget(TiredLabel, 0, 0, 1, 1);

        textBrowser = new QTextBrowser(StatusGroupBox);
        textBrowser->setObjectName(QString::fromUtf8("textBrowser"));

        gridLayout->addWidget(textBrowser, 0, 1, 6, 1);

        TiredLineEdit = new QLineEdit(StatusGroupBox);
        TiredLineEdit->setObjectName(QString::fromUtf8("TiredLineEdit"));

        gridLayout->addWidget(TiredLineEdit, 1, 0, 1, 1);

        BreathLabel = new QLabel(StatusGroupBox);
        BreathLabel->setObjectName(QString::fromUtf8("BreathLabel"));

        gridLayout->addWidget(BreathLabel, 2, 0, 1, 1);

        BreathLineEdit = new QLineEdit(StatusGroupBox);
        BreathLineEdit->setObjectName(QString::fromUtf8("BreathLineEdit"));
        BreathLineEdit->setReadOnly(true);

        gridLayout->addWidget(BreathLineEdit, 3, 0, 1, 1);

        HandsStatusLabel = new QLabel(StatusGroupBox);
        HandsStatusLabel->setObjectName(QString::fromUtf8("HandsStatusLabel"));

        gridLayout->addWidget(HandsStatusLabel, 4, 0, 1, 1);

        HRStatusLineEdit = new QLineEdit(StatusGroupBox);
        HRStatusLineEdit->setObjectName(QString::fromUtf8("HRStatusLineEdit"));
        HRStatusLineEdit->setReadOnly(true);

        gridLayout->addWidget(HRStatusLineEdit, 5, 0, 1, 1);


        horizontalLayout_2->addWidget(StatusGroupBox);


        verticalLayout->addLayout(horizontalLayout_2);

        LogoLabel = new QLabel(centralWidget);
        LogoLabel->setObjectName(QString::fromUtf8("LogoLabel"));
        LogoLabel->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        verticalLayout->addWidget(LogoLabel);

        QtAppClass->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(QtAppClass);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 906, 26));
        QtAppClass->setMenuBar(menuBar);
        mainToolBar = new QToolBar(QtAppClass);
        mainToolBar->setObjectName(QString::fromUtf8("mainToolBar"));
        QtAppClass->addToolBar(Qt::BottomToolBarArea, mainToolBar);
        statusBar = new QStatusBar(QtAppClass);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        QtAppClass->setStatusBar(statusBar);

        retranslateUi(QtAppClass);

        QMetaObject::connectSlotsByName(QtAppClass);
    } // setupUi

    void retranslateUi(QMainWindow *QtAppClass)
    {
        QtAppClass->setWindowTitle(QApplication::translate("QtAppClass", "Demo", nullptr));
        COMGroupBox->setTitle(QApplication::translate("QtAppClass", "COM", nullptr));
        COMOPushButton->setText(QApplication::translate("QtAppClass", "start", nullptr));
        checkBoxBoth->setText(QApplication::translate("QtAppClass", "\345\217\214\346\211\213", nullptr));
        checkBoxLeft->setText(QApplication::translate("QtAppClass", "\345\267\246\346\211\213", nullptr));
        checkBoxRight->setText(QApplication::translate("QtAppClass", "\345\217\263\346\211\213", nullptr));
        StatusGroupBox->setTitle(QApplication::translate("QtAppClass", "Status", nullptr));
        TiredLabel->setText(QApplication::translate("QtAppClass", "\347\226\262\345\212\263\345\272\246", nullptr));
        BreathLabel->setText(QApplication::translate("QtAppClass", "\345\221\274\345\220\270", nullptr));
        HandsStatusLabel->setText(QApplication::translate("QtAppClass", "\345\277\203\347\216\207", nullptr));
        LogoLabel->setText(QApplication::translate("QtAppClass", "\345\220\254\345\277\203(\344\270\212\346\265\267)\346\231\272\350\203\275\347\247\221\346\212\200\346\234\211\351\231\220\345\205\254\345\217\270", nullptr));
    } // retranslateUi

};

namespace Ui {
    class QtAppClass: public Ui_QtAppClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_QTAPP_H
