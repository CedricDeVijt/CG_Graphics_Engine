#include "ScaleLines.h"

void ScaleLines::scale2DLines(Lines2D &lines, const std::vector<int> imageSize, const double &x_min, const double &x_max, const double &y_min, const double &y_max) {
    // scale all lines
    double scalingFactor = 0.95 * (imageSize[0] / (x_max-x_min));
    for (Line2D& line : lines){
        line.scaleLine(scalingFactor);
    }

    // move all lines
    double DCx = (scalingFactor * (x_min + x_max)) / 2;
    double DCy = (scalingFactor * (y_min + y_max)) / 2;

    double dx = (imageSize[0] / 2) - DCx;
    double dy = (imageSize[1] / 2) - DCy;

    for (Line2D &line2D : lines){
        line2D.moveLine(dx, dy);
    }
}
