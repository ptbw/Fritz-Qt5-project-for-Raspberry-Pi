#include "configwindow.h"
#include "ui_configwindow.h"

ConfigWindow::ConfigWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ConfigWindow)
{

    ui->setupUi(this);
}

void ConfigWindow::on_btnCancelSave_accepted()
{

}

void ConfigWindow::on_btnCancelSave_rejected()
{

}
