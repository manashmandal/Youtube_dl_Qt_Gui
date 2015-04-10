#include "youtubedl.h"
#include <QApplication>
#include <QProcess>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    YoutubeDl w;
    w.setFixedSize(w.size());
    w.setWindowTitle("Youtube Video Downloader");
    w.show();

    return a.exec();
}
