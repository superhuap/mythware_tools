#include <QApplication>
#include "ElaApplication.h"
#include "src/page/mainwindow/mainwindow.h"

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);
    ElaApplication::getInstance() -> init();
    mainwindow w;
    w.show();
    return QApplication::exec();
}