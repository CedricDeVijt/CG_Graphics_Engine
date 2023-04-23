#include "WireframeFigureDrawing3D.h"
#include "WireframeFigureDrawing3DParser.h"
#include "../objects/Line2D.h"
#include "../objects/TransformationMatrix.h"
#include "../SharedFunctions/DrawLines.h"
#include "../SharedFunctions/ImageSize.h"
#include "../SharedFunctions/ScaleLines.h"
#include "../SharedFunctions/ProjectionFunctions.h"

WireframeFigureDrawing3D::WireframeFigureDrawing3D(const ini::Configuration &configuration) {
    // Get data from configuration
    int size = configuration["General"]["size"].as_int_or_die();
    std::vector<double> eyeTuple = configuration["General"]["eye"].as_double_tuple_or_die();
    Vector3D eye = Vector3D::vector(eyeTuple[0],eyeTuple[1],eyeTuple[2]);
    std::vector<int> backgroundcolor = configuration["General"]["backgroundcolor"].as_int_tuple_or_die();
    int nrFigures = configuration["General"]["nrFigures"].as_int_or_die();

    // Get all figures from configuration
    Figures3D figuresList = getFigures(configuration, eye, nrFigures);

    // Project lines of all figures
    Lines2D lines = ProjectionFunctions::doProjection(figuresList);

    // Calculate size image
    std::vector<int> imageSize = ImageSize::getImageSize(lines, size, x_min, x_max,y_min, y_max);

    // Scale lines
    ScaleLines::scale2DLines(lines, imageSize, x_min, x_max, y_min,  y_max);

    // Make image
    image = img::EasyImage(imageSize[0], imageSize[1], img::Color(backgroundcolor[0]*255,
                                                                  backgroundcolor[1]*255,
                                                                  backgroundcolor[2]*255));

    // Draw lines on image
    DrawLines::draw2DLines(image, lines);
}

Figures3D WireframeFigureDrawing3D::getFigures(const ini::Configuration &configuration, Vector3D &eye, int nrFigures) const {
    Figures3D figuresList;
    for (int i = 0; i < nrFigures; i++) {
        // Create new figure form data
        std::string figureName = "Figure" + std::to_string(i);

        auto newFigure = WireframeFigureDrawing3DParser::parseWireframeFigureDrawing3DFigure(configuration[figureName]);

        // Apply transformations to all figures (rotations, translation, scaling and eye point transformation)
        Matrix combinedMatrix = TransformationMatrix::linedrawing3DTransformation(newFigure.getScale(), newFigure.getRotateX()*M_PI/180, newFigure.getRotateY()*M_PI/180, newFigure.getRotateZ()*M_PI/180, newFigure.getCenter(), eye);
        newFigure.applyTransformation(combinedMatrix);

        // Add figure to list
        figuresList.push_back(newFigure);
    }
    return figuresList;
}

const img::EasyImage &WireframeFigureDrawing3D::getImage() const {
    return image;
}
