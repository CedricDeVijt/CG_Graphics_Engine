#ifndef CG_GRAPICS_ENGINE_WIREFRAMEFIGUREPARSER_H
#define CG_GRAPICS_ENGINE_WIREFRAMEFIGUREPARSER_H

#include "../BaseFiles/ini_configuration.h"
#include "../Objects/Figure3D.h"

class WireframeFigureParser {
public:
    static Figures3D parseWireframeFigures(const ini::Configuration &configuration, Vector3D &eye, int nrFigures);
    static Figure3D parseWireframeFigure(const ini::Section& figure);

private:
    static Figure3D parseLineDrawing(const ini::Section& figure, const std::vector<double> &rotations, const double &scale, const Vector3D& center, const img::Color& color);
    static Figure3D parse3DLSystem(const std::vector<double> &rotations, const double &scale, const Vector3D &center,const img::Color &color, const std::string &inputfile);
};


#endif //CG_GRAPICS_ENGINE_WIREFRAMEFIGUREPARSER_H
