#ifndef ENGINE_LINE2D_H
#define ENGINE_LINE2D_H
#include "Point2D.h"
#include "LineColor.h"
#include "list"

class Line2D{
public:
    Line2D() = default;
    Line2D(Point2D pointA, Point2D pointB, LineColor color);

    Point2D pointA{};
    Point2D pointB{};
    LineColor color{};

    void scaleLine(const double& factor);

    void moveLine(const double& dx, const double & dy);
};

using Lines2D = std::list<Line2D>;

#endif //ENGINE_LINE2D_H
