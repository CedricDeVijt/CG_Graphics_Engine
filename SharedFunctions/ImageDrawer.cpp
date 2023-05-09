#include <sstream>
#include "ImageDrawer.h"

void ImageDrawer::draw2DLines(img::EasyImage &image, const Lines2D &lines) {
    for (const Line2D &line: lines) {
        image.draw_line(lround(line.pointA.x), lround(line.pointA.y), lround(line.pointB.x), lround(line.pointB.y),
                        line.color);
    }
}

void ImageDrawer::drawZBuffer2DLines(img::EasyImage &image, const Lines2D &lines) {
    ZBuffer zBuffer(image.get_width(), image.get_height());

    for (const Line2D &line: lines) {
        draw_zbuf_line(zBuffer, image, lround(line.pointA.x), lround(line.pointA.y), lround(line.z1),
                       lround(line.pointB.x), lround(line.pointB.y), lround(line.z1), line.color);
    }

}

void ImageDrawer::draw_zbuf_line(ZBuffer &zbuffer, img::EasyImage &image, unsigned int x0, unsigned int y0,
                                 unsigned int z0, unsigned int x1, unsigned int y1,
                                 unsigned int z1, img::Color color) {
    // Check if the line is within the boundaries of the image
    if (x0 >= image.get_width() || y0 >= image.get_height() || x1 >= image.get_width() || y1 > image.get_height()) {
        std::stringstream ss;
        ss << "Drawing line from (" << x0 << "," << y0 << ") to (" << x1 << "," << y1 << ") in image of width "
           << image.get_width() << " and height " << image.get_height();
        throw std::runtime_error(ss.str());
    }
    if (x0 == x1) {
        //special case for x0 == x1
        for (unsigned int i = std::min(y0, y1); i <= std::max(y0, y1); i++) {
            if (zbuffer.isCloser(x0, y0, z0, x1, y1, z1, x0, i)) {
                (image)(x0, i) = color;
            }
        }
    } else if (y0 == y1) {
        //special case for y0 == y1
        for (unsigned int i = std::min(x0, x1); i <= std::max(x0, x1); i++) {
            if (zbuffer.isCloser(x0, y0, z0, x1, y1, z1, i, y0)) {
                (image)(i, y0) = color;
            }
        }
    } else {
        if (x0 > x1) {
            //flip points if x1>x0: we want x0 to have the lowest value
            std::swap(x0, x1);
            std::swap(y0, y1);
            std::swap(z0, z1);
        }
        double m = ((double) y1 - (double) y0) / ((double) x1 - (double) x0); // Slope
        if (-1.0 <= m && m <= 1.0) {
            // Check if the slope is between -1 and 1
            for (unsigned int i = 0; i <= (x1 - x0); i++) {
                // Calculate the y-coordinate of the point on the line for a given x-coordinate (using y = mx + b)
                if (zbuffer.isCloser(x0, y0, z0, x1, y1, z1, x0 + i, (unsigned int) round(y0 + m * i))) {
                    (image)(x0 + i, (unsigned int) round(y0 + m * i)) = color;
                }
            }
        } else if (m > 1.0) {
            // Check if the slope is greater than 1
            for (unsigned int i = 0; i <= (y1 - y0); i++) {
                // Calculate the x-coordinate of the point on the line for a given y-coordinate (using x = (y - b)/m)
                if (zbuffer.isCloser(x0, y0, z0, x1, y1, z1,  (unsigned int) round(x0 + (i / m)), y0 + i)) {
                    (image)((unsigned int) round(x0 + (i / m)), y0 + i) = color;
                }
            }
        } else if (m < -1.0) {
            // Check if the slope is less than -1
            for (unsigned int i = 0; i <= (y0 - y1); i++) {
                // Calculate the x-coordinate of the point on the line for a given y-coordinate (using x = (y - b)/m)
                if (zbuffer.isCloser(x0, y0, z0, x1, y1, z1, (unsigned int) round(x0 - (i / m)), y0 - i)) {
                    (image)((unsigned int) round(x0 - (i / m)), y0 - i) = color;
                }
            }
        }
    }
}
