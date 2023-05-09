#ifndef ENGINE_LINE2D_H
#define ENGINE_LINE2D_H

#include "Point2D.h"
#include "list"
#include "../BaseFiles/easy_image.h"

class Line2D {
public:
    Line2D(const Point2D &pointA, const Point2D &pointB, const img::Color &lineColor);

    Line2D(const Point2D &pointA, const Point2D &pointB, double z1, double z2, const img::Color &color);

    void scaleLine(const double &factor);

    void moveLine(const double &dx, const double &dy);

public:
    Point2D pointA;
    Point2D pointB;

    // Z-Buffer z coordinates
    double z1;
    double z2;

    img::Color color;
};

using Lines2D = std::list<Line2D>;

#endif //ENGINE_LINE2D_H
