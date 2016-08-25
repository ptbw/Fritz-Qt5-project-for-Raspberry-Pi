#ifndef ABOUTBOX_H
#define ABOUTBOX_H

#include <QDialog>

namespace Ui {
class AboutBox;
}

class AboutBox : public QDialog
{
    Q_OBJECT
public:
    explicit AboutBox(QWidget *parent = 0);

signals:

public slots:

private slots:
    void on_btnClose_accepted();

private:
    Ui::AboutBox *ui;

};

#endif // ABOUTBOX_H
