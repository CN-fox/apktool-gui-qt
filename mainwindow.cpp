#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include <QFileDialog>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setWindowFlags(Qt::Window);
    setWindowTitle("gui-apktool");
    setFixedSize(600,400);

    rb1 = ui->rb1;
    rb2 = ui->rb2;
    apkDir = ui->apkDir;
    outDir = ui->outdir;

    process = new QProcess;
    process->setProcessChannelMode(QProcess::MergedChannels);
    connect(process,SIGNAL(readyRead()),this,SLOT(read()));
    connect(process,SIGNAL(finished(int)),this,SLOT(finished(int)));
}

MainWindow::~MainWindow()
{
    process->close();
    delete process;
    delete ui;
}

void MainWindow::on_apkSelect_clicked()
{
    QString path = QFileDialog::getOpenFileName(this, tr("Open Apk"), ".", tr("Apk Files(*.apk)"));
    qDebug() << path;
    apkDir->setText(path);
    int index =  path.lastIndexOf(".");
    path = path.left(index);
    qDebug() << path;
    outDir->setText(path);
}

void MainWindow::on_outSelect_clicked()
{
    QString path = outDir->text();
    if(QFile(path).exists()){
        path = QFileDialog::getExistingDirectory(this,tr("select dir"),path);
    }else{
        path = QFileDialog::getExistingDirectory(this,tr("select dir"),QDir::homePath());
    }
    outDir->setText(path);
}

void MainWindow::on_run_clicked()
{
    QString cmd = getCmd();
    qDebug() << "exec "+cmd;
    process->start(cmd);
    qDebug() << "Clicked";
}

void MainWindow::read()
{
    char buf[1024];
    do{
        process->readLine(buf,sizeof(buf));
        qDebug() << tr(buf);
    }while(process->canReadLine());
}

void MainWindow::finished(int error)
{
    qDebug() << " error"+ error;
}

QString MainWindow::getCmd()
{
    QString s("java -jar");

    if(rb1->isChecked()){
        s.push_back(" apktool-1.5.2.jar d");
    }else{
        s.push_back(" apktool-2.0.0.jar d");
    }

    if(force){
        s.push_back(" -f");
    }

    if(nr){
        s.push_back(" -r");
    }

    if(ns){
        s.push_back(" -s");
    }

    if(QFile(apkDir->text()).exists()){
        s.push_back(" "+apkDir->text());
        s.push_back(" -o "+outDir->text());
    }else{
        return "";
    }

    return s;
}


