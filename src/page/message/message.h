//
// Created by superhuap on 2025/7/27.
//

#ifndef MESSAGE_H
#define MESSAGE_H

#include <QWidget>

class ElaContentDialog;
class ElaText;

QT_BEGIN_NAMESPACE
namespace Ui { class message; }
QT_END_NAMESPACE

class message : public QWidget {
Q_OBJECT

public:
    explicit message(QWidget *parent = nullptr);
    ~message() override;

private slots:
    void onSelectAllButtonClicked();
    void onReLoadDataButtonClicked();
    void onSendButtonClicked();

private:
    Ui::message *ui;
    ElaContentDialog* dialog;
    ElaText* label;
    void configWidgets();
    void loadData();
    void loadMsgData();
    void setupConnections();
    void send(QString msg);
};


#endif //MESSAGE_H
