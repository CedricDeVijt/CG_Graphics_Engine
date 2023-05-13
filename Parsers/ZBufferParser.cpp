#include "ZBufferParser.h"
#include "FigureParser.h"

#include "../Objects/Line2D.h"
#include "../Objects/TransformationMatrix.h"

#include "../SharedFunctions/ProjectionFunctions.h"
#include "../SharedFunctions/ImageSize.h"
#include "../SharedFunctions/TriangulateFace.h"
#include "../SharedFunctions/ImageDrawer.h"

img::EasyImage ZBufferParser::parseZBuffer(const ini::Configuration &configuration) {
    // Get data from configuration
    int size = configuration["General"]["size"].as_int_or_die();
    std::vector<int> backgroundcolor = configuration["General"]["backgroundcolor"].as_int_tuple_or_die();
    int nrFigures = configuration["General"]["nrFigures"].as_int_or_die();
    std::vector<double> eyeTuple = configuration["General"]["eye"].as_double_tuple_or_die();
    Vector3D eye = Vector3D::vector(eyeTuple[0], eyeTuple[1], eyeTuple[2]);

    // Get all figures from configuration
    Figures3D figures = FigureParser::parseWireframeFigures(configuration, eye, nrFigures);

    // Calculate image size
    double x_max, y_max, x_min, y_min;
    Lines2D imageSizeLines = ProjectionFunctions::doProjection(figures);
    std::vector<int> imageSize = ImageSize::getImageSize(imageSizeLines, size, x_min, x_max, y_min, y_max);

    // Create image
    img::EasyImage image = img::EasyImage(imageSize[0], imageSize[1],
                                          img::Color(backgroundcolor[0] * 255,
                                                     backgroundcolor[1] * 255,
                                                     backgroundcolor[2] * 255));

    // Split faces in triangles
    TriangulateFace::triangulateFigures(figures);

    // Draw figures on image
    ImageDrawer::drawTriangulatedFigures(image, figures, x_min, x_max, y_min, y_max);

    return image;
}
