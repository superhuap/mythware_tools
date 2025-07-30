//
// Created by superhuap on 2025/7/27.
//

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QWidget>
#include <ElaWindow.h>


QT_BEGIN_NAMESPACE
namespace Ui { class mainwindow; }
QT_END_NAMESPACE

class mainwindow : public ElaWindow {
Q_OBJECT

public:
    explicit mainwindow(QWidget *parent = nullptr);
    ~mainwindow() override;

private:
    Ui::mainwindow *ui;
    void init();
    QString Setting_key{""};
};


#endif //MAINWINDOW_H
