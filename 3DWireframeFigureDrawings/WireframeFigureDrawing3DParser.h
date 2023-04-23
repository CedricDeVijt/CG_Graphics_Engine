#ifndef CG_GRAPICS_ENGINE_WIREFRAMEFIGUREDRAWING3DPARSER_H
#define CG_GRAPICS_ENGINE_WIREFRAMEFIGUREDRAWING3DPARSER_H


#include "../ini_configuration.h"
#include "../objects/Figure3D.h"

class WireframeFigureDrawing3DParser {
public:

    static Figure3D parseWireframeFigureDrawing3DFigure(const ini::Section& figure);

    static Figure3D parseCube(const ini::Section& figure, std::vector<int> rotations, double scale, const Vector3D& center, const img::Color& color);
    static Figure3D parseTetrahedron(const ini::Section& figure, std::vector<int> rotations, double scale, const Vector3D& center, const img::Color& color);
    static Figure3D parseOctahedron(const ini::Section& figure, std::vector<int> rotations, double scale, const Vector3D& center, const img::Color& color);
    static Figure3D parseIcosahedron(const ini::Section& figure, std::vector<int> rotations, double scale, const Vector3D& center, const img::Color& color);
    static Figure3D parseDodecahedron(const ini::Section& figure, std::vector<int> rotations, double scale, const Vector3D& center, const img::Color& color);
    static Figure3D parseCylinder(const ini::Section& figure, std::vector<int> rotations, double scale, const Vector3D& center, const img::Color& color);
    static Figure3D parseCone(const ini::Section& figure, std::vector<int> rotations, double scale, const Vector3D& center, const img::Color& color);
    static Figure3D parseSphere(const ini::Section& figure, std::vector<int> rotations, double scale, const Vector3D& center, const img::Color& color);
    static Figure3D parseTorus(const ini::Section& figure, std::vector<int> rotations, double scale, const Vector3D& center, const img::Color& color);
};


#endif //CG_GRAPICS_ENGINE_WIREFRAMEFIGUREDRAWING3DPARSER_H
