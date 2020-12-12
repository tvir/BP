#ifndef REPRESENTER_H
#define REPRESENTER_H

#include <QWidget>
#include <QPainter>

class Representer {

public:
    Representer(QWidget* widget) : painter(widget)
    {
        painter.setPen(QPen(Qt::black, 1, Qt::SolidLine, Qt::FlatCap));
        painter.setRenderHint(QPainter::Antialiasing);
    }

    void setColor(const QColor& color)
    {
        painter.setBrush(QBrush(color, Qt::SolidPattern));
    }

    void RepresentCircle(const QPoint& center, unsigned int radius) {
        painter.drawEllipse(center.x() - radius, center.y() - radius, 2*radius, 2*radius);
    }

    void RepresentRectangle(const QPoint &left_top,
                       unsigned int width, unsigned int height) {
        painter.drawRect(left_top.x(), left_top.y(),
                         width, height);
    }

private:
    QPainter painter;
};

#endif // REPRESENTER_H
