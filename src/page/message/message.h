//
// Created by superhuap on 2025/7/27.
//

#ifndef MESSAGE_H
#define MESSAGE_H

#include <QWidget>


QT_BEGIN_NAMESPACE
namespace Ui { class message; }
QT_END_NAMESPACE

class message : public QWidget {
Q_OBJECT

public:
    explicit message(QWidget *parent = nullptr);
    ~message() override;

private:
    Ui::message *ui;
};


#endif //MESSAGE_H
