#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QImage>
#include <QColorDialog>
#include <QFileDialog>
#include <QResizeEvent>
#include <QPainter>
#include <qdebug.h>

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
    void on_setBcgBut_clicked();
    void on_loadBut_clicked();

    void resizeEvent(QResizeEvent*) override;
    void on_setX_valueChanged(int);
    void on_setY_valueChanged(int);
    void on_setR_valueChanged(int);
    void on_setG_valueChanged(int);
    void on_setB_valueChanged(int);

    void on_drawBut_clicked();
    void on_remBut_clicked();

private:
    void resetBcg();
    void showBcg(QSize);

    QImage getImage();
    void setImage(QImage&);

    void updateColor();
    void updateCoordsSets();
    void updatePixel();
    void setupColors();

    Ui::MainWindow *ui;
    QImage * m_image = nullptr;
    bool m_imageIsSet = false;
    QPoint m_coords;
    QColor m_color;
    QPixmap m_backgroundBackup;

};
#endif // MAINWINDOW_H
