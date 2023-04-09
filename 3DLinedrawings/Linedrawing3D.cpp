#include "Linedrawing3D.h"
#include "../objects/Figure3D.h"
#include "../objects/TransformationMatrix.h"
#include "Linedrawing3DFigureParser.h"

Linedrawing3D::Linedrawing3D(const ini::Configuration &configuration) {
    // Get data from configuration
    int size = configuration["General"]["size"].as_int_or_die();
    std::vector<double> eyeTuple = configuration["General"]["eye"].as_double_tuple_or_die();
    Vector3D eye = Vector3D::vector(eyeTuple[0],eyeTuple[1],eyeTuple[2]);
    std::vector<int> backgroundcolor = configuration["General"]["backgroundcolor"].as_int_tuple_or_die();
    int nrFigures = configuration["General"]["nrFigures"].as_int_or_die();

    // Get all figures from configuration
    Figures3D figuresList;
    Lines2D lines;
    for (int i = 0; i < nrFigures; i++) {
        // Create new figure form data
        std::string figureName = "Figure" + std::to_string(i);
        auto newFigure = Linedrawing3DFigureParser::parseLinedrawing3D(configuration[figureName]);

        // Apply transformations to all figures (rotations, translation, scaling and eye point transformation)
        Matrix combinedMatrix = TransformationMatrix::linedrawing3DTransformation(newFigure.getScale(), newFigure.getRotateX(), newFigure.getRotateY(), newFigure.getRotateZ(), newFigure.getCenter(), eye);
        newFigure.applyTransformation(combinedMatrix);

        // Add figure to list
        figuresList.push_back(newFigure);
    }

    // Project lines of all figures
    lines = doProjection(figuresList);

    // Calculate size image
    std::vector<int> imageSize = getImageSize(lines, size);

    // Scale lines
    scale2DLines(lines, imageSize);

    // Make image
    image = img::EasyImage(imageSize[0], imageSize[1], img::Color(backgroundcolor[0]*255,
                                                                  backgroundcolor[1]*255,
                                                                  backgroundcolor[2]*255));

    // Draw lines on image
    draw2DLines(lines);
}

Lines2D Linedrawing3D::doProjection(const Figures3D &figures) {
    Lines2D lines;

    for (const auto& figure : figures){
        std::vector<Face3D> faces = figure.faces;
        std::vector<Vector3D> points = figure.points;

        for (auto face : faces){
            auto point_indexes = face.point_indexes;

            Point2D point1 = doProjection(points[point_indexes[0]], 1);
            Point2D point2 = doProjection(points[point_indexes[1]], 1);

            lines.emplace_back(point1, point2, figure.getColor());
        }
    }
    return lines;
}

Point2D Linedrawing3D::doProjection(const Vector3D &point, const double d){
    double x = (d * point.x)/(-point.z);
    double y = (d * point.y)/(-point.z);

    return {x, y};
}


const img::EasyImage &Linedrawing3D::getImage() const {
    return image;
}

std::vector<int> Linedrawing3D::getImageSize(Lines2D lines, int size) {
    // Find min and max of x and y
    x_max = -INFINITY;
    y_max = -INFINITY;
    x_min = INFINITY;
    y_min = INFINITY;

    for (const Line2D& line : lines){
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
    double image_x = size*(range_x/max_range);
    double image_y = size*(range_y/max_range);

    return {int(image_x), int(image_y)};
}

void Linedrawing3D::draw2DLines(Lines2D lines) {
    for (Line2D line : lines){
        image.draw_line(lround(line.pointA.x), lround(line.pointA.y), lround(line.pointB.x), lround(line.pointB.y), line.colorIMG);
//        std::cout << "A:"<< line.pointA.x << ", " << line.pointA.y << "       B:"<< line.pointB.x << ", " << line.pointB.y << std::endl;
    }
}

void Linedrawing3D::scale2DLines(Lines2D &lines, const std::vector<int> imageSize) const {
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
