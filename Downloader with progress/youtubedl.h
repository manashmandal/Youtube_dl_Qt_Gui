#ifndef YOUTUBEDL_H
#define YOUTUBEDL_H

#include <QtCore>
#include <QtGui>
#include <QLineEdit>


#include <QDialog>

namespace Ui {
class YoutubeDl;
}

class YoutubeDl : public QDialog
{
    Q_OBJECT

public:

    QProcess *process;

    QString downloadLink;
    QString address = "C:\\Users\\Manash\\Documents\\QCommand";
    //QString address = QDir::currentPath();
    explicit YoutubeDl(QWidget *parent = 0);
    ~YoutubeDl();

    QString updated_status;

signals:
    int download_progress();

public slots:
    void readyForOutput();
    void analyzeOutput(QString prog);


private slots:
    void on_link_textChanged(const QString &arg1);

    void on_download_clicked();

    void on_stop_clicked();

    void on_about_clicked();



    void on_downloadProgress_valueChanged(int value);

private:
    Ui::YoutubeDl *ui;
};

#endif // YOUTUBEDL_H
