#include "ZBufferedWireframeParser.h"
#include "WireframeFigureParser.h"
#include "../Objects/Line2D.h"
#include "../SharedFunctions/ProjectionFunctions.h"
#include "../SharedFunctions/ImageSize.h"
#include "../SharedFunctions/ScaleLines.h"
#include "../SharedFunctions/DrawLines.h"

img::EasyImage ZBufferedWireframeParser::parseZBufferedWireframe(const ini::Configuration &configuration) {
    // Get data from configuration
    int size = configuration["General"]["size"].as_int_or_die();
    std::vector<int> backgroundcolor = configuration["General"]["backgroundcolor"].as_int_tuple_or_die();
    int nrFigures = configuration["General"]["nrFigures"].as_int_or_die();
    std::vector<double> eyeTuple = configuration["General"]["eye"].as_double_tuple_or_die();
    Vector3D eye = Vector3D::vector(eyeTuple[0], eyeTuple[1], eyeTuple[2]);

    // Get all figures from configuration
    Figures3D figures = WireframeFigureParser::parseWireframeFigures(configuration, eye, nrFigures);

    // Project lines of all figures
    Lines2D lines = ProjectionFunctions::doProjection(figures);

    // Calculate image size
    double x_max, y_max, x_min, y_min;
    std::vector<int> imageSize = ImageSize::getImageSize(lines, size, x_min, x_max, y_min, y_max);

    // Make image
    img::EasyImage image = img::EasyImage(imageSize[0], imageSize[1],
                                          img::Color(backgroundcolor[0] * 255,
                                                     backgroundcolor[1] * 255,
                                                     backgroundcolor[2] * 255));

    // Scale lines
    ScaleLines::scale2DLines(lines, imageSize, x_min, x_max, y_min, y_max);

    // Draw lines on image
    DrawLines::drawZBuffer2DLines(image, lines);

    return image;
}
