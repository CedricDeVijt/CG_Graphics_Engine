#include <limits>
#include "ImageSize.h"

std::vector<int>
ImageSize::getImageSize(Lines2D lines, int size, double &x_min, double &x_max, double &y_min, double &y_max) {
    x_max = -std::numeric_limits<double>::infinity();
    y_max = -std::numeric_limits<double>::infinity();
    x_min = std::numeric_limits<double>::infinity();
    y_min = std::numeric_limits<double>::infinity();

    for (const Line2D &line: lines) {
        // x_max
        x_max = std::max(line.pointA.x, x_max);
        x_max = std::max(line.pointB.x, x_max);

        // x_min
        x_min = std::min(line.pointA.x, x_min);
        x_min = std::min(line.pointB.x, x_min);

        // y_max
        y_max = std::max(line.pointA.y, y_max);
        y_max = std::max(line.pointB.y, y_max);


        // y_min
        y_min = std::min(line.pointA.y, y_min);
        y_min = std::min(line.pointB.y, y_min);
    }

    // calculate range for x en y
    double range_x = x_max - x_min;
    double range_y = y_max - y_min;

    // calculate max range
    double max_range = std::max(range_x, range_y);

    // calculate size of image
    double image_x = size * (range_x / max_range);
    double image_y = size * (range_y / max_range);

    return {int(image_x), int(image_y)};
}
