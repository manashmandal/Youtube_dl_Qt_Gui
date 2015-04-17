#include "downloadwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    downloadWindow w;
    w.setFixedSize(w.size());
    w.setWindowTitle("Youtube Video Downloader [1.0]");
    w.show();

    return a.exec();
}
