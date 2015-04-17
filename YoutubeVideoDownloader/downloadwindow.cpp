#include "downloadwindow.h"
#include "ui_downloadwindow.h"

downloadWindow::downloadWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::downloadWindow)
{
    ui->setupUi(this);
}

downloadWindow::~downloadWindow()
{
    delete ui;
}
