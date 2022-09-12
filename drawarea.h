#ifndef DRAWAREA_H
#define DRAWAREA_H

#include <QWidget>
#include <QPixmap>
#include <QPoint>
#include <QPainter>
#include <QColor>
#include <QMouseEvent>
#include <QLabel>
#include <qdebug.h>

class DrawArea : public QLabel
{
    Q_OBJECT

public:
    explicit DrawArea(QWidget *parent = nullptr);
    void setColor(QColor&);
    void setPenWidth(double);
    void setPixmap(const QPixmap&);
    bool isFilled() {return m_isFilled;}
    void setDrawing(bool state){m_drawingIsOn = state;}

private:
    QPixmap m_drawArea;
    QPoint m_prevPosition;
    QColor m_color;
    qreal m_width;
    bool m_isFilled = false, m_drawingIsOn = false;

    void paintEvent(QPaintEvent *) override;
    void resizeEvent(QResizeEvent *) override;
    void mousePressEvent(QMouseEvent * ev) override;
    void mouseMoveEvent(QMouseEvent * ev) override;
    void draw(const QPoint &);
    void setDrawPen();

};

#endif // DRAWAREA_H
