#include "figure.h"

Figure::~Figure()
{
}

Circle::Circle(QPoint c, unsigned int r, QColor col) : center(c), radius(r), color(col) {}

bool Circle::contain(QPoint p)
{
    QPoint l = center - p;
    if (sqrt(l.x()*l.x() + l.y()*l.y()) <= radius)
        return true;
    return false;
}

void Circle::draw(Representer *rep)
{
    rep->setColor(color);
    rep->RepresentCircle(center, radius);
}

Rectangle::Rectangle(QPoint t_l, unsigned int w, unsigned int h, QColor col) : top_left(t_l),
    width(w), height(h), color(col)
{
    rect = QRect(top_left, QSize(int(width), int(height)));
}

bool Rectangle::contain(QPoint p)
{
    if (rect.contains(p))
        return true;
    return false;
}

void Rectangle::draw(Representer *rep)
{
    rep->setColor(color);
    rep->RepresentRectangle(top_left, width, height);
}

