//
// Created by superhuap on 2025/7/27.
//

#ifndef COMMAND_H
#define COMMAND_H

#include <QWidget>


QT_BEGIN_NAMESPACE
namespace Ui { class command; }
QT_END_NAMESPACE

class command : public QWidget {
Q_OBJECT

public:
    explicit command(QWidget *parent = nullptr);
    ~command() override;

private:
    Ui::command *ui;
    void loadData();
};


#endif //COMMAND_H
