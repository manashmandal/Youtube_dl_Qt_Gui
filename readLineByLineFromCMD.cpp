#include <QCoreApplication>
#include <QProcess>
#include <QDebug>


int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    QProcess process;
    process.start("ping google.com", QProcess::ReadWrite);

    while(process.waitForReadyRead(-1)){
        qDebug() << process.readAll();
    }

    qDebug() << "Finished\n";
    return a.exec();
}
