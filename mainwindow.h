#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>
#include <vector>
using namespace std;

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void showFrame();
    void sliderShow();

private:
    Ui::MainWindow *ui;
    QTimer timer;
    QImage sheet;
    vector<QImage> frames;
    int currentImage;
    int interval;
    vector<QImage> crop(QImage image, vector<QImage> frames);
};
#endif // MAINWINDOW_H
