#include <fstream>
#include <cmath>

#include "FigureParser.h"
#include "../BaseFiles/l_parser.h"
#include "../Objects/Line2D.h"
#include "../SharedFunctions/LSystemFunctions.h"
#include "../SharedFunctions/TriangulateFace.h"
#include "../Objects/TransformationMatrix.h"
#include "../Objects/PlatonicFigure.h"
#include "../SharedFunctions/FigureFractaliser.h"

Figures3D
FigureParser::parseWireframeFigures(const ini::Configuration &configuration, Vector3D &eye, int nrFigures) {
    Figures3D figuresList;
    for (int i = 0; i < nrFigures; i++) {
        // Create new figure form data
        std::string figureName = "Figure" + std::to_string(i);
        Figures3D newFigures = FigureParser::parseWireframeFigure(configuration[figureName]);

        // Apply transformations to all figures (rotations, translation, scaling and eye point transformation)
        for (Figure3D figure: newFigures) {
            figure.applyTransformation(TransformationMatrix::linedrawing3DTransformation(figure.getScale(),
                                                                                         figure.getRotateX() * M_PI /
                                                                                         180.0,
                                                                                         figure.getRotateY() * M_PI /
                                                                                         180.0,
                                                                                         figure.getRotateZ() * M_PI /
                                                                                         180.0, figure.getCenter(),
                                                                                         eye));

            // Add figure to list
            figuresList.push_back(figure);
        }
    }
    return figuresList;
}

Figures3D FigureParser::parseWireframeFigure(const ini::Section &figure) {
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
    img::Color color = img::Color(figureColor[0] * 255, figureColor[1] * 255, figureColor[2] * 255);

    std::string inputfile = figure["inputfile"].as_string_or_default("");

    double R = figure["R"].as_double_or_default(0);
    double r = figure["r"].as_double_or_default(0);
    int n = figure["n"].as_int_or_default(0);
    int m = figure["m"].as_int_or_default(0);

    double height = figure["height"].as_double_or_default(0);

    int nrIterations = figure["nrIterations"].as_int_or_default(0);
    double fractalScale = figure["fractalScale"].as_double_or_default(0);

    // Create correct figure
    if (type == "LineDrawing") {
        Figure3D newFigure = FigureParser::parseLineDrawing(figure, rotations, scale, center, color);
        return {newFigure};
    } else if (type == "3DLSystem") {
        Figure3D newFigure = FigureParser::parse3DLSystem(rotations, scale, center, color, inputfile);
        return {newFigure};
    } else if (type == "Cube") {
        Figure3D newFigure = PlatonicFigure::createCube(rotations, scale, center, color);
        return {newFigure};
    } else if (type == "Tetrahedron") {
        Figure3D newFigure = PlatonicFigure::createTetrahedron(rotations, scale, center, color);
        return {newFigure};
    } else if (type == "Octahedron") {
        Figure3D newFigure = PlatonicFigure::createOctahedron(rotations, scale, center, color);
        return {newFigure};
    } else if (type == "Icosahedron") {
        Figure3D newFigure = PlatonicFigure::createIcosahedron(rotations, scale, center, color);
        return {newFigure};
    } else if (type == "Dodecahedron") {
        Figure3D newFigure = PlatonicFigure::createDodecahedron(rotations, scale, center, color);
        return {newFigure};
    } else if (type == "Cylinder") {
        Figure3D newFigure = PlatonicFigure::createCylinder(rotations, scale, center, color, n, height);
        return {newFigure};
    } else if (type == "Cone") {
        Figure3D newFigure = PlatonicFigure::createCone(rotations, scale, center, color, n, height);
        return {newFigure};
    } else if (type == "Sphere") {
        Figure3D newFigure = PlatonicFigure::createSphere(rotations, scale, center, color, n);
        return {newFigure};
    } else if (type == "Torus") {
        Figure3D newFigure = PlatonicFigure::createTorus(rotations, scale, center, color, R, r, n, m);
        return {newFigure};
    } else if (type == "FractalCube") {
        Figure3D cube = PlatonicFigure::createCube(rotations, scale, center, color);
        return FigureFractaliser::generateFractal(cube, nrIterations, fractalScale);
    } else if (type == "FractalDodecahedron") {
        Figure3D dodecahedron = PlatonicFigure::createDodecahedron(rotations, scale, center, color);
        return FigureFractaliser::generateFractal(dodecahedron, nrIterations, fractalScale);
    } else if (type == "FractalIcosahedron") {
        Figure3D torus = PlatonicFigure::createIcosahedron(rotations, scale, center, color);
        return FigureFractaliser::generateFractal(torus, nrIterations, fractalScale);
    } else if (type == "FractalTetrahedron") {
        Figure3D tetrahedron = PlatonicFigure::createTetrahedron(rotations, scale, center, color);
        return FigureFractaliser::generateFractal(tetrahedron, nrIterations, fractalScale);
    } else if (type == "FractalOctahedron") {
        Figure3D octahedron = PlatonicFigure::createOctahedron(rotations, scale, center, color);
        return FigureFractaliser::generateFractal(octahedron, nrIterations, fractalScale);
    } else {
        return {};
    }
}

Figure3D FigureParser::parseLineDrawing(const ini::Section &figure, const std::vector<double> &rotations,
                                        const double &scale, const Vector3D &center, const img::Color &color) {
    std::vector<Face3D> faces;
    std::vector<Vector3D> points;

    int nrPoints = figure["nrPoints"].as_int_or_die();
    int nrLines = figure["nrLines"].as_int_or_die();

    // Points
    for (int i = 0; i < nrPoints; i++) {
        std::string pointName = "point" + std::to_string(i);
        auto figurePoint = figure[pointName].as_double_tuple_or_die();
        auto newPoint = Vector3D::point(figurePoint[0], figurePoint[1], figurePoint[2]);
        points.emplace_back(newPoint);
    }

    // Faces
    for (int i = 0; i < nrLines; i++) {
        std::string lineName = "line" + std::to_string(i);
        ini::IntTuple figureLine = figure[lineName].as_int_tuple_or_die();
        auto newFace = Face3D(figureLine);
        faces.emplace_back(newFace);
    }

    return {faces, points, rotations, scale, center, color};
}

Figure3D
FigureParser::parse3DLSystem(const std::vector<double> &rotations, const double &scale, const Vector3D &center,
                             const img::Color &color, const std::string &inputfile) {
    // Parse L-system from inputfile
    LParser::LSystem3D l_system = LSystemFunctions::parseLSystem3D(inputfile);

    // Calculate string
    std::string figureString = LSystemFunctions::getLSystemString(l_system);

    // Get all lines
    std::pair<std::vector<Face3D>, std::vector<Vector3D>> lines = LSystemFunctions::getFacesAndPoints(l_system,
                                                                                                      figureString);

    return {lines.first, lines.second, rotations, scale, center, color};
}