/********************************************************************************
** Form generated from reading UI file 'command.ui'
**
** Created by: Qt User Interface Compiler version 5.15.16
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_COMMAND_H
#define UI_COMMAND_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include "elacombobox.h"
#include "elaplaintextedit.h"
#include "elaprogressbar.h"
#include "elapushbutton.h"
#include "elatext.h"
#include "elatreeview.h"

QT_BEGIN_NAMESPACE

class Ui_command
{
public:
    QHBoxLayout *horizontalLayout;
    QVBoxLayout *verticalLayout;
    ElaPushButton *pushButton_load;
    ElaPushButton *pushButton_selectAll;
    ElaTreeView *treeView;
    QVBoxLayout *verticalLayout_2;
    ElaPlainTextEdit *plainTextEdit_cmd;
    QHBoxLayout *horizontalLayout_2;
    ElaText *label;
    ElaComboBox *comboBox;
    ElaPushButton *pushButton_send;
    ElaProgressBar *progressBar;
    ElaText *progress;
    ElaPlainTextEdit *plainTextEdit_log;

    void setupUi(QWidget *command)
    {
        if (command->objectName().isEmpty())
            command->setObjectName(QString::fromUtf8("command"));
        command->resize(650, 450);
        horizontalLayout = new QHBoxLayout(command);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        pushButton_load = new ElaPushButton(command);
        pushButton_load->setObjectName(QString::fromUtf8("pushButton_load"));

        verticalLayout->addWidget(pushButton_load);

        pushButton_selectAll = new ElaPushButton(command);
        pushButton_selectAll->setObjectName(QString::fromUtf8("pushButton_selectAll"));

        verticalLayout->addWidget(pushButton_selectAll);

        treeView = new ElaTreeView(command);
        // treeView->setObjectName(QString::fromUtf8("treeView"));

        verticalLayout->addWidget(treeView);


        horizontalLayout->addLayout(verticalLayout);

        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        plainTextEdit_cmd = new ElaPlainTextEdit(command);
        // plainTextEdit_cmd->setObjectName(QString::fromUtf8("plainTextEdit_cmd"));
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(plainTextEdit_cmd->sizePolicy().hasHeightForWidth());
        plainTextEdit_cmd->setSizePolicy(sizePolicy);

        verticalLayout_2->addWidget(plainTextEdit_cmd);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        label = new ElaText(command);
        label->setObjectName(QString::fromUtf8("label"));

        horizontalLayout_2->addWidget(label);

        comboBox = new ElaComboBox(command);
        comboBox->setObjectName(QString::fromUtf8("comboBox"));

        horizontalLayout_2->addWidget(comboBox);


        verticalLayout_2->addLayout(horizontalLayout_2);

        pushButton_send = new ElaPushButton(command);
        pushButton_send->setObjectName(QString::fromUtf8("pushButton_send"));

        verticalLayout_2->addWidget(pushButton_send);

        progressBar = new ElaProgressBar(command);
        progressBar->setObjectName(QString::fromUtf8("progressBar"));
        progressBar->setValue(0);
        progressBar->setInvertedAppearance(false);

        verticalLayout_2->addWidget(progressBar);

        progress = new ElaText(command);
        progress->setObjectName(QString::fromUtf8("progress"));
        QSizePolicy sizePolicy1(QSizePolicy::Preferred, QSizePolicy::Maximum);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(progress->sizePolicy().hasHeightForWidth());
        progress->setSizePolicy(sizePolicy1);
        progress->setScaledContents(false);
        progress->setAlignment(Qt::AlignCenter);

        verticalLayout_2->addWidget(progress);

        plainTextEdit_log = new ElaPlainTextEdit(command);
        // plainTextEdit_log->setObjectName(QString::fromUtf8("plainTextEdit_log"));
        plainTextEdit_log->setEnabled(false);

        verticalLayout_2->addWidget(plainTextEdit_log);


        horizontalLayout->addLayout(verticalLayout_2);


        retranslateUi(command);

        QMetaObject::connectSlotsByName(command);
    } // setupUi

    void retranslateUi(QWidget *command)
    {
        command->setWindowTitle(QCoreApplication::translate("command", "command", nullptr));
        pushButton_load->setText(QCoreApplication::translate("command", "\345\212\240\350\275\275", nullptr));
        pushButton_selectAll->setText(QCoreApplication::translate("command", "\345\205\250\351\200\211", nullptr));
        plainTextEdit_cmd->setPlaceholderText(QCoreApplication::translate("command", "\350\276\223\345\205\245\346\203\263\345\217\221\351\200\201\347\232\204\345\221\275\344\273\244", nullptr));
        label->setText(QCoreApplication::translate("command", "\345\277\253\346\215\267\345\221\275\344\273\244", nullptr));
        comboBox->setPlaceholderText(QString());
        pushButton_send->setText(QCoreApplication::translate("command", "\345\217\221\351\200\201", nullptr));
        progress->setText(QCoreApplication::translate("command", "0%", nullptr));
        plainTextEdit_log->setPlaceholderText(QCoreApplication::translate("command", "\346\227\245\345\277\227\346\241\206", nullptr));
    } // retranslateUi

};

namespace Ui {
    class command: public Ui_command {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_COMMAND_H
