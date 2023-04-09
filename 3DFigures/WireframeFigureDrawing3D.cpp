#include "WireframeFigureDrawing3D.h"
#include "../objects/Figure3D.h"
#include "../objects/TransformationMatrix.h"
#include "../objects/Line2D.h"

WireframeFigureDrawing3D::WireframeFigureDrawing3D(const ini::Configuration &configuration) {
    // Get data from configuration
    int size = configuration["General"]["size"].as_int_or_die();
    std::vector<double> eyeTuple = configuration["General"]["eye"].as_double_tuple_or_die();
    Vector3D eye = Vector3D::vector(eyeTuple[0],eyeTuple[1],eyeTuple[2]);
    std::vector<int> backgroundcolor = configuration["General"]["backgroundcolor"].as_int_tuple_or_die();
    int nrFigures = configuration["General"]["nrFigures"].as_int_or_die();

    // Get all figures from configuration
    Figures3D figuresList;
    Lines2D lines;
}
