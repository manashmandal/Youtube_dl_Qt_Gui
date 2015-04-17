#include "downloadwindow.h"
#include "ui_downloadwindow.h"

downloadWindow::downloadWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::downloadWindow)
{
    ui->setupUi(this);
    process = new QProcess(this);
    //Use this when are you using debug
    process->setWorkingDirectory(address);
    //Use this when you are using release
    //process->setWorkingDirectory(QDir::currentPath());

    //connect(process, SIGNAL(readyReadStandardOutput()), this, SLOT(readyForOutput()));
    //connect(this, SIGNAL(download_progress()), ui->downloadProgress, SLOT(setValue(int)));
    //createTaskbar();
}

downloadWindow::~downloadWindow()
{
    delete ui;
}

void downloadWindow::on_exitButton_clicked()
{
    this->close();
}

void downloadWindow::on_link_textEdited(const QString &arg1)
{
    downloadLink = arg1;
    qDebug() << downloadLink;
}

void downloadWindow::on_downloadButton_clicked()
{
    previousDownloadLink = downloadLink;

}

void downloadWindow::readyForOutput()
{
    updatedStatus = process->readLine();
    ui->status->setText(updatedStatus);
    analyzeOutput(updatedStatus);
}

void downloadWindow::analyzeOutput(QString prog)
{
    QString theProgress = "123";
   int perc_index, paren_index;
   int progressInt;

   QString *thatStatus;
   thatStatus = &prog;

    if (thatStatus->contains('%')){
        perc_index = thatStatus->indexOf('%');
        paren_index = thatStatus->indexOf(']');

        QString percentage_progress = "";

        progressInt = (int) thatStatus->mid(paren_index + 1, perc_index - paren_index - 1).remove(QChar(''), Qt::CaseInsensitive).toFloat();


        //qDebug() << "x: " << x << "\n";
        qDebug() << "Truncated string is: " << percentage_progress << "\n";
        qDebug() << "String to int conversion: " << progressInt << "\n";


        ui->downloadProgress->setValue(progressInt);
    }
}
