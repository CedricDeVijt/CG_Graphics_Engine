#ifndef CG_GRAPICS_ENGINE_WIREFRAMEFIGUREPARSER_H
#define CG_GRAPICS_ENGINE_WIREFRAMEFIGUREPARSER_H

#include "../ini_configuration.h"
#include "../Objects/Figure3D.h"

class WireframeFigureParser {
public:

    static Figure3D parseWireframeFigure(const ini::Section& figure);

private:
    static Figure3D parseLineDrawing(const ini::Section& figure, const std::vector<double> &rotations, const double &scale, const Vector3D& center, const img::Color& color);
    static Figure3D parse3DLSystem(const ini::Section& figure, const std::vector<double> &rotations, const double &scale, const Vector3D& center, const img::Color& color);
    static Figure3D parseCube(const std::vector<double> &rotations, const double &scale, const Vector3D& center, const img::Color& color);
    static Figure3D parseTetrahedron(const std::vector<double> &rotations, const double &scale, const Vector3D& center, const img::Color& color);
    static Figure3D parseOctahedron(const std::vector<double> &rotations, const double &scale, const Vector3D& center, const img::Color& color);
    static Figure3D parseIcosahedron(const std::vector<double> &rotations, const double &scale, const Vector3D& center, const img::Color& color);
    static Figure3D parseDodecahedron(const std::vector<double> &rotations, const double &scale, const Vector3D& center, const img::Color& color);
    static Figure3D parseCylinder(const std::vector<double> &rotations, const double &scale, const Vector3D& center, const img::Color& color, const int &n, const double &height);
    static Figure3D parseCone(const std::vector<double> &rotations, const double &scale, const Vector3D& center, const img::Color& color, const int &n, const double &height);
    static Figure3D parseSphere(const std::vector<double> &rotations, const double &scale, const Vector3D& center, const img::Color& color, const int &n);
    static Figure3D parseTorus(const std::vector<double> &rotations, const double &scale, const Vector3D& center, const img::Color& color, const double &R, const double &r, const int &n, const int &m);
};


#endif //CG_GRAPICS_ENGINE_WIREFRAMEFIGUREPARSER_H
