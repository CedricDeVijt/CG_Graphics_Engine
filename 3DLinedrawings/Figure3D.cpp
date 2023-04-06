#include "Figure3D.h"
#include "../TransformationMatrix.h"

Figure3D::Figure3D(const ini::Section& figure) {
    // get all data from section
    getSection(figure);

    // get all points
    getPoints(figure);

    // get all faces
    getFaces(figure);
}

void Figure3D::getSection(const ini::Section &figure) {
//    type = figure["type"].as_string_or_die();
    rotateX = figure["rotateX"].as_int_or_die();
    rotateY = figure["rotateY"].as_int_or_die();
    rotateZ = figure["rotateZ"].as_int_or_die();
    scale = figure["scale"].as_double_or_die();

    auto centerTuple = figure["center"].as_int_tuple_or_die();
    center = Vector3D::vector(centerTuple[0], centerTuple[1], centerTuple[2]);


    nrPoints = figure["nrPoints"].as_int_or_die();
    nrLines = figure["nrLines"].as_int_or_die();

    std::vector<double> figureColor = figure["color"].as_double_tuple_or_die();
//    color = img::Color(figureColor[0]*255, figureColor[1]*255, figureColor[2]*255);
    color = img::Color(255, 0, 0);
}

void Figure3D::getPoints(const ini::Section &figure) {
    for (int i = 0; i < nrPoints; i++) {
        std::string pointName = "point" + std::to_string(i);
        auto figurePoint = figure[pointName].as_double_tuple_or_die();
        auto newPoint  = Vector3D::point(figurePoint[0], figurePoint[1], figurePoint[2]);
        points.emplace_back(newPoint);
    }
}

void Figure3D::getFaces(const ini::Section &figure) {
    for (int i = 0; i < nrLines; i++) {
        std::string lineName = "line" + std::to_string(i);
        ini::IntTuple figureLine = figure[lineName].as_int_tuple_or_die();
        auto newFace  = Face3D(figureLine);
        faces.emplace_back(newFace);
    }
}

void Figure3D::applyTransformation(Vector3D eye) {
    Matrix combinedMatrix = TransformationMatrix::linedrawing3DTransformation(scale, rotateX, rotateY, rotateZ, center, eye);

    for (auto &point : points){
        point = point * combinedMatrix;
    }
}

const img::Color &Figure3D::getColor() const {
    return color;
}
