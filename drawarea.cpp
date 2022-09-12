#include "drawarea.h"

DrawArea::DrawArea(QWidget *parent)
    : QLabel(parent), m_prevPosition(0,0),
      m_color(0,0,0), m_width(1.0)
{}

void DrawArea::paintEvent(QPaintEvent *event)
{
    if(m_isFilled && m_drawingIsOn)
    {
        QPainter painter(this);
        painter.drawPixmap(0, 0, m_drawArea);
    }
    else QLabel::paintEvent(event);
}
void DrawArea::resizeEvent(QResizeEvent *event)
{
    m_drawArea = m_drawArea.scaled(event->size());
}

void DrawArea::mousePressEvent(QMouseEvent * event)
{
    m_prevPosition = event->pos();
}

void DrawArea::mouseMoveEvent(QMouseEvent * event)
{
    draw(event->pos());
}



void DrawArea::setPixmap(const QPixmap& pm)
{
      m_isFilled = true;
      m_drawArea = pm.copy();
      QLabel::setPixmap(m_drawArea);
}

void DrawArea::setColor(QColor& col)
{
    if(col.isValid()) m_color = col;
}

void DrawArea::setPenWidth(double wth)
{
    if(wth > 0.0) m_width = wth;
}

void DrawArea::draw(const QPoint & curPosition)
{
    if(m_isFilled && m_drawingIsOn)
    {
        QPainter painter(&m_drawArea);
        painter.setPen({m_color, m_width});
        painter.drawLine(m_prevPosition, curPosition);
        m_prevPosition = curPosition;
        update();
    }
}




