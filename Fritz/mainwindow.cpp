#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "configwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{

    ui->setupUi(this);
}

void MainWindow::contextMenuEvent(QContextMenuEvent *event)
 {
    configwindow w;
    w.show();
 }

MainWindow::~MainWindow()
{
    delete ui;
}
