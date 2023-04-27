#ifndef CG_GRAPICS_ENGINE_WIREFRAMEFIGUREPARSER_H
#define CG_GRAPICS_ENGINE_WIREFRAMEFIGUREPARSER_H

#include <cmath>
#include "../ini_configuration.h"
#include "../Objects/Figure3D.h"

class WireframeFigureParser {
public:

    static Figure3D parseWireframeFigureDrawing3DFigure(const ini::Section& figure);

private:
    static Figure3D parseLineDrawing(const ini::Section& figure, std::vector<double> rotations, double scale, const Vector3D& center, const img::Color& color);
    static Figure3D parseCube(const ini::Section& figure, std::vector<double> rotations, double scale, const Vector3D& center, const img::Color& color);
    static Figure3D parseTetrahedron(const ini::Section& figure, std::vector<double> rotations, double scale, const Vector3D& center, const img::Color& color);
    static Figure3D parseOctahedron(const ini::Section& figure, std::vector<double> rotations, double scale, const Vector3D& center, const img::Color& color);
    static Figure3D parseIcosahedron(const ini::Section& figure, std::vector<double> rotations, double scale, const Vector3D& center, const img::Color& color);
    static Figure3D parseDodecahedron(const ini::Section& figure, std::vector<double> rotations, double scale, const Vector3D& center, const img::Color& color);
    static Figure3D parseCylinder(const ini::Section& figure, std::vector<double> rotations, double scale, const Vector3D& center, const img::Color& color);
    static Figure3D parseCone(const ini::Section& figure, std::vector<double> rotations, double scale, const Vector3D& center, const img::Color& color);
    static Figure3D parseSphere(const ini::Section& figure, std::vector<double> rotations, double scale, const Vector3D& center, const img::Color& color);
    static Figure3D parseTorus(const ini::Section& figure, std::vector<double> rotations, double scale, const Vector3D& center, const img::Color& color);
};


#endif //CG_GRAPICS_ENGINE_WIREFRAMEFIGUREPARSER_H
