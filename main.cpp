#include <QApplication>
#include "ElaApplication.h"
#include "src/page/mainwindow/mainwindow.h"

int main(int argc, char *argv[]) {
    QApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QApplication::setAttribute(Qt::AA_UseHighDpiPixmaps);
    QApplication a(argc, argv);
    ElaApplication::getInstance() -> init();
    mainwindow w;
    w.show();
    return QApplication::exec();
}