//
// Created by Cedric De Vijt on 09/04/2023.
//

#include "Linedrawing3DFigureParser.h"

Figure3D Linedrawing3DFigureParser::parseLinedrawing3D(const ini::Section &figure) {
    std::vector<Face3D> faces;
    std::vector<Vector3D> points;

    // get all data from section
    std::string type = figure["type"].as_string_or_die();
    int rotateX = figure["rotateX"].as_int_or_die();
    int rotateY = figure["rotateY"].as_int_or_die();
    int rotateZ = figure["rotateZ"].as_int_or_die();
    std::vector<int> rotations = {rotateX, rotateY, rotateZ};

    double scale = figure["scale"].as_double_or_die();

    auto centerTuple = figure["center"].as_int_tuple_or_die();
    Vector3D center = Vector3D::vector(centerTuple[0], centerTuple[1], centerTuple[2]);


    int nrPoints = figure["nrPoints"].as_int_or_die();
    int nrLines = figure["nrLines"].as_int_or_die();

    std::vector<double> figureColor = figure["color"].as_double_tuple_or_die();
    img::Color color = img::Color(figureColor[0]*255, figureColor[1]*255, figureColor[2]*255);

    // get all points
    for (int i = 0; i < nrPoints; i++) {
        std::string pointName = "point" + std::to_string(i);
        auto figurePoint = figure[pointName].as_double_tuple_or_die();
        auto newPoint  = Vector3D::point(figurePoint[0]*scale, figurePoint[1]*scale, figurePoint[2]*scale);
        points.emplace_back(newPoint);
    }

    // get all faces
    for (int i = 0; i < nrLines; i++) {
        std::string lineName = "line" + std::to_string(i);
        ini::IntTuple figureLine = figure[lineName].as_int_tuple_or_die();
        auto newFace  = Face3D(figureLine);
        faces.emplace_back(newFace);
    }

    return {faces, points, rotations, scale, center, color};
}
