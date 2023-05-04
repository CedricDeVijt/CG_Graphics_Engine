
#ifndef CG_GRAPICS_ENGINE_WIREFRAMEPARSER_H
#define CG_GRAPICS_ENGINE_WIREFRAMEPARSER_H


#include <cmath>
#include "../BaseFiles/easy_image.h"
#include "../BaseFiles/ini_configuration.h"
#include "../Objects/Figure3D.h"

class WireframeParser {
public:
    static img::EasyImage parseWireframe(const ini::Configuration &configuration);

private:
    static Figures3D getWireframeFigures(const ini::Configuration &configuration, Vector3D &eye, int nrFigures);
};


#endif //CG_GRAPICS_ENGINE_WIREFRAMEPARSER_H
