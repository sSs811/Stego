#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QImage>
#include <QFileDialog>
#include <QLabel>
#include <QComboBox>
#include <QPushButton>
#include <QPainter>
#include <QSpinBox>

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
    void loadImage();
    void displayBit();
    void saveImage();

private:
    Ui::MainWindow *ui;
    QImage image;
    QImage bitImage;
    void extractBit(int bitIndex);
};

#endif // MAINWINDOW_H
