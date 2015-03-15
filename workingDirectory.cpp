#include <QCoreApplication>
#include <QProcess>
#include <QDebug>


int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    QProcess process;

    QString address = "C:\\Users\\Manash\\Documents\\Command";

    process.setWorkingDirectory(address);
    process.start("cmd.exe", QStringList() << "/cyoutube-dl --help");

    while(process.waitForReadyRead(-1)){
        qDebug() << process.readAll();
    }

    qDebug() << "Finished\n";
    return a.exec();
}
