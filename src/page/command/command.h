//
// Created by superhuap on 2025/7/27.
//

#ifndef COMMAND_H
#define COMMAND_H

#include <QWidget>

class ElaContentDialog;
class ElaText;

QT_BEGIN_NAMESPACE
namespace Ui { class command; }
QT_END_NAMESPACE

class command : public QWidget {
Q_OBJECT

public:
    explicit command(QWidget *parent = nullptr);
    ~command() override;

private slots:
    void onSelectAllButtonClicked();
    void onReLoadDataButtonClicked();
    void onSendButtonClicked();

private:
    Ui::command *ui;
    ElaContentDialog* dialog;
    ElaText* label;
    void loadData();
    void configWidgets();
    void loadCmdData();
    void setupConnections();
    void send(QString cmd);
};


#endif //COMMAND_H
