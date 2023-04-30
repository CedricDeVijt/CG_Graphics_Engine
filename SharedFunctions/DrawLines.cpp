#include "DrawLines.h"

void DrawLines::draw2DLines(img::EasyImage &image, const Lines2D& lines) {
    for (const Line2D& line : lines){
        image.draw_line(lround(line.pointA.x), lround(line.pointA.y), lround(line.pointB.x), lround(line.pointB.y), line.colorIMG);
    }
}
