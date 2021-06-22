#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    sheet.load("/Users/francischen/Desktop/sheet.png");
    // Help us see if we found the file.
    qDebug() << sheet;
    frames = crop(sheet, frames);
    currentImage = 0;
    ui->label->resize(100,100);
    ui->label->setPixmap(QPixmap::fromImage(frames.at(currentImage)));

    interval = 30;
    timer.setInterval(interval);
    connect( &timer,
             SIGNAL(timeout()),
             this,
             SLOT(showFrame()));
    connect( ui->Start,
             SIGNAL(clicked()),
             &timer,
             SLOT(start()));
    connect( ui->Stop,
             SIGNAL(clicked()),
             &timer,
             SLOT(stop()));
    connect( ui->hSlider,
             SIGNAL(valueChanged(int)),
             this,
             SLOT(sliderShow()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

vector<QImage> MainWindow::crop(QImage image, vector<QImage> frames) {
    QImage copy;
    QSize size = image.size();
    int width = size.width();
    int height = size.height();
    for (int h = 0; h <= height; h += 68) {
        for (int w = 0; w <= width; w += 100) {
            copy = image.copy(w, h, w +100, h +68);
            frames.push_back(copy);
        }
    }
    return frames;
}

void MainWindow::showFrame() {
    currentImage = (currentImage+1)%static_cast<int>(frames.size());
    ui->label->setPixmap(QPixmap::fromImage(frames.at(currentImage)));
}

void MainWindow::sliderShow() {
    int value = ui->hSlider->value();
    interval = static_cast<int>(900 / value);
    timer.start(interval);
}

