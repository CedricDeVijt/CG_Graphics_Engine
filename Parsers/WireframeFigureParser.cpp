#include <fstream>
#include <cmath>

#include "WireframeFigureParser.h"
#include "../BaseFiles/l_parser.h"
#include "../Objects/Line2D.h"
#include "../SharedFunctions/LSystemFunctions.h"
#include "../SharedFunctions/SplitTriangleFaces.h"

Figure3D WireframeFigureParser::parseWireframeFigure(const ini::Section &figure) {
    // Get data from config
    std::string type = figure["type"].as_string_or_die();

    double rotateX = figure["rotateX"].as_double_or_die();
    double rotateY = figure["rotateY"].as_double_or_die();
    double rotateZ = figure["rotateZ"].as_double_or_die();
    const std::vector<double> &rotations = {rotateX, rotateY, rotateZ};

    const double &scale = figure["scale"].as_double_or_die();

    auto centerTuple = figure["center"].as_double_tuple_or_die();
    Vector3D center = Vector3D::vector(centerTuple[0], centerTuple[1], centerTuple[2]);

    std::vector<double> figureColor = figure["color"].as_double_tuple_or_die();
    img::Color color = img::Color(figureColor[0]*255, figureColor[1]*255, figureColor[2]*255);

    std::string inputfile = figure["inputfile"].as_string_or_default("");

    double R = figure["R"].as_double_or_default(0);
    double r = figure["r"].as_double_or_default(0);
    int n = figure["n"].as_int_or_default(0);
    double m = figure["m"].as_double_or_default(0);

    double height = figure["height"].as_double_or_default(0);

    // Create correct figure
    if (type == "LineDrawing") {
        return WireframeFigureParser::parseLineDrawing(figure, rotations, scale, center, color);
    }else if (type == "3DLSystem"){
        return WireframeFigureParser::parse3DLSystem(rotations, scale, center, color, inputfile);
    } else if (type == "Cube"){
        return WireframeFigureParser::createCube(rotations, scale, center, color);
    } else if (type == "Tetrahedron"){
        return WireframeFigureParser::createTetrahedron(rotations, scale, center, color);
    } else if (type == "Octahedron"){
        return WireframeFigureParser::createOctahedron(rotations, scale, center, color);
    } else if (type == "Icosahedron"){
        return WireframeFigureParser::createIcosahedron(rotations, scale, center, color);
    } else if (type == "Dodecahedron"){
        return WireframeFigureParser::createDodecahedron(rotations, scale, center, color);
    } else if (type == "Cylinder"){
        return WireframeFigureParser::createCylinder(rotations, scale, center, color, n, height);
    } else if (type == "Cone"){
        return WireframeFigureParser::createCone(rotations, scale, center, color, n, height);
    } else if (type == "Sphere"){
        return WireframeFigureParser::createSphere(rotations, scale, center, color, n);
    } else if (type == "Torus"){
        return WireframeFigureParser::parseTorus(rotations, scale, center, color, R, r, n, m);
    } else {
        return {};
    }
}

Figure3D WireframeFigureParser::parseLineDrawing(const ini::Section &figure, const std::vector<double> &rotations, const double &scale, const Vector3D &center, const img::Color &color) {
    std::vector<Face3D> faces;
    std::vector<Vector3D> points;

    int nrPoints = figure["nrPoints"].as_int_or_die();
    int nrLines = figure["nrLines"].as_int_or_die();

    // Points
    for (int i = 0; i < nrPoints; i++) {
        std::string pointName = "point" + std::to_string(i);
        auto figurePoint = figure[pointName].as_double_tuple_or_die();
        auto newPoint  = Vector3D::point(figurePoint[0], figurePoint[1], figurePoint[2]);
        points.emplace_back(newPoint);
    }

    // Faces
    for (int i = 0; i < nrLines; i++) {
        std::string lineName = "line" + std::to_string(i);
        ini::IntTuple figureLine = figure[lineName].as_int_tuple_or_die();
        auto newFace  = Face3D(figureLine);
        faces.emplace_back(newFace);
    }

    return {faces, points, rotations, scale, center, color};
}

Figure3D
WireframeFigureParser::parse3DLSystem(const std::vector<double> &rotations, const double &scale, const Vector3D &center,
                                      const img::Color &color, const std::string &inputfile) {
    // Parse L-system from inputfile
    LParser::LSystem3D l_system = LSystemFunctions::parseLSystem3D(inputfile);

    // Calculate string
    std::string figureString = LSystemFunctions::getLSystemString(l_system);

    // Get all lines
    std::pair<std::vector<Face3D>, std::vector<Vector3D>> lines = LSystemFunctions::getFacesAndPoints(l_system, figureString);

    return {lines.first, lines.second, rotations, scale, center, color};
}

Figure3D WireframeFigureParser::createCube(const std::vector<double> &rotations, const double &scale, const Vector3D& center, const img::Color& color) {
    std::vector<Face3D> faces;
    std::vector<Vector3D> points;

    // Points
    points.emplace_back(Vector3D::point(1, -1, -1));
    points.emplace_back(Vector3D::point(-1, 1, -1));
    points.emplace_back(Vector3D::point(1, 1, 1));
    points.emplace_back(Vector3D::point(-1, -1, 1));
    points.emplace_back(Vector3D::point(1, 1, -1));
    points.emplace_back(Vector3D::point(-1, -1, -1));
    points.emplace_back(Vector3D::point(1, -1, 1));
    points.emplace_back(Vector3D::point(-1, 1, 1));

    // Faces
    faces.emplace_back(Face3D({0, 4, 2, 6}));
    faces.emplace_back(Face3D({4, 1, 7, 2}));
    faces.emplace_back(Face3D({1, 5, 3, 7}));
    faces.emplace_back(Face3D({5, 0, 6, 3}));
    faces.emplace_back(Face3D({6, 2, 7, 3}));
    faces.emplace_back(Face3D({0, 5, 1, 4}));

    return {faces, points, rotations, scale, center, color};
}

Figure3D WireframeFigureParser::createTetrahedron(const std::vector<double> &rotations, const double &scale, const Vector3D& center, const img::Color& color) {
    std::vector<Face3D> faces;
    std::vector<Vector3D> points;

    // Points
    points.emplace_back(Vector3D::point(1, -1, -1));
    points.emplace_back(Vector3D::point(-1, 1, -1));
    points.emplace_back(Vector3D::point(1, 1, 1));
    points.emplace_back(Vector3D::point(-1, -1, 1));

    // Faces
    faces.emplace_back(Face3D({0, 1, 2}));
    faces.emplace_back(Face3D({1, 3, 2}));
    faces.emplace_back(Face3D({0, 3, 1}));
    faces.emplace_back(Face3D({0, 2, 3}));

    return {faces, points, rotations, scale, center, color};
}

Figure3D WireframeFigureParser::createOctahedron(const std::vector<double> &rotations, const double &scale, const Vector3D& center, const img::Color& color) {
    std::vector<Face3D> faces;
    std::vector<Vector3D> points;

    // Points
    points.emplace_back(Vector3D::point(1, 0, 0));
    points.emplace_back(Vector3D::point(0, 1, 0));
    points.emplace_back(Vector3D::point(-1, 0, 0));
    points.emplace_back(Vector3D::point(0, -1, 0));
    points.emplace_back(Vector3D::point(0, 0, -1));
    points.emplace_back(Vector3D::point(0, 0, 1));

    // Faces
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

Figure3D WireframeFigureParser::createIcosahedron(const std::vector<double> &rotations, const double &scale, const Vector3D& center, const img::Color& color) {
    std::vector<Face3D> faces;
    std::vector<Vector3D> points;

    // Points
    points.emplace_back(Vector3D::point(0, 0, (sqrt(5)) / 2));
    for (int i = 1; i < 6; ++i) {
        points.emplace_back(Vector3D::point(cos((i - 2) * 2 * M_PI / 5), sin((i - 2) * 2 * M_PI / 5), 0.5));
    }
    for (int i = 6; i < 11; ++i) {
        points.emplace_back(
                Vector3D::point(cos(M_PI / 5 + (i - 7) * 2 * M_PI / 5), sin(M_PI / 5 + (i - 7) * 2 * M_PI / 5), -0.5));
    }
    points.emplace_back(Vector3D::point(0, 0, -sqrt(5) / 2));

    // Faces
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
    faces.emplace_back(Face3D({1, 10, 6}));
    faces.emplace_back(Face3D({11, 7, 6}));
    faces.emplace_back(Face3D({11, 8, 7}));
    faces.emplace_back(Face3D({11, 9, 8}));
    faces.emplace_back(Face3D({11, 10, 9}));
    faces.emplace_back(Face3D({11, 6, 10}));



    return {faces, points, rotations, scale, center, color};
}

Figure3D WireframeFigureParser::createDodecahedron(const std::vector<double> &rotations, const double &scale, const Vector3D &center, const img::Color &color) {
    std::vector<Face3D> faces;
    std::vector<Vector3D> points;

    // Points
    Figure3D icosahedron = createIcosahedron({0, 0, 0}, 1, Vector3D::vector(0, 0, 0), color);
    for (const Face3D &face : icosahedron.faces){
        double x = (icosahedron.points[face.point_indexes[0]].x +
                    icosahedron.points[face.point_indexes[1]].x +
                    icosahedron.points[face.point_indexes[2]].x) / 3;

        double y = (icosahedron.points[face.point_indexes[0]].y +
                    icosahedron.points[face.point_indexes[1]].y +
                    icosahedron.points[face.point_indexes[2]].y) / 3;

        double z = (icosahedron.points[face.point_indexes[0]].z +
                    icosahedron.points[face.point_indexes[1]].z +
                    icosahedron.points[face.point_indexes[2]].z) / 3;

        points.push_back(Vector3D::point(x, y, z));
    }

    // Faces
    faces.emplace_back(Face3D({0, 1, 2, 3, 4}));
    faces.emplace_back(Face3D({0, 5, 6, 7, 1}));
    faces.emplace_back(Face3D({1, 7, 8, 9, 2}));
    faces.emplace_back(Face3D({2, 9, 10, 11, 3}));
    faces.emplace_back(Face3D({3, 11, 12, 13, 4}));
    faces.emplace_back(Face3D({4, 13, 14, 5, 0}));
    faces.emplace_back(Face3D({19, 18, 17, 16, 15}));
    faces.emplace_back(Face3D({19, 14, 13, 12, 18}));
    faces.emplace_back(Face3D({18, 12, 11, 10, 17}));
    faces.emplace_back(Face3D({17, 10, 9, 8, 16}));
    faces.emplace_back(Face3D({16, 8, 7, 6, 15}));
    faces.emplace_back(Face3D({15, 6, 5, 14, 19}));

    return {faces, points, rotations, scale, center, color};
}

Figure3D WireframeFigureParser::createCylinder(const std::vector<double> &rotations, const double &scale, const Vector3D& center, const img::Color& color, const int &n, const double &height) {
    std::vector<Face3D> faces;
    std::vector<Vector3D> points;

    // Points
    for (int i = 0; i < n; ++i) {
        points.push_back(Vector3D::point(cos(2 * i * M_PI / n), sin(2 * i * M_PI / n), height));
        points.push_back(Vector3D::point(cos(2 * i * M_PI / n), sin(2 * i * M_PI / n), 0));
    }

    // Faces
    for (int i = 0; i < n; ++i) {
        faces.push_back(Face3D({2*i, 2*i+1, (2*i+3) % (2*n), (2*i+2) % (2*n)}));
    }
    std::vector<int> topFace;
    std::vector<int> bottomFace;
    for (int i = 0; i < n; ++i) {
        topFace.push_back(2*i);
        bottomFace.push_back(2*i+1);
    }
    faces.emplace_back(topFace);
    faces.emplace_back(bottomFace);

    return {faces, points, rotations, scale, center, color};
}

Figure3D WireframeFigureParser::createCone(const std::vector<double> &rotations, const double &scale, const Vector3D& center, const img::Color& color, const int &n, const double &height) {
    std::vector<Face3D> faces;
    std::vector<Vector3D> points;

    // Points
    for (int i = 0; i < n; ++i) {
        points.push_back(Vector3D::point(cos(2 * i * M_PI / n), sin(2 * i * M_PI / n), 0));
    }
    points.emplace_back(Vector3D::point(0, 0, height));

    // Faces
    for (int i = 0; i < n; ++i) {
        faces.emplace_back(Face3D({n, i % n, (i + 1) % n}));
    }
    std::vector<int> topFace;
    for (int i = 0; i < n; ++i) {
        topFace.push_back(i);
    }

    return {faces, points, rotations, scale, center, color};
}

Figure3D WireframeFigureParser::createSphere(const std::vector<double> &rotations, const double &scale, const Vector3D& center, const img::Color& color, const int &n) {
    if (n == 0){
        return createIcosahedron(rotations, scale, center, color);
    } else {
        Figure3D icosahedron = createIcosahedron({0, 0, 0}, 1, Vector3D::vector(0, 0, 0), color);

        // Split icosahedron n-times
        std::pair<std::vector<Face3D>, std::vector<Vector3D>> splitFaces = SplitTriangleFaces::splitFaces(icosahedron.faces, icosahedron.points, n);

        // Normalize points
        for (Vector3D &point : splitFaces.second){
            point.normalise();
        }

    return {splitFaces.first, splitFaces.second, rotations, scale, center, color};
    }
}

Figure3D WireframeFigureParser::parseTorus(const std::vector<double> &rotations, const double &scale, const Vector3D& center, const img::Color& color, const double &R, const double &r, const int &n, const int &m) {
    std::vector<Face3D> faces;
    std::vector<Vector3D> points;
    // Split tube
    for (int i = 0; i < n; ++i) {
        double u = i * (2 * M_PI / n);
        // Split circle
        for (int j = 0; j < m; ++j) {
            double v = j * (2 * M_PI / m);

            points.emplace_back(Vector3D::point((R + r * cos(v)) * cos(u),
                                                (R + r * cos(v)) * sin(u),
                                                r * sin(v)));

            faces.emplace_back(
                Face3D({
                    calculateIndex(i,j,m),
                    calculateIndex((i + 1) % n,j,m),
                    calculateIndex((i + 1) % n,(j + 1) % m,m),
                    calculateIndex(i,(j + 1) % m,m)})
            );
        }
    }

    return {faces, points, rotations, scale, center, color};
}

int WireframeFigureParser::calculateIndex(const int &i, const int &j, const int &m) {
    return i*m+j;
}
