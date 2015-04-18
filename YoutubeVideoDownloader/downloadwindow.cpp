#include "downloadwindow.h"
#include "ui_downloadwindow.h"

downloadWindow::downloadWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::downloadWindow)
{
    ui->setupUi(this);
    process = new QProcess(this);
    ui->pauseButton->setEnabled(false);
    ui->stopButton->setEnabled(false);

    //Use this when are you using debug
    process->setWorkingDirectory(address);
    //Use this when you are using release
    //process->setWorkingDirectory(QDir::currentPath());

    connect(process, SIGNAL(readyReadStandardOutput()), this, SLOT(readyForOutput()));
    connect(this, SIGNAL(download_progress()), ui->downloadProgress, SLOT(setValue(int)));
    createTaskbar();
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
    previousDownloadLink = downloadLink; //Kept a copy for resuming
    //Disabling the buttons and text editors while downloading

    if (ui->link->text() == NULL || !ui->link->text().contains("youtube")){

        QMessageBox::warning(this, "URL Problem", "Please put an appropriate youtube video url!");
       // QMessageBox::information(this, "Confused!", "Please put an appropriate download link");
    }
    else {
        enableStatusSide();
        startDownload(downloadLink);
        //qDebug() << QDir::currentPath();
    }
}

//Download Function
void downloadWindow::startDownload(QString url)
{
    process->start("cmd.exe", QStringList() << "/cyoutube-dl " + url, QProcess::ReadWrite);
}


void downloadWindow::readyForOutput()
{
    updatedStatus = process->readLine();
    ui->status->setText(updatedStatus);
    analyzeOutput(updatedStatus);
}

//Analyzing output for progress and ETA
void downloadWindow::analyzeOutput(QString prog)
{
   int perc_index, paren_index;
   int progressInt;

   QString *thatStatus;
   thatStatus = &prog;

    if (thatStatus->contains('%')){
        perc_index = thatStatus->indexOf('%');
        paren_index = thatStatus->indexOf(']');

        progressInt = (int) thatStatus->mid(paren_index + 1, perc_index - paren_index - 1).remove(QChar(' ')).toFloat();

        qDebug() << "String to int conversion: " << progressInt << "\n";

        ui->downloadProgress->setValue(progressInt);
    }
}

//Creating Taskbar
void downloadWindow::createTaskbar()
{
    taskbarButton = new QWinTaskbarButton(this);
    taskbarButton->setWindow(windowHandle());
    taskbarProgress = taskbarButton->progress();
    taskbarProgress->show();
    connect(ui->downloadProgress, SIGNAL(valueChanged(int)), taskbarProgress, SLOT(setValue(int)));

}

//Taskbar Progress Function
void downloadWindow::showEvent(QShowEvent *e)
{
#ifdef Q_OS_WIN32
    taskbarButton->setWindow(windowHandle());
#endif
    e->accept();
}


void downloadWindow::enableDownloadSide()
{
    ui->link->setEnabled(true);
    ui->downloadButton->setEnabled(true);
    ui->status->clear();
    ui->pauseButton->setEnabled(false);
    ui->stopButton->setEnabled(false);
}

void downloadWindow::enableStatusSide()
{
    ui->link->setEnabled(false);
    ui->downloadButton->setEnabled(false);
    ui->status->clear();
    ui->pauseButton->setEnabled(true);
    ui->stopButton->setEnabled(true);
}

void downloadWindow::downloadFinished()
{
    enableDownloadSide();

}

void downloadWindow::on_stopButton_clicked()
{
    ui->downloadProgress->setValue(0);
    taskbarProgress->setValue(0);
    ui->link->clear();
    process->kill();
    enableDownloadSide();
}

void downloadWindow::on_pauseButton_clicked()
{
    isPaused = !isPaused;
    if (isPaused)
    {
        ui->pauseButton->setText("Resume");
        process->kill();
        taskbarProgress->pause();
    }

    else {
        ui->pauseButton->setText("Pause");
        startDownload(previousDownloadLink);
        taskbarProgress->resume();
    }

}
