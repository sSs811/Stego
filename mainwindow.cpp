#include "mainwindow.h"
#include "ui_mainwindow.h"



#include <QImageReader>
#include <QFileDialog>
#include <QMessageBox>
#include <QPixmap>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);


    connect(ui->loadButton, &QPushButton::clicked, this, &MainWindow::loadImage);
    connect(ui->spinBox, QOverload<int>::of(&QSpinBox::valueChanged), this, &MainWindow::displayBit);
    connect(ui->saveButton, &QPushButton::clicked, this, &MainWindow::saveImage);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::loadImage()
{

    QString fileName = QFileDialog::getOpenFileName(this, tr("Open Image"), "", tr("Images (*.bmp *.pgm *.png *.jpg)"));
    if (!fileName.isEmpty()) {
        image.load(fileName);
        ui->spinBox->setEnabled(true);
        ui->saveButton->setEnabled(true);
        displayBit();

        ui->loadLabel->setPixmap(QPixmap::fromImage(image).scaled(ui->loadLabel->size(), Qt::KeepAspectRatio));

    }
}

void MainWindow::extractBit(int bitIndex)
{

    bitImage = QImage(image.size(), QImage::Format_Grayscale8);
    for (int y = 0; y < image.height(); ++y) {
        for (int x = 0; x < image.width(); ++x) {
            QColor color = image.pixelColor(x, y);
            int pixelValue = color.rgba();


            bool bit = (pixelValue >> bitIndex) & 1;
            int newPixelValue = bit ? 255 : 0;


            bitImage.setPixelColor(x, y, QColor(newPixelValue, newPixelValue, newPixelValue));
        }
    }
}

void MainWindow::displayBit()
{
    int bitIndex = ui->spinBox->value();
    extractBit(bitIndex);
    ui->imageLabel->setPixmap(QPixmap::fromImage(bitImage).scaled(ui->imageLabel->size(), Qt::KeepAspectRatio));

}

void MainWindow::saveImage()
{

    QString fileName = QFileDialog::getSaveFileName(this, tr("Save Image"), "", tr("Images (*.bmp *.png)"));
    if (!fileName.isEmpty()) {
        bitImage.save(fileName);
    }
}
