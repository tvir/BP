#ifndef RANDOMFIGURECREATOR_H
#define RANDOMFIGURECREATOR_H

#include "figure.h"

enum FigureTypes{
    FT_circle, FT_rect, FT_size
};

class RandomFigureCreator
{
public:
    Figure *createNewFigure(const QPoint& p, const int& s)
    {
        std::srand(std::time(nullptr) + p.x() + p.y() + s);
        int type = std::rand() % FT_size;
        QPoint center =  p;
        int r = std::rand() % 255 + 1;
        int g = std::rand() % 255 + 1;
        int b = std::rand() % 255 + 1;
        QColor color(r, g, b);
        if (type == FT_circle)
        {
            int radius = std::rand() % maxLength + minLength;
            if (radius > maxLength)
                radius = maxLength;
            Circle *c = new Circle(center, radius, color);
            return c;
        }
        if (type == FT_rect)
        {
            int a = std::rand() % maxLength + minLength;
            if (a > maxLength)
                a = maxLength;
            if (a % 2 != 0) a += 1;
            int b = std::rand() % maxLength + minLength;
            if (b > maxLength)
                b = maxLength;
            if (b % 2 != 0) b += 1;
            center += QPoint(-a/2, -b/2);
            Rectangle *rect = new Rectangle(center, a, b, color);
            return rect;
        }
        return nullptr;
    }

    void setMaxLenght(const int& l)
    {
        maxLength = l;
    }

private:
    const int minLength = 10;
    int maxLength = 10;

};

#endif // RANDOMFIGURECREATOR_H
