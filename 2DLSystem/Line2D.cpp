#include "Line2D.h"

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

Line2D::Line2D(Point2D pointA_, Point2D pointB_, LineColor color) {
    this->pointA = pointA_;
    this->pointB = pointB_;
    this->color = color;
}

