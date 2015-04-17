#include "downloadwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    downloadWindow w;
    w.show();

    return a.exec();
}
