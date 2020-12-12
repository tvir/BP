#ifndef FIGURE_H
#define FIGURE_H

#include <QPoint>
#include <QRect>
#include <QDebug>

#include "math.h"

#include "representer.h"


class Figure
{
public:
    virtual ~Figure() = 0;
    virtual void draw(Representer* rep) = 0;
    virtual bool contain(QPoint p) = 0;
};


class Circle : public Figure
{
public:
    Circle(QPoint c, unsigned int r, QColor col);
    virtual bool contain(QPoint p);
    virtual void draw(Representer* rep);
private:
    QPoint center;
    unsigned int radius;
    QColor color;
};


class Rectangle : public Figure
{
public:
    Rectangle(QPoint t_l, unsigned int w, unsigned int h, QColor col);
    virtual bool contain(QPoint p);
    virtual void draw(Representer* rep);

private:
    QPoint top_left;
    unsigned int width;
    unsigned int height;
    QColor color;
    QRect rect;
};
#endif // FIGURE_H
