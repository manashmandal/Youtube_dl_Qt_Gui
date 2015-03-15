#include <QCoreApplication>
#include <QProcess>
#include <QDebug>


int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    QProcess process;

    QString address = "C:\\Users\\Manash\\Documents\\Command";
    QString downloadLink = "https://www.youtube.com/watch?v=xMq-FyDBeBA";

    process.setWorkingDirectory(address);
    process.start("cmd.exe", QStringList() << "/cyoutube-dl " + downloadLink);

    while(process.waitForReadyRead(-1)){
        qDebug() << process.readAll();
    }

    qDebug() << "Finished\n";
    return a.exec();
}
