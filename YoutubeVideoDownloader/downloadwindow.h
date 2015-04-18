#ifndef DOWNLOADWINDOW_H
#define DOWNLOADWINDOW_H
#include <QProcess>
#include <QWinTaskbarButton>
#include <QWinTaskbarProgress>
#include <QDebug>
#include <QMainWindow>
#include <QShowEvent>
#include <QMessageBox>
#include <QDir>

namespace Ui {
class downloadWindow;
}

class downloadWindow : public QMainWindow
{
    Q_OBJECT

public:
    //Main Download Handler
    QProcess *process;
    QString downloadLink;
    QString previousDownloadLink;
    const QString address = "C:\\Users\\Manash\\Documents\\QCommand";
    QString updatedStatus;
    bool isPaused;

    // Showing Progress on the taskbar
    void createTaskbar();
    QWinTaskbarButton *taskbarButton;
    QWinTaskbarProgress *taskbarProgress;
    void showEvent(QShowEvent *e);


    //Default
    explicit downloadWindow(QWidget *parent = 0);
    ~downloadWindow();


public slots:
    void readyForOutput();
    void analyzeOutput(QString prog);
    void downloadFinished(int);

private:
    void enableDownloadSide();
    void enableStatusSide();
    void startDownload(QString addr);

signals:
    int download_progress();

private slots:
    void on_exitButton_clicked();

    void on_link_textEdited(const QString &arg1);

    void on_downloadButton_clicked();

    void on_stopButton_clicked();

    void on_pauseButton_clicked();

private:
    Ui::downloadWindow *ui;
};

#endif // DOWNLOADWINDOW_H
