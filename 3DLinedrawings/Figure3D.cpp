#include "Figure3D.h"

Figure3D::Figure3D(ini::Section figure) {
    type = figure["type"].as_string_or_die();
    rotateX = figure["rotateX"].as_int_or_die();
    rotateY = figure["rotateY"].as_int_or_die();
    rotateZ = figure["rotateZ"].as_int_or_die();
    scale = figure["scale"].as_int_or_die();

    center = figure["center"].as_int_tuple_or_die();
    std::vector<int> figureColor = figure["color"].as_int_tuple_or_die();
    color = img::Color(figureColor[0],figureColor[1],figureColor[2]);

    // get all points
    int nrPoints = figure["nrPoints"].as_int_or_die();
    for (int i = 0; i < nrPoints; i++) {
        std::string pointName = "figure" + std::to_string(i);
        auto figurePoint = figure[pointName].as_int_tuple_or_die();
        auto newPoint  = Vector3D::point(figurePoint[0], figurePoint[1], figurePoint[2]);
        points.push_back(newPoint);
    }

    // get all lines
    int nrLines = figure["nrLines"].as_int_or_die();
    for (int i = 0; i < nrLines; i++) {
        std::string lineName = "line" + std::to_string(i);
        auto figureLine = figure[lineName].as_int_tuple_or_die();
        faces.push_back(Face3D(figureLine));
    }

}
