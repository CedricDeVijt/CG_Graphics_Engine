#include <sstream>
#include <limits>
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
                                 unsigned int z0, unsigned int x1, unsigned int y1, unsigned int z1, img::Color color) {
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
                if (zbuffer.isCloser(x0, y0, z0, x1, y1, z1, (unsigned int) round(x0 + (i / m)), y0 + i)) {
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

void ImageDrawer::drawTriangulatedFigures(img::EasyImage &image, const Figures3D &figures, const double &x_min,
                                          const double &x_max, const double &y_min, const double &y_max) {
    // Create a Z-buffer for the image
    ZBuffer zBuffer((int) image.get_width(), (int) image.get_height());

    // Draw each figure on image
    for (Figure3D figure: figures) {
        // Calculate the center of the figure
        double scale = figure.getScale();
        double DCx = (scale * (x_min + x_max)) / 2;
        double DCy = (scale * (y_min + y_max)) / 2;

        // Calculate the offset from the image center to the figure center
        double dx = (image.get_width() / 2) - DCx;
        double dy = (image.get_height() / 2) - DCy;

        // Draw each face of the figure on the image
        for (Face3D face: figure.faces) {
            // Calculate the center of the face
            auto faceCenter = (figure.points[face.point_indexes[0]]
                               + figure.points[face.point_indexes[1]]
                               + figure.points[face.point_indexes[2]]) / 3;

            // Draw the face onto the image using the Z-buffer algorithm
            draw_zbuf_triag(zBuffer, image,
                            figure.points[face.point_indexes[0]],
                            figure.points[face.point_indexes[1]],
                            figure.points[face.point_indexes[2]],
                            faceCenter.length(), dx, dy, figure.getColor());
        }
    }
}

void ImageDrawer::draw_zbuf_triag(ZBuffer &zBuffer, img::EasyImage &image, const Vector3D &A, const Vector3D &B,
                                  const Vector3D &C, double d, double dx, double dy, img::Color color) {
    // Project the three points onto the screen and store them as Point2D objects
    Point2D A_proj(d * A.x / (-A.z) + dx, d * A.y / (-A.z) + dy);
    Point2D B_proj(d * B.x / (-B.z) + dx, d * B.y / (-B.z) + dy);
    Point2D C_proj(d * C.x / (-C.z) + dx, d * C.y / (-C.z) + dy);

    // Find the minimum and maximum y coordinates of the triangle and round them to integer values
    int y_min = round(std::min({A_proj.y, B_proj.y, C_proj.y}) + 0.5);
    int y_max = round(std::max({A_proj.y, B_proj.y, C_proj.y}) - 0.5);

    // Calculate the coordinates of the centroid and the reciprocal of the depth of the centroid
    double xg = (A_proj.x + B_proj.x + C_proj.x) / 3;
    double yg = (A_proj.y + B_proj.y + C_proj.y) / 3;
    double oneOverZg = 1 / (3 * A.z) + 1 / (3 * B.z) + 1 / (3 * C.z);

    // Loop through each row of the triangle
    for (int y = y_min; y <= y_max; ++y) {
        // Initialize the left and right x coordinates to infinity and negative infinity, respectively
        int xLAB = std::numeric_limits<int>::infinity();
        int xLAC = std::numeric_limits<int>::infinity();
        int xLBC = std::numeric_limits<int>::infinity();
        int xRAB = -std::numeric_limits<int>::infinity();
        int xRAC = -std::numeric_limits<int>::infinity();
        int xRBC = -std::numeric_limits<int>::infinity();

        // Check if the current row intersects each edge of the triangle
        // Calculate the x coordinates where the edge intersects the row and store them as either the left or right x coordinate depending on which side of the triangle the row is on
        if ((y - A_proj.y) * (y - B_proj.y) <= 0 and A_proj.y != B_proj.y) {
            xLAB = B_proj.x + (A_proj.x - B_proj.x) * (y - B_proj.y) / (A_proj.y - B_proj.y);
            xRAB = xLAB;
        }
        if ((y - A_proj.y) * (y - C_proj.y) <= 0 and A_proj.y != C_proj.y) {
            xLAC = C_proj.x + (A_proj.x - C_proj.x) * (y - C_proj.y) / (A_proj.y - C_proj.y);
            xRAC = xLAC;
        }
        if ((y - B_proj.y) * (y - C_proj.y) <= 0 and C_proj.y != B_proj.y) {
            xLBC = C_proj.x + (B_proj.x - C_proj.x) * (y - C_proj.y) / (B_proj.y - C_proj.y);
            xRBC = xLBC;
        }

        // calculate the left and right x coordinates of the triangle for the current y value
        int xL = round(std::min({xLAB, xLAC, xLBC}) + 0.5);
        int xR = round(std::max({xRAB, xRAC, xRBC}) - 0.5);

        for (int x = xL; x <= xR; ++x) {
            Vector3D u = B - A;
            Vector3D v = C - A;
            Vector3D w = Vector3D::point(u.y * v.z - u.z * v.y, u.z * v.x - u.x * v.z, u.x * v.y - u.y * v.x);

            double k = w.x * A.x + w.y * A.y + w.z * A.z;

            double dzdx = w.x / (-d * k);
            double dzdy = w.y / (-d * k);

            double oneOverZ = 1.0001 * oneOverZg + (x - xg) * dzdx + (y - yg) * dzdy;

//            if (zBuffer.isCloser(x, y, oneOverZ)) {
//                (image)(x, y) = color;
//            }
            (image)(x, y) = color;
        }
    }
}
