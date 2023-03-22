//
// Created by Cedric De Vijt on 08/03/2023.
//
#include "Point2D.h"

void Point2D::move_with_offset(const double offset_x, const double offset_y) {
    x += offset_x;
    y += offset_y;
}

