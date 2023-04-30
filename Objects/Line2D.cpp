#include "Line2D.h"

Line2D::Line2D(const Point2D &pointA, const Point2D &pointB, const img::Color &colorImg) : pointA(pointA),
                                                                                           pointB(pointB),
                                                                                           colorIMG(colorImg) {}

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

