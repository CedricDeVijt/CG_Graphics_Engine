#include "Linedrawing3D.h"
#include "Figure3D.h"

Linedrawing3D::Linedrawing3D(const ini::Configuration &configuration) {
    // Get data from configuration
    int size = configuration["General"]["size"].as_int_or_die();
    std::vector<double> eye = configuration["General"]["eye"].as_double_tuple_or_die();
    std::vector<int> backgroundcolor = configuration["General"]["backgroundcolor"].as_int_tuple_or_die();
    int nrFigures = configuration["General"]["nrFigures"].as_int_or_die();

    // Get all figures from configuration
    Figures3D figuresList;
    for (int i = 0; i < nrFigures; i++) {
        std::string figureName = "Figure" + std::to_string(nrFigures);
        auto newFigure  = Figure3D(configuration[figureName]);
        figuresList.push_back(newFigure);
    }

    // Eye-point transformation on all figures


    // Project lines of all figures

    // Get lines from figures

    // Calculate size image

    // Make image

    // Draw lines on image


}

const img::EasyImage &Linedrawing3D::getImage() const {
    return image;
}
