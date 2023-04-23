#include "DrawLines.h"

void DrawLines::draw2DLines(img::EasyImage &image, Lines2D lines) {
    for (Line2D line : lines){
        image.draw_line(lround(line.pointA.x), lround(line.pointA.y), lround(line.pointB.x), lround(line.pointB.y), line.colorIMG);
//        std::cout << "A:"<< line.pointA.x << ", " << line.pointA.y << "       B:"<< line.pointB.x << ", " << line.pointB.y << std::endl;
    }
}
