#ifndef CG_GRAPICS_ENGINE_WIREFRAMEFIGUREPARSER_H
#define CG_GRAPICS_ENGINE_WIREFRAMEFIGUREPARSER_H

#include "../ini_configuration.h"
#include "../Objects/Figure3D.h"

class WireframeFigureParser {
public:

    static Figure3D parseWireframeFigure(const ini::Section& figure);

private:
    static Figure3D parseLineDrawing(const ini::Section& figure, const std::vector<double> &rotations, const double &scale, const Vector3D& center, const img::Color& color);
    static Figure3D parse3DLSystem(const std::vector<double> &rotations, const double &scale, const Vector3D &center,
                                   const img::Color &color, const std::string &inputfile);
    static Figure3D createCube(const std::vector<double> &rotations, const double &scale, const Vector3D& center, const img::Color& color);
    static Figure3D createTetrahedron(const std::vector<double> &rotations, const double &scale, const Vector3D& center, const img::Color& color);
    static Figure3D createOctahedron(const std::vector<double> &rotations, const double &scale, const Vector3D& center, const img::Color& color);
    static Figure3D createIcosahedron(const std::vector<double> &rotations, const double &scale, const Vector3D& center, const img::Color& color);
    static Figure3D createDodecahedron(const std::vector<double> &rotations, const double &scale, const Vector3D& center, const img::Color& color);
    static Figure3D createCylinder(const std::vector<double> &rotations, const double &scale, const Vector3D& center, const img::Color& color, const int &n, const double &height);
    static Figure3D createCone(const std::vector<double> &rotations, const double &scale, const Vector3D& center, const img::Color& color, const int &n, const double &height);
    static Figure3D createSphere(const std::vector<double> &rotations, const double &scale, const Vector3D& center, const img::Color& color, const int &n);
    static Figure3D parseTorus(const std::vector<double> &rotations, const double &scale, const Vector3D& center, const img::Color& color, const double &R, const double &r, const int &n, const int &m);

    static int calculateIndex(const int &i, const int &j, const int &m);
};


#endif //CG_GRAPICS_ENGINE_WIREFRAMEFIGUREPARSER_H
