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
#include <QtWidgets/QComboBox>
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
    QHBoxLayout *horizontalLayout_3;
    QComboBox *COMComboBox;
    QPushButton *COMOPushButton;
    QGroupBox *StatusGroupBox;
    QVBoxLayout *verticalLayout_2;
    QLabel *TiredLabel;
    QLineEdit *TiredLineEdit;
    QLabel *BreathLabel;
    QLineEdit *BreathLineEdit;
    QLabel *HandsStatusLabel;
    QLineEdit *HandsStatusLineEdit;
    QTextBrowser *textBrowser;
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
        horizontalLayout_3 = new QHBoxLayout(COMGroupBox);
        horizontalLayout_3->setSpacing(6);
        horizontalLayout_3->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        COMComboBox = new QComboBox(COMGroupBox);
        COMComboBox->setObjectName(QString::fromUtf8("COMComboBox"));

        horizontalLayout_3->addWidget(COMComboBox);

        COMOPushButton = new QPushButton(COMGroupBox);
        COMOPushButton->setObjectName(QString::fromUtf8("COMOPushButton"));

        horizontalLayout_3->addWidget(COMOPushButton);


        horizontalLayout_2->addWidget(COMGroupBox);

        StatusGroupBox = new QGroupBox(centralWidget);
        StatusGroupBox->setObjectName(QString::fromUtf8("StatusGroupBox"));
        verticalLayout_2 = new QVBoxLayout(StatusGroupBox);
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setContentsMargins(11, 11, 11, 11);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        TiredLabel = new QLabel(StatusGroupBox);
        TiredLabel->setObjectName(QString::fromUtf8("TiredLabel"));

        verticalLayout_2->addWidget(TiredLabel);

        TiredLineEdit = new QLineEdit(StatusGroupBox);
        TiredLineEdit->setObjectName(QString::fromUtf8("TiredLineEdit"));

        verticalLayout_2->addWidget(TiredLineEdit);

        BreathLabel = new QLabel(StatusGroupBox);
        BreathLabel->setObjectName(QString::fromUtf8("BreathLabel"));

        verticalLayout_2->addWidget(BreathLabel);

        BreathLineEdit = new QLineEdit(StatusGroupBox);
        BreathLineEdit->setObjectName(QString::fromUtf8("BreathLineEdit"));
        BreathLineEdit->setReadOnly(true);

        verticalLayout_2->addWidget(BreathLineEdit);

        HandsStatusLabel = new QLabel(StatusGroupBox);
        HandsStatusLabel->setObjectName(QString::fromUtf8("HandsStatusLabel"));

        verticalLayout_2->addWidget(HandsStatusLabel);

        HandsStatusLineEdit = new QLineEdit(StatusGroupBox);
        HandsStatusLineEdit->setObjectName(QString::fromUtf8("HandsStatusLineEdit"));
        HandsStatusLineEdit->setReadOnly(true);

        verticalLayout_2->addWidget(HandsStatusLineEdit);

        textBrowser = new QTextBrowser(StatusGroupBox);
        textBrowser->setObjectName(QString::fromUtf8("textBrowser"));

        verticalLayout_2->addWidget(textBrowser);


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
        StatusGroupBox->setTitle(QApplication::translate("QtAppClass", "Status", nullptr));
        TiredLabel->setText(QApplication::translate("QtAppClass", "\347\226\262\345\212\263\345\272\246", nullptr));
        BreathLabel->setText(QApplication::translate("QtAppClass", "\345\221\274\345\220\270", nullptr));
        HandsStatusLabel->setText(QApplication::translate("QtAppClass", "\345\217\214\346\211\213\346\217\241", nullptr));
        LogoLabel->setText(QApplication::translate("QtAppClass", "\345\220\254\345\277\203(\344\270\212\346\265\267)\346\231\272\350\203\275\347\247\221\346\212\200\346\234\211\351\231\220\345\205\254\345\217\270", nullptr));
    } // retranslateUi

};

namespace Ui {
    class QtAppClass: public Ui_QtAppClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_QTAPP_H
