#include "youtubedl.h"
#include "ui_youtubedl.h"
#include <QMessageBox>


YoutubeDl::YoutubeDl(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::YoutubeDl)
{
    ui->setupUi(this);
    ui->link->setPlaceholderText("Put Download Link");
    process = new QProcess(this);

    //Use this when are you using debug
    process->setWorkingDirectory(address);

    //Use this when you are using release
    //process->setWorkingDirectory(QDir::currentPath());



    connect(process, SIGNAL(readyReadStandardOutput()), this, SLOT(readyForOutput()));
    connect(this, SIGNAL(download_progress()), ui->downloadProgress, SLOT(setValue(int)));


}

YoutubeDl::~YoutubeDl()
{
    delete ui;
}

void YoutubeDl::on_link_textChanged(const QString &arg1)
{
    downloadLink = arg1;
    qDebug() << downloadLink;
}


void YoutubeDl::on_download_clicked()
{
    if (ui->link->text() == NULL){
        QMessageBox::information(this, "Confused!", "Please put a Youtube Video link in the paste area.");
    }
    else {
        ui->download->setFlat(true);
        ui->download->setEnabled(false);
        ui->link->setEnabled(false);
        process->start("cmd.exe", QStringList() << "/cyoutube-dl " + downloadLink, QProcess::ReadWrite);
        qDebug() << QDir::currentPath();
    }
}



void YoutubeDl::readyForOutput()
{
    updated_status = process->readLine();
    ui->status->setText(updated_status);
    analyzeOutput(updated_status);
}



void YoutubeDl::on_stop_clicked()
{
    ui->status->clear();
    ui->link->clear();
    ui->link->setEnabled(true);
    ui->downloadProgress->setValue(0);
    ui->download->setFlat(false);
    ui->download->setEnabled(true);
    process->kill();
}

void YoutubeDl::analyzeOutput(QString prog)
{
    QString theProgress = "123";
    int perc_index, paren_index;

   float progressInt;

    QString *thatStatus;
    thatStatus = &prog;

    if (thatStatus->contains('%')){
        perc_index = thatStatus->indexOf('%');
        paren_index = thatStatus->indexOf(']');

        QString percentage_progress = "";
        percentage_progress = thatStatus->mid(paren_index + 1, perc_index - paren_index - 1);

        percentage_progress.remove(QChar(' '), Qt::CaseInsensitive);
        //float x = percentage_progress.toFloat();
        progressInt = (int) percentage_progress.toFloat();

        //qDebug() << "x: " << x << "\n";
        qDebug() << "Truncated string is: " << percentage_progress << "\n";
        qDebug() << "String to int conversion: " << progressInt << "\n";


        ui->downloadProgress->setValue(progressInt);
    }
}

void YoutubeDl::on_about_clicked()
{
    QMessageBox::information(this, "About Me", "I am Manash Kumar Mandal\n\nI have little knowledge in C/C++, C#, Java, Python, Arduino, Processing.\n\nInterested in learning A.I., Augmented Reality and Image Processing.\n\nStudying EEE at KUET; 2K12 batch.\n\nCheck out my projects at github.com/manashmndl\n\n And my personal blog http://medialab.electroscholars.com");
}

void YoutubeDl::on_downloadProgress_valueChanged(int value)
{

}
