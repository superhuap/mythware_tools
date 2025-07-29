/********************************************************************************
** Form generated from reading UI file 'message.ui'
**
** Created by: Qt User Interface Compiler version 5.15.16
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MESSAGE_H
#define UI_MESSAGE_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include <elapushbutton.h>
#include "elacombobox.h"
#include "elaplaintextedit.h"
#include "elaprogressbar.h"
#include "elaspinbox.h"
#include "elatext.h"
#include "elatreeview.h"

QT_BEGIN_NAMESPACE

class Ui_message
{
public:
    QHBoxLayout *horizontalLayout_3;
    QVBoxLayout *verticalLayout;
    ElaPushButton *pushButton_load;
    ElaPushButton *pushButton_selectAll;
    ElaTreeView *treeView;
    QVBoxLayout *verticalLayout_2;
    ElaPlainTextEdit *plainTextEdit_msg;
    QHBoxLayout *horizontalLayout;
    ElaText *label_2;
    ElaSpinBox *spinBox;
    QHBoxLayout *horizontalLayout_4;
    ElaText *label;
    ElaComboBox *comboBox;
    QSpacerItem *verticalSpacer;
    ElaPushButton *pushButton_send;
    QSpacerItem *verticalSpacer_3;
    QHBoxLayout *horizontalLayout_2;
    ElaProgressBar *progressBar;
    ElaText *progress;
    QSpacerItem *verticalSpacer_5;

    void setupUi(QWidget *message)
    {
        if (message->objectName().isEmpty())
            message->setObjectName(QString::fromUtf8("message"));
        message->resize(650, 450);
        horizontalLayout_3 = new QHBoxLayout(message);
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        pushButton_load = new ElaPushButton(message);
        pushButton_load->setObjectName(QString::fromUtf8("pushButton_load"));

        verticalLayout->addWidget(pushButton_load);

        pushButton_selectAll = new ElaPushButton(message);
        pushButton_selectAll->setObjectName(QString::fromUtf8("pushButton_selectAll"));
        pushButton_selectAll->setCheckable(false);
        pushButton_selectAll->setChecked(false);

        verticalLayout->addWidget(pushButton_selectAll);

        treeView = new ElaTreeView(message);

        verticalLayout->addWidget(treeView);


        horizontalLayout_3->addLayout(verticalLayout);

        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        plainTextEdit_msg = new ElaPlainTextEdit(message);
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(plainTextEdit_msg->sizePolicy().hasHeightForWidth());
        plainTextEdit_msg->setSizePolicy(sizePolicy);

        verticalLayout_2->addWidget(plainTextEdit_msg);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        label_2 = new ElaText(message);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        QSizePolicy sizePolicy1(QSizePolicy::Preferred, QSizePolicy::Expanding);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(label_2->sizePolicy().hasHeightForWidth());
        label_2->setSizePolicy(sizePolicy1);

        horizontalLayout->addWidget(label_2);

        spinBox = new ElaSpinBox(message);
        spinBox->setObjectName(QString::fromUtf8("spinBox"));
        QSizePolicy sizePolicy2(QSizePolicy::Minimum, QSizePolicy::Expanding);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(spinBox->sizePolicy().hasHeightForWidth());
        spinBox->setSizePolicy(sizePolicy2);
        spinBox->setMinimum(1);
        spinBox->setMaximum(99999);

        horizontalLayout->addWidget(spinBox);


        verticalLayout_2->addLayout(horizontalLayout);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));
        label = new ElaText(message);
        label->setObjectName(QString::fromUtf8("label"));
        sizePolicy1.setHeightForWidth(label->sizePolicy().hasHeightForWidth());
        label->setSizePolicy(sizePolicy1);

        horizontalLayout_4->addWidget(label);

        comboBox = new ElaComboBox(message);
        comboBox->setObjectName(QString::fromUtf8("comboBox"));
        sizePolicy1.setHeightForWidth(comboBox->sizePolicy().hasHeightForWidth());
        comboBox->setSizePolicy(sizePolicy1);

        horizontalLayout_4->addWidget(comboBox);


        verticalLayout_2->addLayout(horizontalLayout_4);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_2->addItem(verticalSpacer);

        pushButton_send = new ElaPushButton(message);
        pushButton_send->setObjectName(QString::fromUtf8("pushButton_send"));
        QSizePolicy sizePolicy3(QSizePolicy::Minimum, QSizePolicy::Preferred);
        sizePolicy3.setHorizontalStretch(0);
        sizePolicy3.setVerticalStretch(0);
        sizePolicy3.setHeightForWidth(pushButton_send->sizePolicy().hasHeightForWidth());
        pushButton_send->setSizePolicy(sizePolicy3);

        verticalLayout_2->addWidget(pushButton_send);

        verticalSpacer_3 = new QSpacerItem(20, 80, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_2->addItem(verticalSpacer_3);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        progressBar = new ElaProgressBar(message);
        progressBar->setObjectName(QString::fromUtf8("progressBar"));
        sizePolicy.setHeightForWidth(progressBar->sizePolicy().hasHeightForWidth());
        progressBar->setSizePolicy(sizePolicy);
        progressBar->setValue(0);
        progressBar->setInvertedAppearance(false);

        horizontalLayout_2->addWidget(progressBar);

        progress = new ElaText(message);
        progress->setObjectName(QString::fromUtf8("progress"));
        sizePolicy1.setHeightForWidth(progress->sizePolicy().hasHeightForWidth());
        progress->setSizePolicy(sizePolicy1);
        progress->setScaledContents(false);
        progress->setAlignment(Qt::AlignCenter);

        horizontalLayout_2->addWidget(progress);


        verticalLayout_2->addLayout(horizontalLayout_2);

        verticalSpacer_5 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_2->addItem(verticalSpacer_5);


        horizontalLayout_3->addLayout(verticalLayout_2);


        retranslateUi(message);

        QMetaObject::connectSlotsByName(message);
    } // setupUi

    void retranslateUi(QWidget *message)
    {
        message->setWindowTitle(QCoreApplication::translate("message", "message", nullptr));
        pushButton_load->setText(QCoreApplication::translate("message", "\345\212\240\350\275\275", nullptr));
        pushButton_selectAll->setText(QCoreApplication::translate("message", "\345\205\250\351\200\211", nullptr));
        plainTextEdit_msg->setPlaceholderText(QCoreApplication::translate("message", "\350\276\223\345\205\245\346\203\263\345\217\221\351\200\201\347\232\204\346\266\210\346\201\257", nullptr));
        label_2->setText(QCoreApplication::translate("message", "\345\217\221\351\200\201\346\254\241\346\225\260", nullptr));
        label->setText(QCoreApplication::translate("message", "\345\277\253\346\215\267\346\266\210\346\201\257", nullptr));
        comboBox->setPlaceholderText(QString());
        pushButton_send->setText(QCoreApplication::translate("message", "\345\217\221\351\200\201", nullptr));
        progress->setText(QCoreApplication::translate("message", "0%", nullptr));
    } // retranslateUi

};

namespace Ui {
    class message: public Ui_message {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MESSAGE_H
