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

private slots:
    void on_btnPair_clicked();
    void on_btnForward_clicked();

private:
    Ui::MainWindow *ui;

    bool IsPaired = false;
};

#endif // MAINWINDOW_H
