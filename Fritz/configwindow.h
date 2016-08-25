#ifndef CONFIGWINDOW_H
#define CONFIGWINDOW_H

#include <QDialog>

namespace Ui {
class ConfigWindow;
}

class ConfigWindow : public QDialog
{
    Q_OBJECT
public:
    explicit ConfigWindow(QWidget *parent = 0);

signals:

public slots:

private slots:
    void on_btnCancelSave_accepted();

    void on_btnCancelSave_rejected();

private:
    Ui::ConfigWindow *ui;

};

#endif // CONFIGWINDOW_H
