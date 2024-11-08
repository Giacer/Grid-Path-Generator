#include "window.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    Window w;
    w.setFixedSize(800, 550);
    w.show();

    return a.exec();
}
