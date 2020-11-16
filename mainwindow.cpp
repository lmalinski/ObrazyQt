#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent),
      ui(new Ui::MainWindow),
      m_coords(0,0),
      m_color(0,0,0)
{
    ui->setupUi(this);
    ui->image->setScaledContents(true);
    ui->image->setSizePolicy(QSizePolicy::Ignored,QSizePolicy::Ignored);

    QSize dims(this->size());
    QResizeEvent *event = new QResizeEvent(dims,dims);
    QApplication::postEvent(this,event);
}

void MainWindow::resizeEvent(QResizeEvent * event)
{
    updateCoordsSets();
    QMainWindow::resizeEvent(event);
}

MainWindow::~MainWindow()
{
    resetBcg();
    delete ui;
}

void MainWindow::resetBcg()
{
    delete[] m_image;
    m_image = nullptr;

}

void MainWindow::showBcg(QSize dims)
{
    if(m_image != nullptr)
    {
        QImage img = m_image->scaled(dims);
        ui->image->setPixmap(QPixmap::fromImage(img));
        m_color = QColor(img.pixelColor(m_coords));
        m_imageIsSet = true;
        updateColor();
    }
}

void MainWindow::on_setBcgBut_clicked()
{
    if(m_image != nullptr) resetBcg();
    QSize dims = ui->image->size();
    m_image = new QImage(dims,QImage::Format_RGB32);
    QColor color = QColorDialog::getColor();
    if(color.isValid())
    {
        m_image->fill(color);
        showBcg(dims);
    }
}

void MainWindow::on_loadBut_clicked()
{
    if(m_image != nullptr) resetBcg();
    QString fileName = QFileDialog::getOpenFileName(this,"Open Image File","","Images (*.png *.bmp *.jpg)");
    if(!fileName.isEmpty())
    {
        m_image = new QImage(fileName);
        QSize dims = ui->image->size();
        showBcg(dims);
    }
}

QImage MainWindow::getImage()
{
    const QPixmap *map = ui->image->pixmap();
    return map->toImage();
}
void MainWindow::setImage(QImage& img)
{
    ui->image->setPixmap(QPixmap::fromImage(img));
}

void MainWindow::on_setX_valueChanged(int x)
{
    m_coords.setX(x);
    updateColor();
}

void MainWindow::on_setY_valueChanged(int y)
{
    m_coords.setY(y);
    updateColor();
}

void MainWindow::on_setR_valueChanged(int red)
{
    m_color.setRed(red);
    updatePixel();
}

void MainWindow::on_setG_valueChanged(int green)
{
    m_color.setGreen(green);
    updatePixel();
}

void MainWindow::on_setB_valueChanged(int blue)
{
    m_color.setBlue(blue);
    updatePixel();
}

void MainWindow::updateColor()
{
    if(m_imageIsSet)
    {
        QImage img = getImage();
        QColor color = img.pixelColor(m_coords);
        ui->setR->setValue(color.red());
        ui->setG->setValue(color.green());
        ui->setB->setValue(color.blue());
    }
}

void MainWindow::updateCoordsSets()
{
    QSize dims = ui->image->size();
    ui->setX->setMaximum(dims.width());
    ui->setY->setMaximum(dims.height());
}

void MainWindow::updatePixel()
{
    if(m_imageIsSet)
    {
        QImage img = getImage();
        img.setPixelColor(m_coords,m_color);
        setImage(img);
    }
}
