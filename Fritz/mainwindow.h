#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:void on_actionAbout_triggered();


    void on_actionConfig_triggered();

    void on_actionSave_triggered();

    void on_actionQuit_triggered();


    void on_comboBox_activated(const QString &arg1);

private:
    Ui::MainWindow *ui;


};

#endif // MAINWINDOW_H
