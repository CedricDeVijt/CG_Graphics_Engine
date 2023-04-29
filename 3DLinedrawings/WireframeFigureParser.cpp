#include <fstream>
#include "WireframeFigureParser.h"
#include "../l_parser.h"

Figure3D WireframeFigureParser::parseWireframeFigureDrawing3DFigure(const ini::Section &figure) {
    std::string type = figure["type"].as_string_or_die();

    double rotateX = figure["rotateX"].as_int_or_die();
    double rotateY = figure["rotateY"].as_int_or_die();
    double rotateZ = figure["rotateZ"].as_int_or_die();
    std::vector<double> rotations = {rotateX, rotateY, rotateZ};

    double scale = figure["scale"].as_double_or_die();
    auto centerTuple = figure["center"].as_int_tuple_or_die();
    Vector3D center = Vector3D::vector(centerTuple[0], centerTuple[1], centerTuple[2]);
    std::vector<double> figureColor = figure["color"].as_double_tuple_or_die();
    img::Color color = img::Color(figureColor[0]*255, figureColor[1]*255, figureColor[2]*255);

    if (type == "LineDrawing") {
        return WireframeFigureParser::parseLineDrawing(figure, rotations, scale, center, color);
    }else if (type == "3DLSystem"){
        return WireframeFigureParser::parse3DLSystem(figure, rotations, scale, center, color);
    } else if (type == "Cube"){
        return WireframeFigureParser::parseCube(figure, rotations, scale, center, color);
    } else if (type == "Tetrahedron"){
        return WireframeFigureParser::parseTetrahedron(figure, rotations, scale, center, color);
    } else if (type == "Octahedron"){
        return WireframeFigureParser::parseOctahedron(figure, rotations, scale, center, color);
    } else if (type == "Icosahedron"){
        return WireframeFigureParser::parseIcosahedron(figure, rotations, scale, center, color);
//    } else if (type == "Dodecahedron"){
//        return WireframeFigureParser::parseDodecahedron(figure, rotations, scale, center, color);
//    } else if (type == "Cylinder"){
//        return WireframeFigureParser::parseCylinder(figure, rotations, scale, center, color);
//    } else if (type == "Cone"){
//        return WireframeFigureParser::parseCone(figure, rotations, scale, center, color);
//    } else if (type == "Sphere"){
//        return WireframeFigureParser::parseSphere(figure, rotations, scale, center, color);
//    } else if (type == "Torus"){
//        return WireframeFigureParser::parseTorus(figure, rotations, scale, center, color);
//    } else {
//        return Figure3D(__1::vector(), __1::vector(), __1::vector(), 0, Vector3D(), img::Color());
    } else {
        std::vector<Face3D> faces;
        std::vector<Vector3D> points;
        return {faces, points, rotations, scale, center, color};
    }
}

Figure3D WireframeFigureParser::parseLineDrawing(const ini::Section &figure, std::vector<double> rotations, double scale,
                                                 const Vector3D &center, const img::Color &color) {
    std::vector<Face3D> faces;
    std::vector<Vector3D> points;

    int nrPoints = figure["nrPoints"].as_int_or_die();
    int nrLines = figure["nrLines"].as_int_or_die();

    // get all points
    for (int i = 0; i < nrPoints; i++) {
        std::string pointName = "point" + std::to_string(i);
        auto figurePoint = figure[pointName].as_double_tuple_or_die();
        auto newPoint  = Vector3D::point(figurePoint[0], figurePoint[1], figurePoint[2]);
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

Figure3D WireframeFigureParser::parse3DLSystem(const ini::Section &figure, std::vector<double> rotations, double scale,
                                               const Vector3D &center, const img::Color &color) {
    // Get input file
    std::string inputfile = figure["inputfile"].as_string_or_die();

    // Parse L-system from inputfile
    LParser::LSystem3D l_system;
    std::ifstream input_stream(inputfile);
    input_stream >> l_system;
    input_stream.close();

    // Calculate string
    std::string oldString = l_system.get_initiator();
    std::string figureString;
    if (l_system.get_nr_iterations() == 0){
        figureString = oldString;
    } else {
        for (int i = 0; i < l_system.get_nr_iterations(); ++i) {
            figureString = "";
            for (char c: oldString) {
                if (l_system.get_alphabet().find(c) != l_system.get_alphabet().end()){
                    figureString += l_system.get_replacement(c);
                } else {
                    figureString += c;
                }
            }
            oldString = figureString;
        }
    }

    // Get all lines



    return Figure3D();
}

Figure3D WireframeFigureParser::parseCube(const ini::Section& figure, std::vector<double> rotations, double scale, const Vector3D& center, const img::Color& color) {
    std::vector<Face3D> faces;
    std::vector<Vector3D> points;

    points.emplace_back(Vector3D::point(1, -1, -1));
    points.emplace_back(Vector3D::point(-1, 1, -1));
    points.emplace_back(Vector3D::point(1, 1, 1));
    points.emplace_back(Vector3D::point(-1, -1, 1));
    points.emplace_back(Vector3D::point(1, 1, -1));
    points.emplace_back(Vector3D::point(-1, -1, -1));
    points.emplace_back(Vector3D::point(1, -1, 1));
    points.emplace_back(Vector3D::point(-1, 1, 1));

    faces.emplace_back(Face3D({0, 4, 2, 6}));
    faces.emplace_back(Face3D({4, 1, 7, 2}));
    faces.emplace_back(Face3D({1, 5, 3, 7}));
    faces.emplace_back(Face3D({5, 0, 6, 3}));
    faces.emplace_back(Face3D({6, 2, 7, 3}));
    faces.emplace_back(Face3D({0, 5, 1, 4}));


    return {faces, points, rotations, scale, center, color};
}

Figure3D WireframeFigureParser::parseTetrahedron(const ini::Section& figure, std::vector<double> rotations, double scale, const Vector3D& center, const img::Color& color) {
    std::vector<Face3D> faces;
    std::vector<Vector3D> points;

    points.emplace_back(Vector3D::point(1, -1, -1));
    points.emplace_back(Vector3D::point(-1, 1, -1));
    points.emplace_back(Vector3D::point(1, 1, 1));
    points.emplace_back(Vector3D::point(-1, -1, 1));

    faces.emplace_back(Face3D({0, 1, 2}));
    faces.emplace_back(Face3D({1, 3, 2}));
    faces.emplace_back(Face3D({0, 3, 1}));
    faces.emplace_back(Face3D({0, 2, 3}));


    return {faces, points, rotations, scale, center, color};
}

Figure3D WireframeFigureParser::parseOctahedron(const ini::Section& figure, std::vector<double> rotations, double scale, const Vector3D& center, const img::Color& color) {
    std::vector<Face3D> faces;
    std::vector<Vector3D> points;

    points.emplace_back(Vector3D::point(1, 0, 0));
    points.emplace_back(Vector3D::point(0, 1, 0));
    points.emplace_back(Vector3D::point(-1, 0, 0));
    points.emplace_back(Vector3D::point(0, -1, 0));
    points.emplace_back(Vector3D::point(0, 0, -1));
    points.emplace_back(Vector3D::point(0, 0, 1));

    faces.emplace_back(Face3D({0, 1, 5}));
    faces.emplace_back(Face3D({1, 2, 5}));
    faces.emplace_back(Face3D({2, 3, 5}));
    faces.emplace_back(Face3D({3, 0, 5}));
    faces.emplace_back(Face3D({1, 0, 4}));
    faces.emplace_back(Face3D({2, 1, 4}));
    faces.emplace_back(Face3D({3, 2, 4}));
    faces.emplace_back(Face3D({0, 3, 4}));


    return {faces, points, rotations, scale, center, color};
}

Figure3D WireframeFigureParser::parseIcosahedron(const ini::Section& figure, std::vector<double> rotations, double scale, const Vector3D& center, const img::Color& color) {
    std::vector<Face3D> faces;
    std::vector<Vector3D> points;

    points.emplace_back(Vector3D::point(0, 0, sqrt(5) / 2));

    for (int i = 1; i < 6; ++i) {
        points.emplace_back(Vector3D::point(cos((i - 2) * 2 * M_PI / 5), sin((i - 2) * 2 * M_PI / 5), 0.5));
    }
    for (int i = 6; i < 11; ++i) {
        points.emplace_back(
                Vector3D::point(cos(M_PI / 5 + (i - 7) * 2 * M_PI / 5), sin(M_PI / 5 + (i - 7) * 2 * M_PI / 5), -0.5));
    }
    points.emplace_back(Vector3D::point(0, 0, -sqrt(5) / 2));

    faces.emplace_back(Face3D({0, 1, 2}));
    faces.emplace_back(Face3D({0, 2, 3}));
    faces.emplace_back(Face3D({0, 3, 4}));
    faces.emplace_back(Face3D({0, 4, 5}));
    faces.emplace_back(Face3D({0, 5, 1}));
    faces.emplace_back(Face3D({1, 6, 2}));
    faces.emplace_back(Face3D({2, 6, 7}));
    faces.emplace_back(Face3D({2, 7, 3}));
    faces.emplace_back(Face3D({3, 7, 8}));
    faces.emplace_back(Face3D({3, 8, 4}));
    faces.emplace_back(Face3D({4, 8, 9}));
    faces.emplace_back(Face3D({4, 9, 5}));
    faces.emplace_back(Face3D({5, 9, 10}));
    faces.emplace_back(Face3D({5, 10, 1}));
    faces.emplace_back(Face3D({1, 10, 11}));
    faces.emplace_back(Face3D({12, 8, 7}));
    faces.emplace_back(Face3D({12, 9, 8}));
    faces.emplace_back(Face3D({12, 10, 9}));
    faces.emplace_back(Face3D({12, 11, 10}));
    faces.emplace_back(Face3D({12, 7, 11}));


    return {faces, points, rotations, scale, center, color};
}

