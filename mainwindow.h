#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QProcess>
#include <QRadioButton>
#include <QLineEdit>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

private:



public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_apkSelect_clicked();
    void on_run_clicked();
    void read();
    void finished(int);

    void on_outSelect_clicked();

private:
    Ui::MainWindow *ui;
    bool force = true;
    bool ns = false;
    bool nr = false;
    QRadioButton *rb1;
    QRadioButton *rb2;
    QProcess * process;
    QString getCmd();
    QLineEdit *apkDir;
    QLineEdit *outDir;
};

#endif // MAINWINDOW_H
