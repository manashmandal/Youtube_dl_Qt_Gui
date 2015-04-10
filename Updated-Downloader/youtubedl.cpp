#include "youtubedl.h"
#include "ui_youtubedl.h"


YoutubeDl::YoutubeDl(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::YoutubeDl)
{
    ui->setupUi(this);
    ui->link->setPlaceholderText("Put Download Link");
    process = new QProcess(this);
    process->setWorkingDirectory(address);
    //process = new QProcess();
    //process.setWorkingDirectory(QDir::currentPath());
    //process.setWorkingDirectory(address);
    connect(process, SIGNAL(readyReadStandardOutput()), this, SLOT(readyForOutput()));

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
    ui->download->setFlat(true);
    ui->link->setEnabled(false);
    process->start("cmd.exe", QStringList() << "/cyoutube-dl " + downloadLink, QProcess::ReadWrite);
    qDebug() << QDir::currentPath();

}

void YoutubeDl::readyForOutput()
{
    ui->status->setText(process->readAllStandardOutput());
}



void YoutubeDl::on_pushButton_clicked()
{
    ui->status->clear();
    ui->link->clear();
    ui->link->setEnabled(true);
    ui->download->setFlat(false);
    process->kill();
}
