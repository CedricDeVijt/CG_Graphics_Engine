
#ifndef CG_GRAPICS_ENGINE_WIREFRAMEPARSER_H
#define CG_GRAPICS_ENGINE_WIREFRAMEPARSER_H


#include "../easy_image.h"
#include "../ini_configuration.h"
#include "../objects/Figure3D.h"

class WireframeParser {
public:
    static img::EasyImage parseWireframe(const ini::Configuration &configuration);

private:
    static Figures3D getWireframeFigures(const ini::Configuration &configuration, Vector3D &eye, int nrFigures);
};


#endif //CG_GRAPICS_ENGINE_WIREFRAMEPARSER_H
