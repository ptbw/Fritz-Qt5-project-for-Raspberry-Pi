#include "aboutbox.h"
#include "ui_aboutbox.h"

AboutBox::AboutBox(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AboutBox)
{

    ui->setupUi(this);
}

void AboutBox::on_btnClose_accepted()
{

}
