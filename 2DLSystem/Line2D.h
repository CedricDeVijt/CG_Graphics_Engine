#ifndef ENGINE_LINE2D_H
#define ENGINE_LINE2D_H
#include "Point2D.h"
#include "LineColor.h"
#include "list"
#include "../easy_image.h"

class Line2D{
public:
    Line2D() = default;
    Line2D(Point2D pointA, Point2D pointB, LineColor color);
    Line2D(const Point2D &pointA, const Point2D &pointB, const img::Color &colorImg);

    Point2D pointA{};
    Point2D pointB{};
    LineColor color{};
    img::Color colorIMG;

    void scaleLine(const double& factor);

    void moveLine(const double& dx, const double & dy);
};

using Lines2D = std::list<Line2D>;

#endif //ENGINE_LINE2D_H
