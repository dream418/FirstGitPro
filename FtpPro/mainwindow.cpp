#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QByteArray>
#include <QDebug>
#include <QFile>
#include <QIODevice>

#include <private/qzipwriter_p.h>
#include <private/qzipreader_p.h>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow) {
    ui->setupUi(this);
    connect(ui->btnZip, SIGNAL(clicked()), this, SLOT(zip()));
}

MainWindow::~MainWindow() {
    delete ui;
}
#include <QDebug>

void MainWindow::zip() {
    QString path;
    QZipWriter *writer = new QZipWriter(path + "/test.zip");
    //添加文件夹
    //    writer->addDirectory(path + "/ss");
    //添加文件
    QFile file(path + "/test.txt");
    if (!file.exists()) {
        return;
    }
    file.open(QIODevice::ReadOnly);
    writer->addFile("test.txt", file.readAll());
    file.close();
    writer->close();
}

void MainWindow::unzip() {
    QFile read("E:/1.data");
    read.open(QIODevice::ReadOnly);
    QByteArray data;
    data = read.readAll();
    read.close();
    data = qUncompress(data);
    QFile temp("E:/1.bmp");
    temp.open(QIODevice::WriteOnly);
    temp.write(data);
    temp.close();
}
