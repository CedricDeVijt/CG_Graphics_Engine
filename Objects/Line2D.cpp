#include "Line2D.h"

Line2D::Line2D(const Point2D &pointA, const Point2D &pointB, const img::Color &lineColor) :
pointA(pointA), pointB(pointB), color(lineColor) {}

Line2D::Line2D(const Point2D &pointA, const Point2D &pointB, double z1, double z2, const img::Color &color) :
        pointA(pointA), pointB(pointB), z1(z1), z2(zB), color(color) {}

void Line2D::scaleLine(const double &factor){
    pointA.x *= factor;
    pointA.y *= factor;
    pointB.x *= factor;
    pointB.y *= factor;
}

void Line2D::moveLine(const double &dx, const double &dy) {
    pointA.x += dx;
    pointA.y += dy;
    pointB.x += dx;
    pointB.y += dy;
}

